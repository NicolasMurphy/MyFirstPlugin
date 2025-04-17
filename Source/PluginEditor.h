#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MyFirstPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MyFirstPluginAudioProcessorEditor(MyFirstPluginAudioProcessor&);
    ~MyFirstPluginAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    MyFirstPluginAudioProcessor& audioProcessor;

    juce::Slider feedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyFirstPluginAudioProcessorEditor)
};
