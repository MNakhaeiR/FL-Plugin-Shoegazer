#include "ShoegazeVoice.h"

ShoegazeVoice::ShoegazeVoice()
{
    envelopeParams.attack = 0.1f;
    envelopeParams.decay = 0.3f;
    envelopeParams.sustain = 0.7f;
    envelopeParams.release = 0.5f;
    envelope.setParameters(envelopeParams);
}

void ShoegazeVoice::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    currentSampleRate = sampleRate;

    osc1.prepareToPlay(sampleRate);
    osc2.prepareToPlay(sampleRate);
    envelope.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;

    filter.prepare(spec);
    filter.reset();
    filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    filter.setCutoffFrequency(filterCutoffFreq);
    filter.setResonance(filterResonanceValue);
}

bool ShoegazeVoice::canPlaySound(juce::SynthesiserSound *sound)
{
    return dynamic_cast<ShoegazeSound *>(sound) != nullptr;
}

void ShoegazeVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *, int)
{
    currentMidiNote = midiNoteNumber;
    currentVelocity = velocity;

    float frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    osc1.setFrequency(frequency);
    osc2.setFrequency(frequency);

    envelope.noteOn();
}

void ShoegazeVoice::stopNote(float velocity, bool allowTailOff)
{
    juce::ignoreUnused(velocity);

    if (allowTailOff)
        envelope.noteOff();
    else
        clearCurrentNote();
}

void ShoegazeVoice::pitchWheelMoved(int newValue)
{
    pitchBend = (float)(newValue - 8192) / 8192.0f;
}

void ShoegazeVoice::controllerMoved(int controllerNumber, int newValue)
{
    juce::ignoreUnused(controllerNumber, newValue);
}

void ShoegazeVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;

    for (int sample = 0; sample < numSamples; ++sample)
    {
        // Generate oscillator mix
        float osc1Sample = osc1.getNextSample();
        float osc2Sample = osc2.getNextSample();
        float mixedSample = (osc1Sample + osc2Sample) * 0.5f;

        // Apply envelope
        float envelopeValue = envelope.getNextSample();
        float outputSample = mixedSample * envelopeValue * currentVelocity;

        // Apply to all output channels
        for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
        {
            outputBuffer.addSample(channel, startSample + sample, outputSample);
        }

        // Check if note should stop
        if (!envelope.isActive())
            clearCurrentNote();
    }

    // Apply filter (process mono for now)
    if (outputBuffer.getNumChannels() > 0)
    {
        for (int ch = 0; ch < outputBuffer.getNumChannels(); ++ch)
        {
            for (int i = 0; i < numSamples; ++i)
            {
                float sample = outputBuffer.getSample(ch, startSample + i);
                float filtered = filter.processSample(ch, sample);
                outputBuffer.setSample(ch, startSample + i, filtered);
            }
        }
    }
}

void ShoegazeVoice::setOscillatorWaveform(int oscIndex, int waveform)
{
    if (oscIndex == 0)
        osc1.setWaveform(waveform);
    else if (oscIndex == 1)
        osc2.setWaveform(waveform);
}

void ShoegazeVoice::setOscillatorDetune(float detune)
{
    osc1.setDetune(detune);
    osc2.setDetune(detune);
}

void ShoegazeVoice::setOscillatorUnison(int voices)
{
    osc1.setUnison(voices);
    osc2.setUnison(voices);
}

void ShoegazeVoice::setFilterCutoff(float cutoff)
{
    filterCutoffFreq = cutoff;
    filter.setCutoffFrequency(cutoff);
}

void ShoegazeVoice::setFilterResonance(float resonance)
{
    filterResonanceValue = resonance;
    filter.setResonance(resonance);
}

void ShoegazeVoice::setAttack(float attack)
{
    envelopeParams.attack = attack;
    envelope.setParameters(envelopeParams);
}

void ShoegazeVoice::setDecay(float decay)
{
    envelopeParams.decay = decay;
    envelope.setParameters(envelopeParams);
}

void ShoegazeVoice::setSustain(float sustain)
{
    envelopeParams.sustain = sustain;
    envelope.setParameters(envelopeParams);
}

void ShoegazeVoice::setRelease(float release)
{
    envelopeParams.release = release;
    envelope.setParameters(envelopeParams);
}
