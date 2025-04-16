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

void MyFirstPluginAudioProcessor::prepareToPlay(double, int) {}
void MyFirstPluginAudioProcessor::releaseResources() {}

void MyFirstPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        float* data = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            data[i] *= 0.5f;  // Simple gain reduction
        }
    }
}

bool MyFirstPluginAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* MyFirstPluginAudioProcessor::createEditor() {
    return new MyFirstPluginAudioProcessorEditor(*this);
}

void MyFirstPluginAudioProcessor::getStateInformation(juce::MemoryBlock&) {}
void MyFirstPluginAudioProcessor::setStateInformation(const void*, int) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyFirstPluginAudioProcessor();
}
