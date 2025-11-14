# Build Instructions for Shoegazer VST Plugin

## Quick Start (Windows)

Open PowerShell and run:

```powershell
# Navigate to project root
cd D:\Projects\Audio\FL-Studio\Shoegazer

# Create build directory
if (!(Test-Path build)) { mkdir build }
cd build

# Configure CMake
cmake .. -G "Visual Studio 17 2022" -A x64

# Build Release version
cmake --build . --config Release

# The plugin will be in:
# build\ShoegazerPlugin_artefacts\Release\VST3\Shoegazer.vst3
```

## Installation

After building, copy the VST3 to your plugin folder:

```powershell
# Copy to system VST3 folder
Copy-Item -Path "ShoegazerPlugin_artefacts\Release\VST3\Shoegazer.vst3" -Destination "C:\Program Files\Common Files\VST3\" -Recurse -Force
```

Then rescan plugins in FL Studio.

## Development Build

For debugging:

```powershell
cmake --build . --config Debug
```

## Clean Build

To start fresh:

```powershell
cd D:\Projects\Audio\FL-Studio\Shoegazer
Remove-Item -Recurse -Force build
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

## Building Standalone

The standalone version is automatically built alongside the VST3:

```
build\ShoegazerPlugin_artefacts\Release\Standalone\Shoegazer.exe
```

## Troubleshooting

### JUCE Not Found

Make sure the JUCE folder is in the project root:

```
D:\Projects\Audio\FL-Studio\Shoegazer\JUCE\
```

### CMake Version Error

Update CMake to 3.22 or higher:

```powershell
winget install Kitware.CMake
```

### Visual Studio Not Found

Install Visual Studio 2022 with "Desktop development with C++" workload.

### Build Errors

1. Clean build directory
2. Update JUCE to latest version
3. Check all source files are present in Source/ directory

## Project Structure

```
Shoegazer/
├── CMakeLists.txt          # Main build configuration
├── README.md               # Documentation
├── BUILD.md               # This file
├── JUCE/                  # JUCE framework
└── Source/
    ├── PluginProcessor.cpp/h    # Main audio processing
    ├── PluginEditor.cpp/h       # UI editor
    ├── DSP/
    │   ├── ShoegazeVoice.cpp/h      # Synthesizer voice
    │   ├── ShoegazeSound.h          # Sound definition
    │   ├── WavetableOscillator.cpp/h # Oscillator
    │   └── EffectsChain.cpp/h       # Effects processing
    └── UI/
        ├── ModernLookAndFeel.cpp/h    # Custom UI theme
        ├── CustomComponents.cpp/h      # UI components
        └── VisualizerComponent.cpp/h   # Waveform display
```

## Configuration Options

Edit CMakeLists.txt to change:

- `COMPANY_NAME`: Your company name
- `PLUGIN_MANUFACTURER_CODE`: 4-character manufacturer ID
- `PLUGIN_CODE`: 4-character plugin ID
- `FORMATS`: Build formats (VST3, AU, Standalone, etc.)
- `COPY_PLUGIN_AFTER_BUILD`: Auto-copy to plugin folder (TRUE/FALSE)

## Performance Optimization

For maximum performance in Release builds, CMake is configured with:

- Link-Time Optimization (LTO)
- Recommended warning flags
- Optimized DSP code paths

## Testing

1. Build the standalone version
2. Test audio processing
3. Load in FL Studio as VST3
4. Test automation in your DAW
5. Verify preset saving/loading

## Distribution

To distribute:

1. Build in Release mode
2. Copy `Shoegazer.vst3` from build folder
3. Include README.md
4. Consider code signing (Windows) or notarization (macOS)
