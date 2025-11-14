#include "DrumSynthesizer.h"

DrumSynthesizer::DrumSynthesizer()
{
}

void DrumSynthesizer::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    currentSampleRate = sampleRate;
}

void DrumSynthesizer::triggerDrum(DrumType type, float velocity)
{
    currentDrum = type;
    currentVelocity = juce::jlimit(0.0f, 1.0f, velocity);
    envelope = 1.0f;
    phase = 0.0f;
    pitchEnvelope = 1.0f;
    
    // Set parameters based on drum type
    switch (type)
    {
        case Kick:
            frequency = kickPitch;
            envelopeDecay = 0.001f + (1.0f - kickDecay) * 0.005f;
            pitchEnvelopeDecay = 0.01f;
            noiseLevel = 0.05f;
            break;
            
        case Snare:
            frequency = 180.0f + snareTone * 120.0f;
            envelopeDecay = 0.002f;
            pitchEnvelopeDecay = 0.02f;
            noiseLevel = 0.6f + snareSnappy * 0.3f;
            break;
            
        case ClosedHat:
            frequency = 8000.0f + hatTone * 4000.0f;
            envelopeDecay = 0.003f + (1.0f - hatDecay) * 0.01f;
            noiseLevel = 1.0f;
            break;
            
        case OpenHat:
            frequency = 8000.0f + hatTone * 4000.0f;
            envelopeDecay = 0.001f;
            noiseLevel = 1.0f;
            break;
            
        case Tom:
            frequency = 120.0f;
            envelopeDecay = 0.0015f;
            pitchEnvelopeDecay = 0.015f;
            noiseLevel = 0.1f;
            break;
            
        case Crash:
            frequency = 3000.0f;
            envelopeDecay = 0.0003f;
            noiseLevel = 0.9f;
            break;
            
        case Rim:
            frequency = 400.0f;
            envelopeDecay = 0.01f;
            noiseLevel = 0.3f;
            break;
            
        case Clap:
            frequency = 1000.0f;
            envelopeDecay = 0.004f;
            noiseLevel = 0.8f;
            break;
    }
}

float DrumSynthesizer::getNextSample()
{
    if (envelope < 0.001f)
        return 0.0f;
    
    float output = 0.0f;
    
    switch (currentDrum)
    {
        case Kick:
            output = synthesizeKick();
            break;
        case Snare:
            output = synthesizeSnare();
            break;
        case ClosedHat:
            output = synthesizeHat(false);
            break;
        case OpenHat:
            output = synthesizeHat(true);
            break;
        case Tom:
            output = synthesizeTom();
            break;
        case Crash:
            output = synthesizeCrash();
            break;
        case Rim:
            output = synthesizeRim();
            break;
        case Clap:
            output = synthesizeClap();
            break;
    }
    
    // Apply envelope and velocity
    output *= envelope * currentVelocity;
    
    // Update envelopes
    envelope *= (1.0f - envelopeDecay);
    pitchEnvelope *= (1.0f - pitchEnvelopeDecay);
    
    return output * 0.5f; // Scale down to prevent clipping
}

float DrumSynthesizer::synthesizeKick()
{
    // Sine wave with pitch envelope for thump
    float currentFreq = frequency * (0.3f + pitchEnvelope * 0.7f);
    phase += currentFreq / static_cast<float>(currentSampleRate) * juce::MathConstants<float>::twoPi;
    
    if (phase >= juce::MathConstants<float>::twoPi)
        phase -= juce::MathConstants<float>::twoPi;
    
    float sine = std::sin(phase);
    
    // Add click
    float noise = (random.nextFloat() * 2.0f - 1.0f) * noiseLevel;
    float click = noise * pitchEnvelope * pitchEnvelope;
    
    return sine * 0.8f + click * 0.2f;
}

float DrumSynthesizer::synthesizeSnare()
{
    // Triangle wave for body
    float currentFreq = frequency * (0.5f + pitchEnvelope * 0.5f);
    phase += currentFreq / static_cast<float>(currentSampleRate) * juce::MathConstants<float>::twoPi;
    
    if (phase >= juce::MathConstants<float>::twoPi)
        phase -= juce::MathConstants<float>::twoPi;
    
    float triangle = 2.0f * std::abs(2.0f * (phase / juce::MathConstants<float>::twoPi - 0.5f)) - 1.0f;
    
    // White noise for snare
    float noise = (random.nextFloat() * 2.0f - 1.0f);
    
    // High-pass filter the noise
    static float lastNoise = 0.0f;
    float filteredNoise = noise - lastNoise * 0.95f;
    lastNoise = noise;
    
    return triangle * (1.0f - noiseLevel) + filteredNoise * noiseLevel;
}

float DrumSynthesizer::synthesizeHat(bool open)
{
    // High-frequency noise for hi-hats
    float noise = random.nextFloat() * 2.0f - 1.0f;
    
    // Band-pass filter
    static float bp1 = 0.0f, bp2 = 0.0f;
    float filtered = noise - bp1 * 0.7f;
    bp2 = bp1;
    bp1 = filtered;
    
    return (filtered - bp2 * 0.3f) * (open ? 0.7f : 1.0f);
}

float DrumSynthesizer::synthesizeTom()
{
    // Similar to kick but higher pitch
    float currentFreq = frequency * (0.5f + pitchEnvelope * 0.5f);
    phase += currentFreq / static_cast<float>(currentSampleRate) * juce::MathConstants<float>::twoPi;
    
    if (phase >= juce::MathConstants<float>::twoPi)
        phase -= juce::MathConstants<float>::twoPi;
    
    float sine = std::sin(phase);
    float noise = (random.nextFloat() * 2.0f - 1.0f) * noiseLevel;
    
    return sine * 0.9f + noise * 0.1f;
}

float DrumSynthesizer::synthesizeCrash()
{
    // Complex noise for crash
    float noise1 = random.nextFloat() * 2.0f - 1.0f;
    float noise2 = random.nextFloat() * 2.0f - 1.0f;
    
    // Ring modulation
    float modulated = noise1 * noise2;
    
    // Band-pass filter
    static float bp = 0.0f;
    float filtered = modulated - bp * 0.5f;
    bp = filtered;
    
    return filtered * noiseLevel;
}

float DrumSynthesizer::synthesizeRim()
{
    // Short metallic click
    float currentFreq = frequency * (0.8f + pitchEnvelope * 0.2f);
    phase += currentFreq / static_cast<float>(currentSampleRate) * juce::MathConstants<float>::twoPi;
    
    if (phase >= juce::MathConstants<float>::twoPi)
        phase -= juce::MathConstants<float>::twoPi;
    
    float sine = std::sin(phase);
    float noise = (random.nextFloat() * 2.0f - 1.0f) * noiseLevel;
    
    return sine * 0.3f + noise * 0.7f;
}

float DrumSynthesizer::synthesizeClap()
{
    // Multiple short bursts of noise
    float noise = random.nextFloat() * 2.0f - 1.0f;
    
    // Create burst effect
    float burstEnv = envelope > 0.95f || (envelope > 0.7f && envelope < 0.75f) || (envelope > 0.5f && envelope < 0.53f) ? 1.0f : 0.3f;
    
    return noise * noiseLevel * burstEnv;
}

void DrumSynthesizer::setKickPitch(float pitch)
{
    kickPitch = juce::jlimit(30.0f, 120.0f, pitch);
}

void DrumSynthesizer::setKickDecay(float decay)
{
    kickDecay = juce::jlimit(0.0f, 1.0f, decay);
}

void DrumSynthesizer::setSnareTone(float tone)
{
    snareTone = juce::jlimit(0.0f, 1.0f, tone);
}

void DrumSynthesizer::setSnareSnappy(float snappy)
{
    snareSnappy = juce::jlimit(0.0f, 1.0f, snappy);
}

void DrumSynthesizer::setHatTone(float tone)
{
    hatTone = juce::jlimit(0.0f, 1.0f, tone);
}

void DrumSynthesizer::setHatDecay(float decay)
{
    hatDecay = juce::jlimit(0.0f, 1.0f, decay);
}
