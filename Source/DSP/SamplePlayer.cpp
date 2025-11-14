#include "SamplePlayer.h"

SamplePlayer::SamplePlayer()
{
    // Register audio formats
    formatManager.registerBasicFormats();
    
    // Add voices
    for (int i = 0; i < 16; ++i)
        addVoice(new juce::SamplerVoice());
}

SamplePlayer::~SamplePlayer()
{
    clearSamples();
}

void SamplePlayer::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    setCurrentPlaybackSampleRate(sampleRate);
}

bool SamplePlayer::loadSample(const juce::File& file, int midiNote)
{
    if (!file.existsAsFile())
        return false;
    
    auto* reader = formatManager.createReaderFor(file);
    if (reader == nullptr)
        return false;
    
    sampleNames.add(file.getFileNameWithoutExtension());
    addSampleToSynth(reader, midiNote);
    
    return true;
}

bool SamplePlayer::loadSample(const void* data, size_t dataSize, const juce::String& name, int midiNote)
{
    juce::MemoryInputStream inputStream(data, dataSize, false);
    auto* reader = formatManager.createReaderFor(std::make_unique<juce::MemoryInputStream>(data, dataSize, false));
    
    if (reader == nullptr)
        return false;
    
    sampleNames.add(name);
    addSampleToSynth(reader, midiNote);
    
    return true;
}

void SamplePlayer::addSampleToSynth(juce::AudioFormatReader* reader, int midiNote)
{
    juce::BigInteger allNotes;
    allNotes.setRange(midiNote, 1, true);
    
    auto sound = new juce::SamplerSound(
        sampleNames[sampleNames.size() - 1],
        *reader,
        allNotes,
        midiNote,  // root note
        0.01,      // attack time
        0.1,       // release time
        10.0       // maximum sample length
    );
    
    addSound(sound);
    
    delete reader;
}

void SamplePlayer::clearSamples()
{
    clearSounds();
    sampleNames.clear();
    loadedSamples.clear();
}

juce::String SamplePlayer::getSampleName(int index) const
{
    if (index >= 0 && index < sampleNames.size())
        return sampleNames[index];
    return {};
}

void SamplePlayer::loadFactorySamples()
{
    // This would load embedded samples or samples from a default location
    // For now, we'll just set up the player to be ready for user samples
    
    // In a full implementation, you could embed samples using BinaryData
    // or load from a Resources folder
    
    DBG("SamplePlayer: Ready for samples. Use loadSample() to add drums/guitars.");
}
