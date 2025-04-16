#include "PluginProcessor.h"
#include "PluginEditor.h"

MyFirstPluginAudioProcessorEditor::MyFirstPluginAudioProcessorEditor(MyFirstPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);
}

MyFirstPluginAudioProcessorEditor::~MyFirstPluginAudioProcessorEditor() {}

void MyFirstPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawFittedText("My First Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void MyFirstPluginAudioProcessorEditor::resized() {}
