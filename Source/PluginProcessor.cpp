#include "PluginProcessor.h"
#include "PluginEditor.h"

MyFirstPluginAudioProcessor::MyFirstPluginAudioProcessor() {}
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

void MyFirstPluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    const int delayBufferSize = static_cast<int>(2.0 * sampleRate); // 2 seconds max delay
    delayBuffer.setSize(getTotalNumOutputChannels(), delayBufferSize);
    delayBuffer.clear();
    delayWritePosition = 0;
}

void MyFirstPluginAudioProcessor::releaseResources() {}

void MyFirstPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    const int delayBufferSize = delayBuffer.getNumSamples();
    const int delayTimeInSamples = 4800; // ~0.1 sec delay at 48kHz

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            int delayReadPosition = (delayWritePosition + i - delayTimeInSamples + delayBufferSize) % delayBufferSize;
            float delayedSample = delayData[delayReadPosition];

            // Write current sample to delay buffer
            delayData[(delayWritePosition + i) % delayBufferSize] = channelData[i];

            // Mix in delayed sample
            channelData[i] += 0.5f * delayedSample;
        }
    }

    delayWritePosition = (delayWritePosition + numSamples) % delayBuffer.getNumSamples();
}

bool MyFirstPluginAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* MyFirstPluginAudioProcessor::createEditor()
{
    return new MyFirstPluginAudioProcessorEditor(*this);
}

void MyFirstPluginAudioProcessor::getStateInformation(juce::MemoryBlock&) {}
void MyFirstPluginAudioProcessor::setStateInformation(const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyFirstPluginAudioProcessor();
}
