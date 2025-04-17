# Development Journal

## 2025-04-18

### Goals
- Begin prototyping a pitch-based comb filter by mapping a frequency control to delay time and refining the feedback loop accordingly.
- Preserve the existing delay-time control for experimentation, and consider adding a mode toggle or separating frequency control into a dedicated UI section.

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
