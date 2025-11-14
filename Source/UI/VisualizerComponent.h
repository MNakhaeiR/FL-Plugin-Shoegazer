#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Audio Visualizer Component
 * Displays waveform and spectrum analyzer
 */
class VisualizerComponent : public juce::Component,
                            public juce::Timer
{
public:
    VisualizerComponent();
    ~VisualizerComponent() override;
    
    void paint (juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;
    
    void pushBuffer (const juce::AudioBuffer<float>& buffer);
    
private:
    std::vector<float> waveformData;
    std::vector<float> spectrumData;
    
    juce::dsp::FFT fft;
    std::vector<float> fftData;
    
    static constexpr int fftOrder = 10;
    static constexpr int fftSize = 1 << fftOrder;
    
    int writePosition = 0;
    float glowPhase = 0.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualizerComponent)
};
