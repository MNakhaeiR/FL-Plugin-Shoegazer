cmake_minimum_required(VERSION 3.22)

project(ShoegazerPlugin VERSION 1.0.0)

# Add JUCE to the project
add_subdirectory(JUCE)

# Define the plugin target
juce_add_plugin(ShoegazerPlugin
    VERSION 1.0.0
    COMPANY_NAME "Shahrvand"
    PLUGIN_MANUFACTURER_CODE Shrvnd
    PLUGIN_CODE Sgzr
    FORMATS VST3 Standalone
    PRODUCT_NAME "Shoegazer"
    
    # Plugin characteristics
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    
    # Copy to VST3 folder for easy testing
    COPY_PLUGIN_AFTER_BUILD FALSE
    
    # VST3 SDK path (if needed)
    # VST3_SDK_PATH "path/to/vst3sdk"
)

# Generate JuceHeader.h
juce_generate_juce_header(ShoegazerPlugin)

# Source files
target_sources(ShoegazerPlugin
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/DSP/ShoegazeVoice.cpp
        Source/DSP/ShoegazeVoice.h
        Source/DSP/ShoegazeSound.h
        Source/DSP/EffectsChain.cpp
        Source/DSP/EffectsChain.h
        Source/DSP/WavetableOscillator.cpp
        Source/DSP/WavetableOscillator.h
        Source/DSP/PresetManager.cpp
        Source/DSP/PresetManager.h
        Source/DSP/DrumSynthesizer.cpp
        Source/DSP/DrumSynthesizer.h
        Source/DSP/SamplePlayer.cpp
        Source/DSP/SamplePlayer.h
        Source/UI/ModernLookAndFeel.cpp
        Source/UI/ModernLookAndFeel.h
        Source/UI/CustomComponents.cpp
        Source/UI/CustomComponents.h
        Source/UI/VisualizerComponent.cpp
        Source/UI/VisualizerComponent.h
)

# Compiler definitions
target_compile_definitions(ShoegazerPlugin
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
)

# Link JUCE modules
target_link_libraries(ShoegazerPlugin
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_animation
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Set C++ standard
set_target_properties(ShoegazerPlugin PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
