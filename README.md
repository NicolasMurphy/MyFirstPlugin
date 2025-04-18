# MyFirstPlugin

This is an early-stage experiment in building audio plugins using JUCE and C++.

The project is inspired by Reason’s Thor comb filter - particularly its ability to push resonance beyond 100%.
The goal is to explore comb filtering and delay-based effects, and eventually introduce unique twists of my own, though the final direction is still evolving.

### Plugin Availability

Compiled VST3 builds are available in the [`/dist`](./dist) folder.

- **Windows**: May work depending on DAW and system configuration. If you experience any crashes, please report them along with any available crash logs or details.
- **macOS**: Not currently supported. Plugins must be built natively on a Mac using Xcode in order to function properly.

If you'd like to test on macOS, the JUCE project can be built manually using Xcode.

> I plan to support macOS builds and offer platform-specific installers in the future.

### Tools Used

- C++17
- JUCE Framework
- CMake
- VST3 SDK
- Visual Studio 2022
