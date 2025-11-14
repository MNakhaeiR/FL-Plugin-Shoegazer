#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ShoegazerAudioProcessorEditor::ShoegazerAudioProcessorEditor (ShoegazerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel (&modernLookAndFeel);
    
    // Create panels
    synthPanel = std::make_unique<GradientPanel> ("SYNTHESIZER");
    addAndMakeVisible (synthPanel.get());
    
    filterPanel = std::make_unique<GradientPanel> ("FILTER");
    addAndMakeVisible (filterPanel.get());
    
    envelopePanel = std::make_unique<GradientPanel> ("ENVELOPE");
    addAndMakeVisible (envelopePanel.get());
    
    effectsPanel = std::make_unique<GradientPanel> ("EFFECTS");
    addAndMakeVisible (effectsPanel.get());
    
    visualizer = std::make_unique<VisualizerComponent>();
    addAndMakeVisible (visualizer.get());
    
    // Oscillator controls
    osc1WaveCombo = std::make_unique<juce::ComboBox>();
    osc1WaveCombo->addItem ("Sine", 1);
    osc1WaveCombo->addItem ("Saw", 2);
    osc1WaveCombo->addItem ("Square", 3);
    osc1WaveCombo->addItem ("Triangle", 4);
    osc1WaveCombo->addItem ("Rich", 5);
    addAndMakeVisible (osc1WaveCombo.get());
    comboAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::OSC1_WAVE_ID, *osc1WaveCombo));
    
    osc2WaveCombo = std::make_unique<juce::ComboBox>();
    osc2WaveCombo->addItem ("Sine", 1);
    osc2WaveCombo->addItem ("Saw", 2);
    osc2WaveCombo->addItem ("Square", 3);
    osc2WaveCombo->addItem ("Triangle", 4);
    osc2WaveCombo->addItem ("Rich", 5);
    addAndMakeVisible (osc2WaveCombo.get());
    comboAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::OSC2_WAVE_ID, *osc2WaveCombo));
    
    detuneSlider = std::make_unique<AnimatedSlider>();
    detuneSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    detuneSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible (detuneSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::OSC_DETUNE_ID, *detuneSlider));
    
    unisonSlider = std::make_unique<AnimatedSlider>();
    unisonSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    unisonSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible (unisonSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::OSC_UNISON_ID, *unisonSlider));
    
    osc1Label = std::make_unique<StyledLabel> ("OSC 1");
    addAndMakeVisible (osc1Label.get());
    
    osc2Label = std::make_unique<StyledLabel> ("OSC 2");
    addAndMakeVisible (osc2Label.get());
    
    detuneLabel = std::make_unique<StyledLabel> ("DETUNE");
    addAndMakeVisible (detuneLabel.get());
    
    unisonLabel = std::make_unique<StyledLabel> ("UNISON");
    addAndMakeVisible (unisonLabel.get());
    
    // Filter controls
    cutoffSlider = std::make_unique<AnimatedSlider>();
    cutoffSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    cutoffSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible (cutoffSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::FILTER_CUTOFF_ID, *cutoffSlider));
    
    resonanceSlider = std::make_unique<AnimatedSlider>();
    resonanceSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    resonanceSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible (resonanceSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::FILTER_RESONANCE_ID, *resonanceSlider));
    
    cutoffLabel = std::make_unique<StyledLabel> ("CUTOFF");
    addAndMakeVisible (cutoffLabel.get());
    
    resonanceLabel = std::make_unique<StyledLabel> ("RESONANCE");
    addAndMakeVisible (resonanceLabel.get());
    
    // Envelope controls
    attackSlider = std::make_unique<AnimatedSlider>();
    attackSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    attackSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (attackSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::ENV_ATTACK_ID, *attackSlider));
    
    decaySlider = std::make_unique<AnimatedSlider>();
    decaySlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    decaySlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (decaySlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::ENV_DECAY_ID, *decaySlider));
    
    sustainSlider = std::make_unique<AnimatedSlider>();
    sustainSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    sustainSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (sustainSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::ENV_SUSTAIN_ID, *sustainSlider));
    
    releaseSlider = std::make_unique<AnimatedSlider>();
    releaseSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    releaseSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (releaseSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::ENV_RELEASE_ID, *releaseSlider));
    
    attackLabel = std::make_unique<StyledLabel> ("ATTACK");
    addAndMakeVisible (attackLabel.get());
    
    decayLabel = std::make_unique<StyledLabel> ("DECAY");
    addAndMakeVisible (decayLabel.get());
    
    sustainLabel = std::make_unique<StyledLabel> ("SUSTAIN");
    addAndMakeVisible (sustainLabel.get());
    
    releaseLabel = std::make_unique<StyledLabel> ("RELEASE");
    addAndMakeVisible (releaseLabel.get());
    
    // Effects controls
    reverbSizeSlider = std::make_unique<AnimatedSlider>();
    reverbSizeSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    reverbSizeSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (reverbSizeSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::REVERB_SIZE_ID, *reverbSizeSlider));
    
    reverbWetSlider = std::make_unique<AnimatedSlider>();
    reverbWetSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    reverbWetSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (reverbWetSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::REVERB_WET_ID, *reverbWetSlider));
    
    chorusMixSlider = std::make_unique<AnimatedSlider>();
    chorusMixSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    chorusMixSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (chorusMixSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::CHORUS_MIX_ID, *chorusMixSlider));
    
    delayTimeSlider = std::make_unique<AnimatedSlider>();
    delayTimeSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    delayTimeSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (delayTimeSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::DELAY_TIME_ID, *delayTimeSlider));
    
    delayMixSlider = std::make_unique<AnimatedSlider>();
    delayMixSlider->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    delayMixSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 70, 20);
    addAndMakeVisible (delayMixSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::DELAY_MIX_ID, *delayMixSlider));
    
    masterVolumeSlider = std::make_unique<AnimatedSlider>();
    masterVolumeSlider->setSliderStyle (juce::Slider::LinearVertical);
    masterVolumeSlider->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible (masterVolumeSlider.get());
    sliderAttachments.push_back (std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (
        audioProcessor.getAPVTS(), ShoegazerAudioProcessor::MASTER_VOLUME_ID, *masterVolumeSlider));
    
    reverbSizeLabel = std::make_unique<StyledLabel> ("REV SIZE");
    addAndMakeVisible (reverbSizeLabel.get());
    
    reverbWetLabel = std::make_unique<StyledLabel> ("REV MIX");
    addAndMakeVisible (reverbWetLabel.get());
    
    chorusMixLabel = std::make_unique<StyledLabel> ("CHORUS");
    addAndMakeVisible (chorusMixLabel.get());
    
    delayTimeLabel = std::make_unique<StyledLabel> ("DELAY TIME");
    addAndMakeVisible (delayTimeLabel.get());
    
    delayMixLabel = std::make_unique<StyledLabel> ("DELAY MIX");
    addAndMakeVisible (delayMixLabel.get());
    
    masterVolumeLabel = std::make_unique<StyledLabel> ("MASTER");
    addAndMakeVisible (masterVolumeLabel.get());
    
    setSize (900, 600);
    startTimerHz (30);
}

ShoegazerAudioProcessorEditor::~ShoegazerAudioProcessorEditor()
{
    stopTimer();
    setLookAndFeel (nullptr);
}

//==============================================================================
void ShoegazerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Animated background
    juce::ColourGradient background (
        ModernLookAndFeel::getBackgroundColor().brighter (0.05f + 0.02f * std::sin (backgroundAnimation)),
        0, 0,
        ModernLookAndFeel::getBackgroundColor().darker (0.1f),
        (float) getWidth(), (float) getHeight(),
        false);
    g.setGradientFill (background);
    g.fillAll();
    
    // Title
    g.setColour (ModernLookAndFeel::getTextColor());
    g.setFont (juce::Font (32.0f, juce::Font::bold));
    
    // Glowing title effect
    g.setColour (ModernLookAndFeel::getPrimaryColor().withAlpha (0.3f));
    g.drawText ("SHOEGAZER", 20, 15, 400, 40, juce::Justification::left);
    
    g.setColour (ModernLookAndFeel::getTextColor());
    g.drawText ("SHOEGAZER", 20, 15, 400, 40, juce::Justification::left);
    
    g.setFont (juce::Font (14.0f));
    g.setColour (ModernLookAndFeel::getSecondaryColor());
    g.drawText ("Dreamy Synthesizer & Effects", 25, 50, 300, 20, juce::Justification::left);
}

void ShoegazerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds();
    area.removeFromTop (80); // Title area
    
    auto visualizerArea = area.removeFromTop (120);
    visualizer->setBounds (visualizerArea.reduced (10));
    
    auto controlsArea = area.reduced (10);
    
    // Layout panels in a grid
    auto topRow = controlsArea.removeFromTop (180);
    synthPanel->setBounds (topRow.removeFromLeft (280).reduced (5));
    filterPanel->setBounds (topRow.removeFromLeft (200).reduced (5));
    envelopePanel->setBounds (topRow.removeFromLeft (320).reduced (5));
    
    auto bottomRow = controlsArea.removeFromTop (180);
    effectsPanel->setBounds (bottomRow.removeFromLeft (680).reduced (5));
    
    auto masterArea = bottomRow.reduced (5);
    masterVolumeLabel->setBounds (masterArea.removeFromTop (20));
    masterVolumeSlider->setBounds (masterArea.removeFromBottom (140));
    
    // Synth panel layout
    auto synthArea = synthPanel->getBounds().reduced (15, 40);
    int oscWidth = 120;
    
    auto osc1Area = synthArea.removeFromLeft (oscWidth);
    osc1Label->setBounds (osc1Area.removeFromTop (20));
    osc1WaveCombo->setBounds (osc1Area.removeFromTop (25));
    
    synthArea.removeFromLeft (10);
    auto osc2Area = synthArea.removeFromLeft (oscWidth);
    osc2Label->setBounds (osc2Area.removeFromTop (20));
    osc2WaveCombo->setBounds (osc2Area.removeFromTop (25));
    
    synthArea = synthPanel->getBounds().reduced (15, 75);
    auto detuneArea = synthArea.removeFromLeft (130);
    detuneLabel->setBounds (detuneArea.removeFromBottom (20));
    detuneSlider->setBounds (detuneArea);
    
    auto unisonArea = synthArea.removeFromLeft (130);
    unisonLabel->setBounds (unisonArea.removeFromBottom (20));
    unisonSlider->setBounds (unisonArea);
    
    // Filter panel layout
    auto filterArea = filterPanel->getBounds().reduced (15, 40);
    auto cutoffArea = filterArea.removeFromLeft (90);
    cutoffLabel->setBounds (cutoffArea.removeFromBottom (20));
    cutoffSlider->setBounds (cutoffArea);
    
    auto resonanceArea = filterArea.removeFromLeft (90);
    resonanceLabel->setBounds (resonanceArea.removeFromBottom (20));
    resonanceSlider->setBounds (resonanceArea);
    
    // Envelope panel layout
    auto envArea = envelopePanel->getBounds().reduced (15, 40);
    auto attackArea = envArea.removeFromLeft (75);
    attackLabel->setBounds (attackArea.removeFromBottom (20));
    attackSlider->setBounds (attackArea);
    
    auto decayArea = envArea.removeFromLeft (75);
    decayLabel->setBounds (decayArea.removeFromBottom (20));
    decaySlider->setBounds (decayArea);
    
    auto sustainArea = envArea.removeFromLeft (75);
    sustainLabel->setBounds (sustainArea.removeFromBottom (20));
    sustainSlider->setBounds (sustainArea);
    
    auto releaseArea = envArea.removeFromLeft (75);
    releaseLabel->setBounds (releaseArea.removeFromBottom (20));
    releaseSlider->setBounds (releaseArea);
    
    // Effects panel layout
    auto fxArea = effectsPanel->getBounds().reduced (15, 40);
    
    auto reverbSizeArea = fxArea.removeFromLeft (90);
    reverbSizeLabel->setBounds (reverbSizeArea.removeFromBottom (20));
    reverbSizeSlider->setBounds (reverbSizeArea);
    
    auto reverbWetArea = fxArea.removeFromLeft (90);
    reverbWetLabel->setBounds (reverbWetArea.removeFromBottom (20));
    reverbWetSlider->setBounds (reverbWetArea);
    
    fxArea.removeFromLeft (20);
    
    auto chorusArea = fxArea.removeFromLeft (90);
    chorusMixLabel->setBounds (chorusArea.removeFromBottom (20));
    chorusMixSlider->setBounds (chorusArea);
    
    fxArea.removeFromLeft (20);
    
    auto delayTimeArea = fxArea.removeFromLeft (90);
    delayTimeLabel->setBounds (delayTimeArea.removeFromBottom (20));
    delayTimeSlider->setBounds (delayTimeArea);
    
    auto delayMixArea = fxArea.removeFromLeft (90);
    delayMixLabel->setBounds (delayMixArea.removeFromBottom (20));
    delayMixSlider->setBounds (delayMixArea);
}

void ShoegazerAudioProcessorEditor::timerCallback()
{
    backgroundAnimation += 0.02f;
    if (backgroundAnimation > juce::MathConstants<float>::twoPi)
        backgroundAnimation -= juce::MathConstants<float>::twoPi;
    
    repaint();
}
