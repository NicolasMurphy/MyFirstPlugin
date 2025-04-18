#include "PluginProcessor.h"
#include "PluginEditor.h"

MyFirstPluginAudioProcessor::MyFirstPluginAudioProcessor()
    : parameters(*this, nullptr, juce::Identifier("Params"),
        {
            std::make_unique<juce::AudioParameterFloat>("feedback", "Feedback", -2.0f, 2.0f, 0.5f),
            std::make_unique<juce::AudioParameterFloat>("delayTime", "Delay Time", 9.0f, 2400.0f, 480.0f)
        })
{}

MyFirstPluginAudioProcessor::~MyFirstPluginAudioProcessor() {}

const juce::String MyFirstPluginAudioProcessor::getName() const { return "MyFirstPlugin"; }
bool MyFirstPluginAudioProcessor::acceptsMidi() const { return false; }
bool MyFirstPluginAudioProcessor::producesMidi() const { return false; }
bool MyFirstPluginAudioProcessor::isMidiEffect() const { return false; }
double MyFirstPluginAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int MyFirstPluginAudioProcessor::getNumPrograms() { return 1; }
int MyFirstPluginAudioProcessor::getCurrentProgram() { return 0; }
void MyFirstPluginAudioProcessor::setCurrentProgram(int) {}
const juce::String MyFirstPluginAudioProcessor::getProgramName(int) { return {}; }
void MyFirstPluginAudioProcessor::changeProgramName(int, const juce::String&) {}

void MyFirstPluginAudioProcessor::prepareToPlay(double sampleRate, int)
{
    const int delayBufferSize = static_cast<int>(2.0 * sampleRate);
    delayBuffer.setSize(getTotalNumOutputChannels(), delayBufferSize);
    delayBuffer.clear();
    delayWritePosition = 0;

    // Initialize one damping filter per output channel
    dampingFilters.clear();
    for (int i = 0; i < getTotalNumOutputChannels(); ++i)
    {
        auto* filter = new juce::IIRFilter();
        filter->setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, 4000.0)); // 4kHz cutoff
        dampingFilters.add(filter);
    }
}

void MyFirstPluginAudioProcessor::releaseResources() {}

void MyFirstPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    const int delayBufferSize = delayBuffer.getNumSamples();

    float feedback = *parameters.getRawParameterValue("feedback");
    int delayTimeInSamples = static_cast<int>(*parameters.getRawParameterValue("delayTime"));

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            const int readPosition = (delayWritePosition + i - delayTimeInSamples + delayBufferSize) % delayBufferSize;
            const int writePosition = (delayWritePosition + i) % delayBufferSize;

            float dampingCutoff = 200.0f + 10000.0f * std::pow(0.5f, delayTimeInSamples / 5000.0f);
            dampingFilters[channel]->setCoefficients(juce::IIRCoefficients::makeLowPass(getSampleRate(), dampingCutoff));

            float delayedSample = dampingFilters[channel]->processSingleSampleRaw(delayData[readPosition]);

            delayData[writePosition] = channelData[i] + (feedback * delayedSample);
            channelData[i] += delayedSample;

        }
    }

    delayWritePosition = (delayWritePosition + numSamples) % delayBuffer.getNumSamples();
}

bool MyFirstPluginAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* MyFirstPluginAudioProcessor::createEditor()
{
    return new MyFirstPluginAudioProcessorEditor(*this);
}

void MyFirstPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream(destData, true).writeString(parameters.state.toXmlString());
}

void MyFirstPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto xml = juce::parseXML(juce::String::createStringFromData(static_cast<const char*>(data), sizeInBytes));
    if (xml)
        parameters.state = juce::ValueTree::fromXml(*xml);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyFirstPluginAudioProcessor();
}
