#include "PluginEditor.h"
#include "PluginProcessor.h"

MyFirstPluginAudioProcessorEditor::MyFirstPluginAudioProcessorEditor(MyFirstPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Configure the feedback slider
    feedbackSlider.setSliderStyle(juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    feedbackSlider.setRange(-2.0f, 2.0f, 0.01f);
    addAndMakeVisible(feedbackSlider);

    // Attach the slider to the parameter
    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getState(), "feedback", feedbackSlider);

    // Set the window size
    setSize(200, 200);
}

MyFirstPluginAudioProcessorEditor::~MyFirstPluginAudioProcessorEditor() {}

void MyFirstPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Feedback", getLocalBounds(), juce::Justification::centredTop, 1);
}

void MyFirstPluginAudioProcessorEditor::resized()
{
    feedbackSlider.setBounds(40, 50, 120, 120);
}
