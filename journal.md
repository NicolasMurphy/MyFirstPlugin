# Development Journal

## 2025-04-18

### Goals
- Add damping
- Add interpolation
- Future enhancements: Logarithmic frequency mapping, polarity switch.
- Potential future enhancements: Saturation, Stereo spread / detuning, freezing?, exciters?

### Notes
-

## 2025-04-17

### Goals
- Initial setup and proof of concept using a simple delay effect.

### Notes
- Current development workflow:
  - Build the plugin by opening and compiling `MyFirstPlugin.sln` in Visual Studio (Release | x64)
  - Test the plugin using JUCE’s `AudioPluginHost.exe` with live mic input
  - Remove and re-add the plugin in AudioPluginHost between builds by deleting and re-inserting it into the signal chain
- Delay feedback currently exhibits glitching when delay time is adjusted in real-time. This may be addressed later with interpolation or by introducing a fixed-delay comb mode.
