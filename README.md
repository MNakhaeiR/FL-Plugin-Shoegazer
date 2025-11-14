# Shoegazer VST Plugin

**A professional-grade VST3 synthesizer and effects plugin for creating dreamy, atmospheric shoegaze music.**

## 🎵 Features

### Synthesizer

- **Dual Wavetable Oscillators** with 5 waveform types (Sine, Saw, Square, Triangle, Rich Harmonic)
- **Unison Mode** with up to 8 voices per oscillator for ultra-thick sounds
- **Detune Control** for creating lush, chorused textures
- **State-Variable Filter** with resonance for shaping your sound
- **ADSR Envelope** for dynamic control

### Effects Chain

- **Reverb**: Massive, atmospheric reverb perfect for shoegaze
  - Room Size, Damping, Wet/Dry Mix, Stereo Width
- **Chorus**: Rich modulation for shimmering textures
  - Rate, Depth, Feedback, Mix controls
- **Delay**: Tempo-synced or free-running delay
  - Delay Time (10-2000ms), Feedback, Mix
- **Distortion/Saturation**: Warm analog-style saturation

### User Interface

- **Stunning Modern Dark Theme** with purple and cyan accents
- **Animated Controls** with glow effects and smooth transitions
- **Real-time Visualizer** showing waveform and spectrum
- **Organized Panel Layout** for intuitive workflow
- **Fully Automatable Parameters** for DAW integration

## 🔧 Building the Plugin

### Prerequisites

- **CMake** 3.22 or higher
- **C++17 compatible compiler**
  - Windows: Visual Studio 2019/2022
  - macOS: Xcode 12+
  - Linux: GCC 9+ or Clang 10+
- **JUCE Framework** (included as submodule)

### Windows Build Instructions

```powershell
# Navigate to project directory
cd D:\Projects\Audio\FL-Studio\Shoegazer

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

# Build the plugin
cmake --build . --config Release

# The VST3 will be in: build\ShoegazerPlugin_artefacts\Release\VST3\
```

### macOS Build Instructions

```bash
cd /path/to/Shoegazer

mkdir build && cd build

cmake .. -G "Xcode"

cmake --build . --config Release

# VST3 will be in: build/ShoegazerPlugin_artefacts/Release/VST3/
```

### Linux Build Instructions

```bash
cd /path/to/Shoegazer

mkdir build && cd build

cmake ..

cmake --build . --config Release
```

## 📦 Installation

### Windows

1. Copy `Shoegazer.vst3` to: `C:\Program Files\Common Files\VST3\`
2. Rescan plugins in FL Studio

### macOS

1. Copy `Shoegazer.vst3` to: `~/Library/Audio/Plug-Ins/VST3/` or `/Library/Audio/Plug-Ins/VST3/`
2. Rescan plugins in your DAW

### FL Studio Specific

- **For Synth**: The plugin will appear in the Channel Rack under "Generators"
- **For Effects**: Route to mixer and add as an effect (though it's primarily a synth)

## 🎹 Usage

### Getting Started

1. Load Shoegazer in FL Studio's Channel Rack as a generator
2. Play MIDI notes to hear the rich, layered sound
3. Adjust oscillator waveforms and unison for thickness
4. Add reverb and delay for that classic shoegaze wash
5. Use the filter to shape your sound

### Preset Workflow

- All parameters are automatable in your DAW
- Save your settings using your DAW's preset management
- State is automatically saved with your project

### Sound Design Tips

- **Thick Pads**: Set Unison to 6-8, detune to 0.15, add reverb
- **Lead Sounds**: Use Rich waveform, lower reverb, increase filter cutoff
- **Dreamy Textures**: Max out reverb size, add chorus and delay
- **Aggressive Tones**: Add distortion, increase filter resonance

## 🎛️ Parameters

### Oscillators

- **Osc 1/2 Wave**: Choose waveform type
- **Detune**: 0.0 - 1.0 (spread between unison voices)
- **Unison**: 1 - 8 voices

### Filter

- **Cutoff**: 20 Hz - 20 kHz
- **Resonance**: 0.1 - 2.0

### Envelope

- **Attack**: 0.001 - 5.0 seconds
- **Decay**: 0.001 - 5.0 seconds
- **Sustain**: 0.0 - 1.0
- **Release**: 0.001 - 10.0 seconds

### Effects

- **Reverb Size**: 0.0 - 1.0
- **Reverb Mix**: 0.0 - 1.0
- **Chorus Mix**: 0.0 - 1.0
- **Delay Time**: 10 - 2000 ms
- **Delay Mix**: 0.0 - 1.0

### Master

- **Volume**: 0.0 - 2.0

## 🐛 Troubleshooting

### Plugin Doesn't Load

- Ensure you're using a 64-bit version
- Check that Visual C++ Redistributables are installed (Windows)
- Verify the .vst3 file is in the correct directory

### No Sound

- Check MIDI input is reaching the plugin
- Verify master volume is not at 0
- Check your DAW's routing

### Performance Issues

- Reduce unison voice count
- Lower reverb quality if CPU usage is high
- Disable effects you're not using

## 🔮 Future Enhancements

- Preset browser with factory presets
- Additional oscillator modes (FM, additive)
- Modulation matrix
- More effects (phaser, flanger)
- MPE support

## 📄 License

This project uses the JUCE framework, which is licensed under GPL v3 or commercial license.

For the plugin itself: All rights reserved © 2025

## 🙏 Credits

Built with:

- **JUCE Framework** - Audio plugin framework
- **C++17** - Programming language
- **CMake** - Build system

Created for producing beautiful shoegaze and ambient music. 🌊✨

---

**Enjoy creating dreamy soundscapes!** 🎸🎹
