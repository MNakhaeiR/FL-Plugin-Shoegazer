#include "VisualizerComponent.h"
#include "ModernLookAndFeel.h"

VisualizerComponent::VisualizerComponent() : fft(fftOrder)
{
    waveformData.resize(512, 0.0f);
    spectrumData.resize(fftSize / 2, 0.0f);
    fftData.resize(fftSize * 2, 0.0f);

    startTimerHz(60);
}

VisualizerComponent::~VisualizerComponent()
{
    stopTimer();
}

void VisualizerComponent::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Background
    g.fillAll(ModernLookAndFeel::getBackgroundColor().darker(0.3f));

    // Waveform
    juce::Path waveformPath;
    waveformPath.startNewSubPath(0, bounds.getCentreY());

    for (int i = 0; i < waveformData.size(); ++i)
    {
        auto x = juce::jmap((float)i, 0.0f, (float)waveformData.size(), 0.0f, bounds.getWidth());
        auto y = juce::jmap(waveformData[i], -1.0f, 1.0f, bounds.getBottom(), bounds.getY());
        waveformPath.lineTo(x, y);
    }

    // Glowing waveform
    g.setColour(ModernLookAndFeel::getSecondaryColor().withAlpha(0.2f));
    g.strokePath(waveformPath, juce::PathStrokeType(3.0f), juce::AffineTransform());

    g.setColour(ModernLookAndFeel::getSecondaryColor().withAlpha(0.8f));
    g.strokePath(waveformPath, juce::PathStrokeType(1.5f), juce::AffineTransform());

    // Spectrum bars
    auto barWidth = bounds.getWidth() / 64.0f;
    for (int i = 0; i < 64; ++i)
    {
        auto specIndex = juce::jmap(i, 0, 64, 0, (int)spectrumData.size());
        auto level = juce::jlimit(0.0f, 1.0f, spectrumData[specIndex]);

        auto x = i * barWidth;
        auto barHeight = level * bounds.getHeight() * 0.8f;
        auto y = bounds.getBottom() - barHeight;

        // Gradient from bottom to top
        juce::ColourGradient barGradient(
            ModernLookAndFeel::getAccentColor().withAlpha(0.8f), x, bounds.getBottom(),
            ModernLookAndFeel::getPrimaryColor().withAlpha(0.8f), x, y,
            false);
        g.setGradientFill(barGradient);
        g.fillRect(x, y, barWidth - 1, barHeight);
    }

    // Animated glow overlay
    g.setColour(ModernLookAndFeel::getPrimaryColor().withAlpha(0.1f + 0.05f * std::sin(glowPhase)));
    g.fillAll();
}

void VisualizerComponent::resized()
{
}

void VisualizerComponent::timerCallback()
{
    glowPhase += 0.05f;
    if (glowPhase > juce::MathConstants<float>::twoPi)
        glowPhase -= juce::MathConstants<float>::twoPi;

    repaint();
}

void VisualizerComponent::pushBuffer(const juce::AudioBuffer<float> &buffer)
{
    if (buffer.getNumChannels() == 0)
        return;

    auto *channelData = buffer.getReadPointer(0);
    auto numSamples = buffer.getNumSamples();

    // Update waveform data
    for (int i = 0; i < numSamples && writePosition < waveformData.size(); ++i)
    {
        waveformData[writePosition++] = channelData[i];
        if (writePosition >= waveformData.size())
            writePosition = 0;
    }

    // Update FFT data
    if (numSamples >= fftSize)
    {
        std::fill(fftData.begin(), fftData.end(), 0.0f);
        std::copy(channelData, channelData + fftSize, fftData.begin());

        // Apply window
        juce::dsp::WindowingFunction<float> window(fftSize, juce::dsp::WindowingFunction<float>::hann);
        window.multiplyWithWindowingTable(fftData.data(), fftSize);

        // Perform FFT
        fft.performFrequencyOnlyForwardTransform(fftData.data());

        // Update spectrum data with smoothing
        for (int i = 0; i < spectrumData.size(); ++i)
        {
            auto newValue = fftData[i] / fftSize;
            spectrumData[i] = spectrumData[i] * 0.8f + newValue * 0.2f;
        }
    }
}
