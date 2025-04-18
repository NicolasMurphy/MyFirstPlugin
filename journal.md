# Development Journal

## 2025-04-18

### Goals
- ⏳ Add interpolation for smooth delay-time sweeps
- ⏳ Add polarity switch (COMB+/– style)
- ⏳ Rename "Feedback" to "Resonance"
- ⏳ Rename "Delay" to "Frequency"
- ⏳ Currently using a 50/50 wet/dry mix (`channelData[i] += delayedSample;`). Consider testing 100% wet mode later by replacing it with `channelData[i] = delayedSample;` to better match traditional comb filter behavior. This can be found in PluginProcessor.cpp line 70.
- ⏳ 200% feedback is too much, change to 150%, maybe less
-

### Notes
-


## 2025-04-17

### Goals
- ✅ Add damping (low-pass filter in feedback path)
- ⏳ Add interpolation for smooth delay-time sweeps
- ✅ Apply logarithmic mapping to delay slider and tighten bounds to comb-relevant range
- ⏳ Add polarity switch (COMB+/– style)
- ⏳ Rename "Feedback" to "Resonance"
- ⏳ Rename "Delay" to "Frequency"
- ⏳ Currently using a 50/50 wet/dry mix (`channelData[i] += delayedSample;`). Consider testing 100% wet mode later by replacing it with `channelData[i] = delayedSample;` to better match traditional comb filter behavior. This can be found in PluginProcessor.cpp line 70.
- 🧠 Future enhancements:
  - Saturation in feedback loop
  - Stereo spread / channel detuning
  - Freeze mode
  - Built-in exciters (e.g. burst, noise, click)
  - Different modes (explore Zebra's comb filter)

### Notes
- Damping is currently hardcoded to ~4kHz but is dynamically mapped to delay time for a more natural, "physical model"-like tone. Perhaps adjusting the hardcoded value and way this is dynamically mapped can be how I can implement different "modes".
- Delay slider now ranges from 9 to 2400 samples, emphasizing the most musically useful comb range.
- Skew factor added for better control at lower (pitched) delay values.
- Next up: interpolation to prevent glitching when delay is modulated. Although not noticing this when testing in DAW.


## 2025-04-16

### Goals
- Initial setup and proof of concept using a simple delay effect

### Notes
- Current development workflow:
  - Build the plugin by opening and compiling `MyFirstPlugin.sln` in Visual Studio (Release | x64)
  - Test the plugin using JUCE’s `AudioPluginHost.exe` with live mic input
  - Remove and re-add the plugin in AudioPluginHost between builds by deleting and re-inserting it into the signal chain
- Delay feedback currently exhibits glitching when delay time is adjusted in real-time. This may be addressed later with interpolation or by introducing a fixed-delay comb mode.
