#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Wavetable Oscillator with morphing capabilities
 * Creates rich harmonic content for shoegaze-style sounds
 */
class WavetableOscillator
{
public:
    WavetableOscillator();
    
    void prepareToPlay (double sampleRate);
    void setFrequency (float frequency);
    void setWaveform (int waveformType); // 0=Sine, 1=Saw, 2=Square, 3=Triangle, 4=Custom
    void setDetune (float detuneAmount);
    void setUnison (int voiceCount);
    
    float getNextSample();
    
private:
    void generateWavetable (int type);
    
    std::vector<float> wavetable;
    float phase = 0.0f;
    float phaseDelta = 0.0f;
    float currentFrequency = 440.0f;
    double currentSampleRate = 44100.0;
    
    int unisonVoices = 1;
    float detuneAmount = 0.0f;
    std::vector<float> unisonPhases;
    std::vector<float> unisonDetunes;
    
    static constexpr int wavetableSize = 2048;
};
