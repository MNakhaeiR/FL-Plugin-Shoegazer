#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Sample Player - Loads and plays audio samples for drums and guitars
 * Supports WAV, AIFF, FLAC, OGG formats
 */
class SamplePlayer : public juce::Synthesiser
{
public:
    SamplePlayer();
    ~SamplePlayer() override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    
    // Load sample from file
    bool loadSample(const juce::File& file, int midiNote = 60);
    bool loadSample(const void* data, size_t dataSize, const juce::String& name, int midiNote = 60);
    
    // Clear all samples
    void clearSamples();
    
    // Get info
    int getNumLoadedSamples() const { return loadedSamples.size(); }
    juce::String getSampleName(int index) const;
    
    // Load factory samples for shoegaze drums/guitars
    void loadFactorySamples();
    
private:
    juce::AudioFormatManager formatManager;
    juce::OwnedArray<juce::AudioFormatReaderSource> loadedSamples;
    juce::StringArray sampleNames;
    
    void addSampleToSynth(juce::AudioFormatReader* reader, int midiNote);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamplePlayer)
};
