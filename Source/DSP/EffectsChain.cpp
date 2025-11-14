#include "EffectsChain.h"

EffectsChain::EffectsChain()
{
    // Initialize reverb with shoegaze-friendly settings
    reverbParams.roomSize = 0.8f;
    reverbParams.damping = 0.5f;
    reverbParams.wetLevel = 0.4f;
    reverbParams.dryLevel = 0.6f;
    reverbParams.width = 1.0f;
    reverbParams.freezeMode = 0.0f;
    reverb.setParameters(reverbParams);
}

void EffectsChain::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;

    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;

    // Prepare chorus
    chorus.prepare(spec);
    chorus.setRate(1.5f);
    chorus.setDepth(0.5f);
    chorus.setFeedback(0.3f);
    chorus.setCentreDelay(7.0f);
    chorus.setMix(chorusMix);

    // Prepare delay
    maxDelayInSamples = static_cast<int>(sampleRate * 2.0); // 2 seconds max
    delayLine.prepare(spec);
    delayLine.setMaximumDelayInSamples(maxDelayInSamples);
    delayLine.setDelay(delayTimeMs * 0.001f * static_cast<float>(sampleRate));
    delayBuffer.resize(samplesPerBlock);

    // Prepare wave shaper for distortion
    waveShaper.prepare(spec);
    waveShaper.functionToUse = [](float x)
    {
        return std::tanh(x * 2.0f) * 0.5f;
    };

    // Prepare buffers
    dryBuffer.setSize(2, samplesPerBlock);
    wetBuffer.setSize(2, samplesPerBlock);

    reset();
}

void EffectsChain::reset()
{
    reverb.reset();
    chorus.reset();
    delayLine.reset();
    waveShaper.reset();
}

void EffectsChain::processBlock(juce::AudioBuffer<float> &buffer)
{
    const int numSamples = buffer.getNumSamples();
    const int numChannels = buffer.getNumChannels();

    // Store dry signal
    dryBuffer.makeCopyOf(buffer);

    // Process Distortion (if enabled)
    if (distortionEnabled && distortionAmount > 0.01f)
    {
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);

        // Apply gain before distortion
        float preGain = 1.0f + distortionAmount * 5.0f;
        block.multiplyBy(preGain);

        waveShaper.process(context);

        // Apply mix
        for (int ch = 0; ch < numChannels; ++ch)
        {
            auto *channelData = buffer.getWritePointer(ch);
            auto *dryData = dryBuffer.getReadPointer(ch);

            for (int i = 0; i < numSamples; ++i)
            {
                channelData[i] = dryData[i] * (1.0f - distortionMix) +
                                 channelData[i] * distortionMix;
            }
        }
    }

    // Process Chorus (if enabled)
    if (chorusEnabled)
    {
        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        chorus.process(context);
    }

    // Process Delay (if enabled)
    if (delayEnabled && delayMix > 0.01f)
    {
        for (int ch = 0; ch < numChannels; ++ch)
        {
            auto *channelData = buffer.getWritePointer(ch);

            for (int i = 0; i < numSamples; ++i)
            {
                // Read delayed sample
                float delayedSample = delayLine.popSample(ch);

                // Mix with input and feedback
                float inputSample = channelData[i];
                float outputSample = inputSample + delayedSample * delayFeedback;

                // Push to delay line
                delayLine.pushSample(ch, outputSample);

                // Mix dry and wet
                channelData[i] = inputSample * (1.0f - delayMix) +
                                 delayedSample * delayMix;
            }
        }
    }

    // Process Reverb (if enabled) - Always last for maximum dreamy effect
    if (reverbEnabled)
    {
        if (numChannels == 1)
        {
            reverb.processMono(buffer.getWritePointer(0), numSamples);
        }
        else if (numChannels == 2)
        {
            reverb.processStereo(buffer.getWritePointer(0),
                                 buffer.getWritePointer(1),
                                 numSamples);
        }
    }
}

void EffectsChain::setReverbSize(float size)
{
    reverbParams.roomSize = juce::jlimit(0.0f, 1.0f, size);
    reverb.setParameters(reverbParams);
}

void EffectsChain::setReverbDamping(float damping)
{
    reverbParams.damping = juce::jlimit(0.0f, 1.0f, damping);
    reverb.setParameters(reverbParams);
}

void EffectsChain::setReverbWetLevel(float wet)
{
    reverbParams.wetLevel = juce::jlimit(0.0f, 1.0f, wet);
    reverb.setParameters(reverbParams);
}

void EffectsChain::setReverbWidth(float width)
{
    reverbParams.width = juce::jlimit(0.0f, 1.0f, width);
    reverb.setParameters(reverbParams);
}

void EffectsChain::setChorusRate(float rate)
{
    chorus.setRate(juce::jlimit(0.1f, 10.0f, rate));
}

void EffectsChain::setChorusDepth(float depth)
{
    chorus.setDepth(juce::jlimit(0.0f, 1.0f, depth));
}

void EffectsChain::setChorusFeedback(float feedback)
{
    chorus.setFeedback(juce::jlimit(0.0f, 0.95f, feedback));
}

void EffectsChain::setChorusMix(float mix)
{
    chorusMix = juce::jlimit(0.0f, 1.0f, mix);
    chorus.setMix(chorusMix);
}

void EffectsChain::setDelayTime(float timeMs)
{
    delayTimeMs = juce::jlimit(10.0f, 2000.0f, timeMs);
    float delaySamples = delayTimeMs * 0.001f * static_cast<float>(currentSampleRate);
    delayLine.setDelay(juce::jmin(delaySamples, (float)maxDelayInSamples));
}

void EffectsChain::setDelayFeedback(float feedback)
{
    delayFeedback = juce::jlimit(0.0f, 0.95f, feedback);
}

void EffectsChain::setDelayMix(float mix)
{
    delayMix = juce::jlimit(0.0f, 1.0f, mix);
}

void EffectsChain::setDistortionAmount(float amount)
{
    distortionAmount = juce::jlimit(0.0f, 1.0f, amount);
}

void EffectsChain::setDistortionMix(float mix)
{
    distortionMix = juce::jlimit(0.0f, 1.0f, mix);
}

void EffectsChain::setEffectEnabled(int effectIndex, bool enabled)
{
    switch (effectIndex)
    {
    case 0:
        reverbEnabled = enabled;
        break;
    case 1:
        chorusEnabled = enabled;
        break;
    case 2:
        delayEnabled = enabled;
        break;
    case 3:
        distortionEnabled = enabled;
        break;
    default:
        break;
    }
}
