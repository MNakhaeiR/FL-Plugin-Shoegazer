#pragma once

#include <JuceHeader.h>
#include "DSP/ShoegazeVoice.h"
#include "DSP/ShoegazeSound.h"
#include "DSP/EffectsChain.h"

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

private:
    //==============================================================================
    juce::AudioProcessorValueTreeState apvts;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    juce::Synthesiser synthesiser;
    EffectsChain effectsChain;

    static constexpr int numVoices = 16;

    void updateSynthParameters();
    void updateEffectsParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShoegazerAudioProcessor)
};
