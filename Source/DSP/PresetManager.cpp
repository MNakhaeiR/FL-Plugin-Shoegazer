#include "PresetManager.h"

PresetManager::PresetManager()
{
    createFactoryPresets();
}

void PresetManager::createFactoryPresets()
{
    presets.clear();
    
    // Add factory presets
    presets.push_back(createThickPadPreset());
    presets.push_back(createShimmeringLeadPreset());
    presets.push_back(createAmbientTexturePreset());
    presets.push_back(createDreamyBassPreset());
    presets.push_back(createNoiseWallPreset());
    presets.push_back(createCrystalArpPreset());
    presets.push_back(createVelvetPadPreset());
    presets.push_back(createDistortedLeadPreset());
}

Preset PresetManager::createThickPadPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 4, nullptr);  // Rich
    state.setProperty("osc2Wave", 1, nullptr);  // Saw
    state.setProperty("oscDetune", 0.15f, nullptr);
    state.setProperty("oscUnison", 6, nullptr);
    state.setProperty("filterCutoff", 2000.0f, nullptr);
    state.setProperty("filterResonance", 0.5f, nullptr);
    state.setProperty("envAttack", 0.5f, nullptr);
    state.setProperty("envDecay", 0.5f, nullptr);
    state.setProperty("envSustain", 0.8f, nullptr);
    state.setProperty("envRelease", 1.5f, nullptr);
    state.setProperty("reverbSize", 0.9f, nullptr);
    state.setProperty("reverbWet", 0.5f, nullptr);
    state.setProperty("chorusMix", 0.3f, nullptr);
    state.setProperty("delayMix", 0.3f, nullptr);
    state.setProperty("fmAmount", 0.0f, nullptr);
    state.setProperty("fmRatio", 2.0f, nullptr);
    state.setProperty("noiseLevel", 0.05f, nullptr);
    state.setProperty("subOscLevel", 0.3f, nullptr);
    
    return Preset("Thick Pad", "Pads", state);
}

Preset PresetManager::createShimmeringLeadPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 4, nullptr);
    state.setProperty("osc2Wave", 0, nullptr);
    state.setProperty("oscDetune", 0.08f, nullptr);
    state.setProperty("oscUnison", 4, nullptr);
    state.setProperty("filterCutoff", 8000.0f, nullptr);
    state.setProperty("filterResonance", 0.3f, nullptr);
    state.setProperty("envAttack", 0.05f, nullptr);
    state.setProperty("envDecay", 0.3f, nullptr);
    state.setProperty("envSustain", 0.7f, nullptr);
    state.setProperty("envRelease", 0.8f, nullptr);
    state.setProperty("reverbSize", 0.6f, nullptr);
    state.setProperty("reverbWet", 0.3f, nullptr);
    state.setProperty("chorusMix", 0.4f, nullptr);
    state.setProperty("delayMix", 0.2f, nullptr);
    state.setProperty("fmAmount", 1.5f, nullptr);
    state.setProperty("fmRatio", 3.0f, nullptr);
    state.setProperty("noiseLevel", 0.0f, nullptr);
    state.setProperty("subOscLevel", 0.0f, nullptr);
    
    return Preset("Shimmering Lead", "Leads", state);
}

Preset PresetManager::createAmbientTexturePreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 4, nullptr);
    state.setProperty("osc2Wave", 3, nullptr);
    state.setProperty("oscDetune", 0.25f, nullptr);
    state.setProperty("oscUnison", 8, nullptr);
    state.setProperty("filterCutoff", 3000.0f, nullptr);
    state.setProperty("filterResonance", 0.8f, nullptr);
    state.setProperty("envAttack", 2.0f, nullptr);
    state.setProperty("envDecay", 1.0f, nullptr);
    state.setProperty("envSustain", 0.6f, nullptr);
    state.setProperty("envRelease", 3.0f, nullptr);
    state.setProperty("reverbSize", 1.0f, nullptr);
    state.setProperty("reverbWet", 0.7f, nullptr);
    state.setProperty("chorusMix", 0.5f, nullptr);
    state.setProperty("delayTime", 500.0f, nullptr);
    state.setProperty("delayFeedback", 0.7f, nullptr);
    state.setProperty("delayMix", 0.6f, nullptr);
    state.setProperty("fmAmount", 0.5f, nullptr);
    state.setProperty("fmRatio", 1.5f, nullptr);
    state.setProperty("noiseLevel", 0.25f, nullptr);
    state.setProperty("subOscLevel", 0.1f, nullptr);
    
    return Preset("Ambient Texture", "Textures", state);
}

Preset PresetManager::createDreamyBassPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 1, nullptr);  // Saw
    state.setProperty("osc2Wave", 2, nullptr);  // Square
    state.setProperty("oscDetune", 0.05f, nullptr);
    state.setProperty("oscUnison", 3, nullptr);
    state.setProperty("filterCutoff", 800.0f, nullptr);
    state.setProperty("filterResonance", 1.2f, nullptr);
    state.setProperty("envAttack", 0.01f, nullptr);
    state.setProperty("envDecay", 0.4f, nullptr);
    state.setProperty("envSustain", 0.6f, nullptr);
    state.setProperty("envRelease", 0.5f, nullptr);
    state.setProperty("reverbSize", 0.5f, nullptr);
    state.setProperty("reverbWet", 0.2f, nullptr);
    state.setProperty("chorusMix", 0.2f, nullptr);
    state.setProperty("delayMix", 0.15f, nullptr);
    state.setProperty("fmAmount", 0.0f, nullptr);
    state.setProperty("fmRatio", 2.0f, nullptr);
    state.setProperty("noiseLevel", 0.0f, nullptr);
    state.setProperty("subOscLevel", 0.6f, nullptr);
    
    return Preset("Dreamy Bass", "Bass", state);
}

Preset PresetManager::createNoiseWallPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 2, nullptr);
    state.setProperty("osc2Wave", 1, nullptr);
    state.setProperty("oscDetune", 0.3f, nullptr);
    state.setProperty("oscUnison", 8, nullptr);
    state.setProperty("filterCutoff", 5000.0f, nullptr);
    state.setProperty("filterResonance", 0.9f, nullptr);
    state.setProperty("envAttack", 0.1f, nullptr);
    state.setProperty("envDecay", 0.2f, nullptr);
    state.setProperty("envSustain", 0.9f, nullptr);
    state.setProperty("envRelease", 0.5f, nullptr);
    state.setProperty("reverbSize", 0.95f, nullptr);
    state.setProperty("reverbWet", 0.6f, nullptr);
    state.setProperty("chorusMix", 0.4f, nullptr);
    state.setProperty("distAmount", 0.4f, nullptr);
    state.setProperty("distMix", 0.3f, nullptr);
    state.setProperty("delayMix", 0.4f, nullptr);
    state.setProperty("fmAmount", 3.0f, nullptr);
    state.setProperty("fmRatio", 5.0f, nullptr);
    state.setProperty("noiseLevel", 0.4f, nullptr);
    state.setProperty("subOscLevel", 0.2f, nullptr);
    
    return Preset("Noise Wall", "Aggressive", state);
}

Preset PresetManager::createCrystalArpPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 0, nullptr);  // Sine
    state.setProperty("osc2Wave", 4, nullptr);  // Rich
    state.setProperty("oscDetune", 0.1f, nullptr);
    state.setProperty("oscUnison", 2, nullptr);
    state.setProperty("filterCutoff", 12000.0f, nullptr);
    state.setProperty("filterResonance", 0.4f, nullptr);
    state.setProperty("envAttack", 0.001f, nullptr);
    state.setProperty("envDecay", 0.2f, nullptr);
    state.setProperty("envSustain", 0.3f, nullptr);
    state.setProperty("envRelease", 0.3f, nullptr);
    state.setProperty("reverbSize", 0.7f, nullptr);
    state.setProperty("reverbWet", 0.4f, nullptr);
    state.setProperty("chorusMix", 0.3f, nullptr);
    state.setProperty("delayTime", 250.0f, nullptr);
    state.setProperty("delayMix", 0.5f, nullptr);
    state.setProperty("fmAmount", 2.0f, nullptr);
    state.setProperty("fmRatio", 4.0f, nullptr);
    state.setProperty("noiseLevel", 0.0f, nullptr);
    state.setProperty("subOscLevel", 0.0f, nullptr);
    
    return Preset("Crystal Arp", "Plucks", state);
}

Preset PresetManager::createVelvetPadPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 3, nullptr);  // Triangle
    state.setProperty("osc2Wave", 0, nullptr);  // Sine
    state.setProperty("oscDetune", 0.12f, nullptr);
    state.setProperty("oscUnison", 5, nullptr);
    state.setProperty("filterCutoff", 1500.0f, nullptr);
    state.setProperty("filterResonance", 0.6f, nullptr);
    state.setProperty("envAttack", 1.0f, nullptr);
    state.setProperty("envDecay", 0.8f, nullptr);
    state.setProperty("envSustain", 0.75f, nullptr);
    state.setProperty("envRelease", 2.0f, nullptr);
    state.setProperty("reverbSize", 0.85f, nullptr);
    state.setProperty("reverbWet", 0.5f, nullptr);
    state.setProperty("chorusMix", 0.35f, nullptr);
    state.setProperty("delayMix", 0.25f, nullptr);
    state.setProperty("fmAmount", 0.0f, nullptr);
    state.setProperty("fmRatio", 2.0f, nullptr);
    state.setProperty("noiseLevel", 0.15f, nullptr);
    state.setProperty("subOscLevel", 0.2f, nullptr);
    
    return Preset("Velvet Pad", "Pads", state);
}

Preset PresetManager::createDistortedLeadPreset()
{
    juce::ValueTree state("Preset");
    state.setProperty("osc1Wave", 1, nullptr);
    state.setProperty("osc2Wave", 2, nullptr);
    state.setProperty("oscDetune", 0.06f, nullptr);
    state.setProperty("oscUnison", 3, nullptr);
    state.setProperty("filterCutoff", 6000.0f, nullptr);
    state.setProperty("filterResonance", 1.0f, nullptr);
    state.setProperty("envAttack", 0.02f, nullptr);
    state.setProperty("envDecay", 0.3f, nullptr);
    state.setProperty("envSustain", 0.7f, nullptr);
    state.setProperty("envRelease", 0.6f, nullptr);
    state.setProperty("reverbSize", 0.6f, nullptr);
    state.setProperty("reverbWet", 0.3f, nullptr);
    state.setProperty("chorusMix", 0.2f, nullptr);
    state.setProperty("distAmount", 0.6f, nullptr);
    state.setProperty("distMix", 0.5f, nullptr);
    state.setProperty("delayMix", 0.3f, nullptr);
    state.setProperty("fmAmount", 4.0f, nullptr);
    state.setProperty("fmRatio", 6.0f, nullptr);
    state.setProperty("noiseLevel", 0.1f, nullptr);
    state.setProperty("subOscLevel", 0.0f, nullptr);
    
    return Preset("Distorted Lead", "Leads", state);
}

void PresetManager::savePreset(const juce::String& name, const juce::String& category, const juce::ValueTree& state)
{
    presets.push_back(Preset(name, category, state.createCopy()));
    savePresetsToFile();
}

bool PresetManager::loadPreset(int index, juce::ValueTree& outState)
{
    if (index >= 0 && index < static_cast<int>(presets.size()))
    {
        outState = presets[index].state.createCopy();
        return true;
    }
    return false;
}

bool PresetManager::loadPresetByName(const juce::String& name, juce::ValueTree& outState)
{
    for (const auto& preset : presets)
    {
        if (preset.name == name)
        {
            outState = preset.state.createCopy();
            return true;
        }
    }
    return false;
}

void PresetManager::deletePreset(int index)
{
    if (index >= 0 && index < static_cast<int>(presets.size()))
    {
        presets.erase(presets.begin() + index);
        savePresetsToFile();
    }
}

Preset PresetManager::getPreset(int index) const
{
    if (index >= 0 && index < static_cast<int>(presets.size()))
        return presets[index];
    return Preset();
}

juce::StringArray PresetManager::getPresetNames() const
{
    juce::StringArray names;
    for (const auto& preset : presets)
        names.add(preset.name);
    return names;
}

juce::StringArray PresetManager::getCategories() const
{
    juce::StringArray categories;
    for (const auto& preset : presets)
    {
        if (!categories.contains(preset.category))
            categories.add(preset.category);
    }
    return categories;
}

std::vector<Preset> PresetManager::getPresetsInCategory(const juce::String& category) const
{
    std::vector<Preset> filtered;
    for (const auto& preset : presets)
    {
        if (preset.category == category)
            filtered.push_back(preset);
    }
    return filtered;
}

juce::File PresetManager::getPresetsDirectory()
{
    auto appData = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);
    auto presetsDir = appData.getChildFile("Shoegazer").getChildFile("Presets");
    
    if (!presetsDir.exists())
        presetsDir.createDirectory();
    
    return presetsDir;
}

void PresetManager::savePresetsToFile()
{
    auto presetsFile = getPresetsDirectory().getChildFile("UserPresets.xml");
    
    juce::ValueTree root("Presets");
    for (const auto& preset : presets)
    {
        juce::ValueTree presetNode("Preset");
        presetNode.setProperty("name", preset.name, nullptr);
        presetNode.setProperty("category", preset.category, nullptr);
        presetNode.appendChild(preset.state.createCopy(), nullptr);
        root.appendChild(presetNode, nullptr);
    }
    
    if (auto xml = root.createXml())
        xml->writeToFile(presetsFile, {});
}

void PresetManager::loadPresetsFromFile()
{
    auto presetsFile = getPresetsDirectory().getChildFile("UserPresets.xml");
    
    if (presetsFile.existsAsFile())
    {
        if (auto xml = juce::parseXML(presetsFile))
        {
            auto root = juce::ValueTree::fromXml(*xml);
            if (root.isValid() && root.hasType("Presets"))
            {
                presets.clear();
                for (int i = 0; i < root.getNumChildren(); ++i)
                {
                    auto presetNode = root.getChild(i);
                    if (presetNode.hasType("Preset"))
                    {
                        auto name = presetNode.getProperty("name").toString();
                        auto category = presetNode.getProperty("category").toString();
                        auto state = presetNode.getChild(0);
                        
                        if (state.isValid())
                            presets.push_back(Preset(name, category, state));
                    }
                }
            }
        }
    }
}
