#include "PluginEditor.h"
#include "PluginProcessor.h"

MyFirstPluginAudioProcessorEditor::MyFirstPluginAudioProcessorEditor(MyFirstPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Feedback slider
    feedbackSlider.setSliderStyle(juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    feedbackSlider.setRange(-2.0f, 2.0f, 0.01f);
    addAndMakeVisible(feedbackSlider);

    feedbackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getState(), "feedback", feedbackSlider);

    // Delay slider
    delaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    delaySlider.setRange(9.0f, 2400.0f, 1.0f); // Delay in samples
    delaySlider.setSkewFactorFromMidPoint(100.0f); // Emphasize lower end (musical range)

    addAndMakeVisible(delaySlider);

    delayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getState(), "delayTime", delaySlider);

    setSize(240, 260);
}

MyFirstPluginAudioProcessorEditor::~MyFirstPluginAudioProcessorEditor() {}

void MyFirstPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);

    g.drawFittedText("Feedback", juce::Rectangle<int>(60, 5, 120, 20), juce::Justification::centred, 1);
    g.drawFittedText("Delay Time", juce::Rectangle<int>(30, 170, 180, 20), juce::Justification::centred, 1);
}

void MyFirstPluginAudioProcessorEditor::resized()
{
    feedbackSlider.setBounds(60, 20, 120, 120);
    delaySlider.setBounds(30, 190, 180, 30);
}
