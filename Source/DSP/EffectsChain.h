#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * EffectsChain - Shoegaze-style effects processing
 * Includes reverb, chorus, delay, and distortion
 */
class EffectsChain
{
public:
    EffectsChain();

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void reset();
    void processBlock(juce::AudioBuffer<float> &buffer);

    // Effect parameters
    void setReverbSize(float size);
    void setReverbDamping(float damping);
    void setReverbWetLevel(float wet);
    void setReverbWidth(float width);

    void setChorusRate(float rate);
    void setChorusDepth(float depth);
    void setChorusFeedback(float feedback);
    void setChorusMix(float mix);

    void setDelayTime(float timeMs);
    void setDelayFeedback(float feedback);
    void setDelayMix(float mix);

    void setDistortionAmount(float amount);
    void setDistortionMix(float mix);

    void setEffectEnabled(int effectIndex, bool enabled);

private:
    // Reverb
    juce::Reverb reverb;
    juce::Reverb::Parameters reverbParams;
    bool reverbEnabled = true;

    // Chorus
    juce::dsp::Chorus<float> chorus;
    float chorusMix = 0.3f;
    bool chorusEnabled = true;

    // Delay
    juce::dsp::DelayLine<float> delayLine;
    float delayTimeMs = 250.0f;
    float delayFeedback = 0.5f;
    float delayMix = 0.4f;
    bool delayEnabled = true;
    std::vector<float> delayBuffer;

    // Distortion/Saturation
    juce::dsp::WaveShaper<float> waveShaper;
    float distortionAmount = 0.0f;
    float distortionMix = 0.0f;
    bool distortionEnabled = false;

    double currentSampleRate = 44100.0;
    int maxDelayInSamples = 0;

    // Helper buffers
    juce::AudioBuffer<float> dryBuffer;
    juce::AudioBuffer<float> wetBuffer;
};
