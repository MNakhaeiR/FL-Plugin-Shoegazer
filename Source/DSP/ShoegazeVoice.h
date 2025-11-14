#pragma once

#include <JuceHeader.h>
#include "ShoegazeSound.h"
#include "WavetableOscillator.h"

//==============================================================================
/**
 * ShoegazeVoice - Individual voice for polyphonic synthesis
 * Features dual oscillators, filter, and envelope
 */
class ShoegazeVoice : public juce::SynthesiserVoice
{
public:
    ShoegazeVoice();
    ~ShoegazeVoice() override = default;

    bool canPlaySound(juce::SynthesiserSound *sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *, int) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newValue) override;
    void controllerMoved(int controllerNumber, int newValue) override;
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock);

    // Parameter setters
    void setOscillatorWaveform(int oscIndex, int waveform);
    void setOscillatorDetune(float detune);
    void setOscillatorUnison(int voices);
    void setFilterCutoff(float cutoff);
    void setFilterResonance(float resonance);
    void setAttack(float attack);
    void setDecay(float decay);
    void setSustain(float sustain);
    void setRelease(float release);

private:
    WavetableOscillator osc1, osc2;
    juce::ADSR envelope;
    juce::ADSR::Parameters envelopeParams;
    
    juce::dsp::StateVariableTPTFilter<float> filter;    double currentSampleRate = 44100.0;
    int currentMidiNote = 0;
    float currentVelocity = 0.0f;
    float pitchBend = 0.0f;

    float filterCutoffFreq = 2000.0f;
    float filterResonanceValue = 0.7f;
};
