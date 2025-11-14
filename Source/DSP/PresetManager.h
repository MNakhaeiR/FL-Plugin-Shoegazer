#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Preset Manager - Handles saving, loading, and managing presets
 */
struct Preset
{
    juce::String name;
    juce::String category;
    juce::ValueTree state;
    
    Preset() = default;
    Preset(const juce::String& n, const juce::String& cat, const juce::ValueTree& s)
        : name(n), category(cat), state(s) {}
};

class PresetManager
{
public:
    PresetManager();
    
    // Preset operations
    void savePreset(const juce::String& name, const juce::String& category, const juce::ValueTree& state);
    bool loadPreset(int index, juce::ValueTree& outState);
    bool loadPresetByName(const juce::String& name, juce::ValueTree& outState);
    void deletePreset(int index);
    
    // Factory presets
    void createFactoryPresets();
    
    // Getters
    int getNumPresets() const { return static_cast<int>(presets.size()); }
    Preset getPreset(int index) const;
    std::vector<Preset> getAllPresets() const { return presets; }
    juce::StringArray getPresetNames() const;
    juce::StringArray getCategories() const;
    std::vector<Preset> getPresetsInCategory(const juce::String& category) const;
    
    // File operations
    void savePresetsToFile();
    void loadPresetsFromFile();
    juce::File getPresetsDirectory();
    
private:
    std::vector<Preset> presets;
    
    // Factory preset builders
    Preset createThickPadPreset();
    Preset createShimmeringLeadPreset();
    Preset createAmbientTexturePreset();
    Preset createDreamyBassPreset();
    Preset createNoiseWallPreset();
    Preset createCrystalArpPreset();
    Preset createVelvetPadPreset();
    Preset createDistortedLeadPreset();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};
