#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ModernLookAndFeel.h"
#include "UI/CustomComponents.h"
#include "UI/VisualizerComponent.h"

//==============================================================================
/**
 * Shoegazer Plugin Editor - Stunning UI with animations
 */
class ShoegazerAudioProcessorEditor : public juce::AudioProcessorEditor,
                                      public juce::Timer
{
public:
    ShoegazerAudioProcessorEditor (ShoegazerAudioProcessor&);
    ~ShoegazerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    ShoegazerAudioProcessor& audioProcessor;
    ModernLookAndFeel modernLookAndFeel;
    
    // UI Components
    std::unique_ptr<GradientPanel> synthPanel;
    std::unique_ptr<GradientPanel> filterPanel;
    std::unique_ptr<GradientPanel> envelopePanel;
    std::unique_ptr<GradientPanel> effectsPanel;
    std::unique_ptr<GradientPanel> drumPanel;
    std::unique_ptr<VisualizerComponent> visualizer;
    
    // Preset browser
    std::unique_ptr<juce::ComboBox> presetCombo;
    std::unique_ptr<StyledLabel> presetLabel;
    
    // Oscillator controls
    std::unique_ptr<juce::ComboBox> osc1WaveCombo;
    std::unique_ptr<juce::ComboBox> osc2WaveCombo;
    std::unique_ptr<AnimatedSlider> detuneSlider;
    std::unique_ptr<AnimatedSlider> unisonSlider;
    
    std::unique_ptr<StyledLabel> osc1Label;
    std::unique_ptr<StyledLabel> osc2Label;
    std::unique_ptr<StyledLabel> detuneLabel;
    std::unique_ptr<StyledLabel> unisonLabel;
    
    // Filter controls
    std::unique_ptr<AnimatedSlider> cutoffSlider;
    std::unique_ptr<AnimatedSlider> resonanceSlider;
    std::unique_ptr<StyledLabel> cutoffLabel;
    std::unique_ptr<StyledLabel> resonanceLabel;
    
    // Envelope controls
    std::unique_ptr<AnimatedSlider> attackSlider;
    std::unique_ptr<AnimatedSlider> decaySlider;
    std::unique_ptr<AnimatedSlider> sustainSlider;
    std::unique_ptr<AnimatedSlider> releaseSlider;
    
    std::unique_ptr<StyledLabel> attackLabel;
    std::unique_ptr<StyledLabel> decayLabel;
    
    // Drum controls
    std::unique_ptr<AnimatedSlider> drumKickPitchSlider;
    std::unique_ptr<AnimatedSlider> drumKickDecaySlider;
    std::unique_ptr<AnimatedSlider> drumSnareToneSlider;
    std::unique_ptr<AnimatedSlider> drumSnareSnappySlider;
    std::unique_ptr<AnimatedSlider> drumHatToneSlider;
    std::unique_ptr<AnimatedSlider> drumHatDecaySlider;
    
    std::unique_ptr<StyledLabel> drumKickPitchLabel;
    std::unique_ptr<StyledLabel> drumKickDecayLabel;
    std::unique_ptr<StyledLabel> drumSnareToneLabel;
    std::unique_ptr<StyledLabel> drumSnareSnappyLabel;
    std::unique_ptr<StyledLabel> drumHatToneLabel;
    std::unique_ptr<StyledLabel> drumHatDecayLabel;
    std::unique_ptr<StyledLabel> sustainLabel;
    std::unique_ptr<StyledLabel> releaseLabel;
    
    // Effects controls
    std::unique_ptr<AnimatedSlider> reverbSizeSlider;
    std::unique_ptr<AnimatedSlider> reverbWetSlider;
    std::unique_ptr<AnimatedSlider> chorusMixSlider;
    std::unique_ptr<AnimatedSlider> delayTimeSlider;
    std::unique_ptr<AnimatedSlider> delayMixSlider;
    std::unique_ptr<AnimatedSlider> masterVolumeSlider;
    
    std::unique_ptr<StyledLabel> reverbSizeLabel;
    std::unique_ptr<StyledLabel> reverbWetLabel;
    std::unique_ptr<StyledLabel> chorusMixLabel;
    std::unique_ptr<StyledLabel> delayTimeLabel;
    std::unique_ptr<StyledLabel> delayMixLabel;
    std::unique_ptr<StyledLabel> masterVolumeLabel;
    
    // Attachments
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> comboAttachments;
    
    // Animation
    float backgroundAnimation = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShoegazerAudioProcessorEditor)
};
