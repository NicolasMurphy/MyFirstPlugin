cmake_minimum_required(VERSION 3.15)

project(MyFirstPlugin VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# Path to your JUCE folder (adjust this!)
set(JUCE_DIR "C:/Users/Admin/JUCE")

add_subdirectory(${JUCE_DIR} JUCE)

juce_add_plugin(MyFirstPlugin
    COMPANY_NAME "My Company"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE MfPl
    FORMATS VST3
    PRODUCT_NAME "My First Plugin"
)

target_sources(MyFirstPlugin PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

target_compile_definitions(MyFirstPlugin PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(MyFirstPlugin PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_utils
)
