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
    
    for (int i = 0; i < unisonVoices; ++i)
    {
        // Linear interpolation for smooth playback
        int index0 = (int) unisonPhases[i] % wavetableSize;
        int index1 = (index0 + 1) % wavetableSize;
        float frac = unisonPhases[i] - (int) unisonPhases[i];
        
        float sample = wavetable[index0] + frac * (wavetable[index1] - wavetable[index0]);
        output += sample;
        
        // Advance phase with detune
        float detunedDelta = phaseDelta * std::pow (2.0f, unisonDetunes[i] / 12.0f);
        unisonPhases[i] += detunedDelta;
        
        if (unisonPhases[i] >= wavetableSize)
            unisonPhases[i] -= wavetableSize;
    }
    
    return output / (float) unisonVoices; // Normalize
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
