#pragma once

#include <JuceHeader.h>
#include "DSP/ShoegazeVoice.h"
#include "DSP/ShoegazeSound.h"
#include "DSP/EffectsChain.h"
#include "DSP/PresetManager.h"
#include "DSP/DrumSynthesizer.h"
#include "DSP/SamplePlayer.h"

//==============================================================================
/**
 * Shoegazer Plugin Processor
 * Main audio processing class combining synth and effects
 */
class ShoegazerAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    ShoegazerAudioProcessor();
    ~ShoegazerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    //==============================================================================
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    //==============================================================================
    // Access to parameters
    juce::AudioProcessorValueTreeState &getAPVTS() { return apvts; }

    // Parameter IDs
    static constexpr const char *OSC1_WAVE_ID = "osc1Wave";
    static constexpr const char *OSC2_WAVE_ID = "osc2Wave";
    static constexpr const char *OSC_DETUNE_ID = "oscDetune";
    static constexpr const char *OSC_UNISON_ID = "oscUnison";
    static constexpr const char *FM_AMOUNT_ID = "fmAmount";
    static constexpr const char *FM_RATIO_ID = "fmRatio";
    static constexpr const char *NOISE_LEVEL_ID = "noiseLevel";
    static constexpr const char *SUB_OSC_LEVEL_ID = "subOscLevel";

    static constexpr const char *FILTER_CUTOFF_ID = "filterCutoff";
    static constexpr const char *FILTER_RESONANCE_ID = "filterResonance";

    static constexpr const char *ENV_ATTACK_ID = "envAttack";
    static constexpr const char *ENV_DECAY_ID = "envDecay";
    static constexpr const char *ENV_SUSTAIN_ID = "envSustain";
    static constexpr const char *ENV_RELEASE_ID = "envRelease";

    static constexpr const char *REVERB_SIZE_ID = "reverbSize";
    static constexpr const char *REVERB_DAMPING_ID = "reverbDamping";
    static constexpr const char *REVERB_WET_ID = "reverbWet";
    static constexpr const char *REVERB_WIDTH_ID = "reverbWidth";

    static constexpr const char *CHORUS_RATE_ID = "chorusRate";
    static constexpr const char *CHORUS_DEPTH_ID = "chorusDepth";
    static constexpr const char *CHORUS_FEEDBACK_ID = "chorusFeedback";
    static constexpr const char *CHORUS_MIX_ID = "chorusMix";

    static constexpr const char *DELAY_TIME_ID = "delayTime";
    static constexpr const char *DELAY_FEEDBACK_ID = "delayFeedback";
    static constexpr const char *DELAY_MIX_ID = "delayMix";

    static constexpr const char *DIST_AMOUNT_ID = "distAmount";
    static constexpr const char *DIST_MIX_ID = "distMix";

    static constexpr const char *MASTER_VOLUME_ID = "masterVolume";
    
    // Drum parameters
    static constexpr const char *DRUM_KICK_PITCH_ID = "drumKickPitch";
    static constexpr const char *DRUM_KICK_DECAY_ID = "drumKickDecay";
    static constexpr const char *DRUM_SNARE_TONE_ID = "drumSnareTone";
    static constexpr const char *DRUM_SNARE_SNAPPY_ID = "drumSnareSnappy";
    static constexpr const char *DRUM_HAT_TONE_ID = "drumHatTone";
    static constexpr const char *DRUM_HAT_DECAY_ID = "drumHatDecay";
    
    // Preset management
    void loadPreset(int presetIndex);
    juce::String getCurrentPresetName() const { return currentPresetName; }
    int getNumPresets() const;
    juce::StringArray getPresetNames() const;

private:
    //==============================================================================
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    juce::Synthesiser synthesiser;
    EffectsChain effectsChain;
    PresetManager presetManager;
    SamplePlayer samplePlayer;
    
    // Drum synthesizers (polyphonic)
    juce::OwnedArray<DrumSynthesizer> drumVoices;
    static constexpr int numDrumVoices = 8;
    
    juce::String currentPresetName = "Default";

    static constexpr int numVoices = 16;

    void updateSynthParameters();
    void updateEffectsParameters();
    void updateDrumParameters();
    void triggerDrum(int midiNote, float velocity);
    DrumSynthesizer::DrumType getDrumTypeFromMidiNote(int midiNote);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShoegazerAudioProcessor)
};
