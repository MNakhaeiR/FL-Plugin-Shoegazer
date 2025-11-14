#include "WavetableOscillator.h"

WavetableOscillator::WavetableOscillator()
{
    wavetable.resize (wavetableSize);
    generateWavetable (0); // Start with sine wave
}

void WavetableOscillator::prepareToPlay (double sampleRate)
{
    currentSampleRate = sampleRate;
    phase = 0.0f;
}

void WavetableOscillator::setFrequency (float frequency)
{
    currentFrequency = frequency;
    phaseDelta = (float) (frequency / currentSampleRate * wavetableSize);
}

void WavetableOscillator::setWaveform (int waveformType)
{
    generateWavetable (waveformType);
}

void WavetableOscillator::setDetune (float detune)
{
    detuneAmount = detune;
}

void WavetableOscillator::setUnison (int voiceCount)
{
    unisonVoices = juce::jlimit (1, 8, voiceCount);
    unisonPhases.resize (unisonVoices);
    unisonDetunes.resize (unisonVoices);
    
    // Initialize unison voices with spread
    for (int i = 0; i < unisonVoices; ++i)
    {
        unisonPhases[i] = 0.0f;
        float spread = (float) i / (float) unisonVoices - 0.5f;
        unisonDetunes[i] = spread * detuneAmount;
    }
}

float WavetableOscillator::getNextSample()
{
    float output = 0.0f;
    
    // FM modulator
    float fmMod = 0.0f;
    if (fmAmount > 0.0f)
    {
        fmMod = std::sin(fmPhase) * fmAmount * currentFrequency;
        fmPhase += (currentFrequency * fmRatio * 2.0f * juce::MathConstants<float>::pi) / (float)currentSampleRate;
        if (fmPhase >= juce::MathConstants<float>::twoPi)
            fmPhase -= juce::MathConstants<float>::twoPi;
    }
    
    for (int i = 0; i < unisonVoices; ++i)
    {
        // Linear interpolation for smooth playback with FM
        float modulatedPhase = unisonPhases[i] + fmMod;
        int index0 = ((int) modulatedPhase) % wavetableSize;
        if (index0 < 0) index0 += wavetableSize;
        int index1 = (index0 + 1) % wavetableSize;
        float frac = modulatedPhase - std::floor(modulatedPhase);
        
        float sample = wavetable[index0] + frac * (wavetable[index1] - wavetable[index0]);
        output += sample;
        
        // Advance phase with detune
        float detunedDelta = phaseDelta * std::pow (2.0f, unisonDetunes[i] / 12.0f);
        unisonPhases[i] += detunedDelta;
        
        if (unisonPhases[i] >= wavetableSize)
            unisonPhases[i] -= wavetableSize;
    }
    
    output /= (float) unisonVoices; // Normalize
    
    // Add sub-oscillator (one octave down)
    if (subOscLevel > 0.0f)
    {
        float subSample = std::sin(subPhase);
        output += subSample * subOscLevel;
        
        subPhase += phaseDelta * 0.5f; // One octave down
        if (subPhase >= wavetableSize)
            subPhase -= wavetableSize;
    }
    
    // Add noise
    if (noiseLevel > 0.0f)
    {
        float noise = (noiseGen.nextFloat() * 2.0f - 1.0f) * noiseLevel;
        output += noise * 0.3f; // Scaled for mix
    }
    
    return output;
}

void WavetableOscillator::generateWavetable (int type)
{
    switch (type)
    {
        case 0: // Sine
            for (int i = 0; i < wavetableSize; ++i)
                wavetable[i] = std::sin (2.0f * juce::MathConstants<float>::pi * i / wavetableSize);
            break;
            
        case 1: // Saw
            for (int i = 0; i < wavetableSize; ++i)
                wavetable[i] = 2.0f * (float) i / wavetableSize - 1.0f;
            break;
            
        case 2: // Square
            for (int i = 0; i < wavetableSize; ++i)
                wavetable[i] = i < wavetableSize / 2 ? 1.0f : -1.0f;
            break;
            
        case 3: // Triangle
            for (int i = 0; i < wavetableSize; ++i)
            {
                float phase = (float) i / wavetableSize;
                if (phase < 0.25f)
                    wavetable[i] = 4.0f * phase;
                else if (phase < 0.75f)
                    wavetable[i] = 2.0f - 4.0f * phase;
                else
                    wavetable[i] = 4.0f * phase - 4.0f;
            }
            break;
            
        case 4: // Rich harmonic content for shoegaze
            for (int i = 0; i < wavetableSize; ++i)
            {
                float phase = 2.0f * juce::MathConstants<float>::pi * i / wavetableSize;
                wavetable[i] = std::sin (phase) * 0.6f +
                              std::sin (2.0f * phase) * 0.3f +
                              std::sin (3.0f * phase) * 0.15f +
                              std::sin (5.0f * phase) * 0.1f;
            }
            break;
    }
}

void WavetableOscillator::setFMAmount(float amount)
{
    fmAmount = juce::jlimit(0.0f, 10.0f, amount);
}

void WavetableOscillator::setFMRatio(float ratio)
{
    fmRatio = juce::jlimit(0.5f, 8.0f, ratio);
}

void WavetableOscillator::setNoiseLevel(float level)
{
    noiseLevel = juce::jlimit(0.0f, 1.0f, level);
}

void WavetableOscillator::setSubOscLevel(float level)
{
    subOscLevel = juce::jlimit(0.0f, 1.0f, level);
}
