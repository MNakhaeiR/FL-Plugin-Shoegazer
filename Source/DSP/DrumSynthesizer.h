#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Drum Synthesizer - Synthesized drum sounds for shoegaze
 * Includes kick, snare, hi-hat, tom, and cymbal synthesis
 */
class DrumSynthesizer
{
public:
    enum DrumType
    {
        Kick = 0,
        Snare,
        ClosedHat,
        OpenHat,
        Tom,
        Crash,
        Rim,
        Clap
    };
    
    DrumSynthesizer();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void triggerDrum(DrumType type, float velocity);
    float getNextSample();
    bool isActive() const { return envelope > 0.001f; }
    
    // Parameters for each drum type
    void setKickPitch(float pitch);
    void setKickDecay(float decay);
    void setSnareTone(float tone);
    void setSnareSnappy(float snappy);
    void setHatTone(float tone);
    void setHatDecay(float decay);
    
private:
    double currentSampleRate = 44100.0;
    
    // Envelope
    float envelope = 0.0f;
    float envelopeDecay = 0.0f;
    
    // Oscillators for synthesis
    float phase = 0.0f;
    float frequency = 0.0f;
    float pitchEnvelope = 0.0f;
    float pitchEnvelopeDecay = 0.0f;
    
    // Noise generator
    juce::Random random;
    float noiseLevel = 0.0f;
    
    // Current drum parameters
    DrumType currentDrum = Kick;
    float currentVelocity = 1.0f;
    
    // User parameters
    float kickPitch = 60.0f;
    float kickDecay = 0.3f;
    float snareTone = 0.5f;
    float snareSnappy = 0.7f;
    float hatTone = 0.8f;
    float hatDecay = 0.15f;
    
    // Synthesis methods
    float synthesizeKick();
    float synthesizeSnare();
    float synthesizeHat(bool open);
    float synthesizeTom();
    float synthesizeCrash();
    float synthesizeRim();
    float synthesizeClap();
};
