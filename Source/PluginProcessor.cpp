#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ShoegazerAudioProcessor::ShoegazerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
                         ),
#endif
      apvts(*this, nullptr, "Parameters", createParameterLayout())
{
    // Add voices to synthesiser
    for (int i = 0; i < numVoices; ++i)
        synthesiser.addVoice(new ShoegazeVoice());

    synthesiser.addSound(new ShoegazeSound());
    
    // Initialize drum voices
    for (int i = 0; i < numDrumVoices; ++i)
        drumVoices.add(new DrumSynthesizer());
    
    // Load factory presets
    presetManager.createFactoryPresets();
}

ShoegazerAudioProcessor::~ShoegazerAudioProcessor()
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout ShoegazerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Oscillator parameters
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        OSC1_WAVE_ID, "Osc 1 Wave",
        juce::StringArray{"Sine", "Saw", "Square", "Triangle", "Rich"}, 4));

    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        OSC2_WAVE_ID, "Osc 2 Wave",
        juce::StringArray{"Sine", "Saw", "Square", "Triangle", "Rich"}, 1));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        OSC_DETUNE_ID, "Detune",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterInt>(
        OSC_UNISON_ID, "Unison Voices", 1, 8, 3));
    
    // Advanced synthesis parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        FM_AMOUNT_ID, "FM Amount",
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.1f), 0.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        FM_RATIO_ID, "FM Ratio",
        juce::NormalisableRange<float>(0.5f, 8.0f, 0.1f), 2.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        NOISE_LEVEL_ID, "Noise Level",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        SUB_OSC_LEVEL_ID, "Sub Osc Level",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

    // Filter parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        FILTER_CUTOFF_ID, "Filter Cutoff",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.3f), 2000.0f,
        "Hz"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        FILTER_RESONANCE_ID, "Filter Resonance",
        juce::NormalisableRange<float>(0.1f, 2.0f, 0.01f), 0.7f));

    // Envelope parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        ENV_ATTACK_ID, "Attack",
        juce::NormalisableRange<float>(0.001f, 5.0f, 0.001f, 0.3f), 0.1f,
        "s"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        ENV_DECAY_ID, "Decay",
        juce::NormalisableRange<float>(0.001f, 5.0f, 0.001f, 0.3f), 0.3f,
        "s"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        ENV_SUSTAIN_ID, "Sustain",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.7f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        ENV_RELEASE_ID, "Release",
        juce::NormalisableRange<float>(0.001f, 10.0f, 0.001f, 0.3f), 0.5f,
        "s"));

    // Reverb parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        REVERB_SIZE_ID, "Reverb Size",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.8f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        REVERB_DAMPING_ID, "Reverb Damping",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        REVERB_WET_ID, "Reverb Wet",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.4f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        REVERB_WIDTH_ID, "Reverb Width",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f));

    // Chorus parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        CHORUS_RATE_ID, "Chorus Rate",
        juce::NormalisableRange<float>(0.1f, 10.0f, 0.1f), 1.5f,
        "Hz"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        CHORUS_DEPTH_ID, "Chorus Depth",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        CHORUS_FEEDBACK_ID, "Chorus Feedback",
        juce::NormalisableRange<float>(0.0f, 0.95f, 0.01f), 0.3f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        CHORUS_MIX_ID, "Chorus Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.3f));

    // Delay parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DELAY_TIME_ID, "Delay Time",
        juce::NormalisableRange<float>(10.0f, 2000.0f, 1.0f), 250.0f,
        "ms"));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DELAY_FEEDBACK_ID, "Delay Feedback",
        juce::NormalisableRange<float>(0.0f, 0.95f, 0.01f), 0.5f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DELAY_MIX_ID, "Delay Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.4f));

    // Distortion parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DIST_AMOUNT_ID, "Distortion Amount",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DIST_MIX_ID, "Distortion Mix",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));

    // Master volume
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        MASTER_VOLUME_ID, "Master Volume",
        juce::NormalisableRange<float>(0.0f, 2.0f, 0.01f), 0.7f));
    
    // Drum synthesizer parameters
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DRUM_KICK_PITCH_ID, "Kick Pitch",
        juce::NormalisableRange<float>(30.0f, 120.0f, 1.0f), 60.0f,
        "Hz"));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DRUM_KICK_DECAY_ID, "Kick Decay",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.3f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DRUM_SNARE_TONE_ID, "Snare Tone",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DRUM_SNARE_SNAPPY_ID, "Snare Snappy",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.7f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DRUM_HAT_TONE_ID, "Hat Tone",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.8f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        DRUM_HAT_DECAY_ID, "Hat Decay",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.15f));

    return {params.begin(), params.end()};
}

//==============================================================================
const juce::String ShoegazerAudioProcessor::getName() const
{
    return "Shoegazer";
}

bool ShoegazerAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ShoegazerAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool ShoegazerAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ShoegazerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ShoegazerAudioProcessor::getNumPrograms()
{
    return 1;
}

int ShoegazerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ShoegazerAudioProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

const juce::String ShoegazerAudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}

void ShoegazerAudioProcessor::changeProgramName(int index, const juce::String &newName)
{
    juce::ignoreUnused(index, newName);
}

//==============================================================================
void ShoegazerAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synthesiser.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synthesiser.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<ShoegazeVoice *>(synthesiser.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock);
        }
    }

    effectsChain.prepareToPlay(sampleRate, samplesPerBlock);
    samplePlayer.prepareToPlay(sampleRate, samplesPerBlock);
    
    for (auto* drum : drumVoices)
        drum->prepareToPlay(sampleRate, samplesPerBlock);
}

void ShoegazerAudioProcessor::releaseResources()
{
    effectsChain.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ShoegazerAudioProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void ShoegazerAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Update parameters
    updateSynthParameters();
    updateEffectsParameters();
    updateDrumParameters();

    // Process MIDI for drums (notes below C2) and synth (C2 and above)
    juce::MidiBuffer synthMidi, drumMidi;
    
    for (const auto metadata : midiMessages)
    {
        auto message = metadata.getMessage();
        if (message.isNoteOn())
        {
            int note = message.getNoteNumber();
            if (note < 36) // Notes below C2 trigger drums
            {
                float velocity = message.getFloatVelocity();
                triggerDrum(note, velocity);
            }
            else // C2 and above for synth
            {
                synthMidi.addEvent(message, metadata.samplePosition);
            }
        }
        else
        {
            synthMidi.addEvent(message, metadata.samplePosition);
        }
    }

    // Render synthesiser
    synthesiser.renderNextBlock(buffer, synthMidi, 0, buffer.getNumSamples());
    
    // Render drums
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        float drumSample = 0.0f;
        for (auto* drum : drumVoices)
        {
            if (drum->isActive())
                drumSample += drum->getNextSample();
        }
        
        for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
            buffer.addSample(ch, sample, drumSample);
    }
    
    // Render sample player
    juce::AudioSourceChannelInfo channelInfo(&buffer, 0, buffer.getNumSamples());
    samplePlayer.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    // Apply effects chain
    effectsChain.processBlock(buffer);

    // Apply master volume
    float masterVolume = apvts.getRawParameterValue(MASTER_VOLUME_ID)->load();
    buffer.applyGain(masterVolume);
}

void ShoegazerAudioProcessor::updateSynthParameters()
{
    int osc1Wave = apvts.getRawParameterValue(OSC1_WAVE_ID)->load();
    int osc2Wave = apvts.getRawParameterValue(OSC2_WAVE_ID)->load();
    float detune = apvts.getRawParameterValue(OSC_DETUNE_ID)->load();
    int unison = apvts.getRawParameterValue(OSC_UNISON_ID)->load();

    float fmAmount = apvts.getRawParameterValue(FM_AMOUNT_ID)->load();
    float fmRatio = apvts.getRawParameterValue(FM_RATIO_ID)->load();
    float noiseLevel = apvts.getRawParameterValue(NOISE_LEVEL_ID)->load();
    float subOscLevel = apvts.getRawParameterValue(SUB_OSC_LEVEL_ID)->load();
    
    float filterCutoff = apvts.getRawParameterValue(FILTER_CUTOFF_ID)->load();
    float filterResonance = apvts.getRawParameterValue(FILTER_RESONANCE_ID)->load();

    float attack = apvts.getRawParameterValue(ENV_ATTACK_ID)->load();
    float decay = apvts.getRawParameterValue(ENV_DECAY_ID)->load();
    float sustain = apvts.getRawParameterValue(ENV_SUSTAIN_ID)->load();
    float release = apvts.getRawParameterValue(ENV_RELEASE_ID)->load();

    for (int i = 0; i < synthesiser.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<ShoegazeVoice *>(synthesiser.getVoice(i)))
        {
            voice->setOscillatorWaveform(0, osc1Wave);
            voice->setOscillatorWaveform(1, osc2Wave);
            voice->setOscillatorDetune(detune);
            voice->setOscillatorUnison(unison);
            
            voice->setFMAmount(fmAmount);
            voice->setFMRatio(fmRatio);
            voice->setNoiseLevel(noiseLevel);
            voice->setSubOscLevel(subOscLevel);

            voice->setFilterCutoff(filterCutoff);
            voice->setFilterResonance(filterResonance);

            voice->setAttack(attack);
            voice->setDecay(decay);
            voice->setSustain(sustain);
            voice->setRelease(release);
        }
    }
}

void ShoegazerAudioProcessor::updateEffectsParameters()
{
    effectsChain.setReverbSize(apvts.getRawParameterValue(REVERB_SIZE_ID)->load());
    effectsChain.setReverbDamping(apvts.getRawParameterValue(REVERB_DAMPING_ID)->load());
    effectsChain.setReverbWetLevel(apvts.getRawParameterValue(REVERB_WET_ID)->load());
    effectsChain.setReverbWidth(apvts.getRawParameterValue(REVERB_WIDTH_ID)->load());

    effectsChain.setChorusRate(apvts.getRawParameterValue(CHORUS_RATE_ID)->load());
    effectsChain.setChorusDepth(apvts.getRawParameterValue(CHORUS_DEPTH_ID)->load());
    effectsChain.setChorusFeedback(apvts.getRawParameterValue(CHORUS_FEEDBACK_ID)->load());
    effectsChain.setChorusMix(apvts.getRawParameterValue(CHORUS_MIX_ID)->load());

    effectsChain.setDelayTime(apvts.getRawParameterValue(DELAY_TIME_ID)->load());
    effectsChain.setDelayFeedback(apvts.getRawParameterValue(DELAY_FEEDBACK_ID)->load());
    effectsChain.setDelayMix(apvts.getRawParameterValue(DELAY_MIX_ID)->load());

    effectsChain.setDistortionAmount(apvts.getRawParameterValue(DIST_AMOUNT_ID)->load());
    effectsChain.setDistortionMix(apvts.getRawParameterValue(DIST_MIX_ID)->load());
}

void ShoegazerAudioProcessor::updateDrumParameters()
{
    float kickPitch = apvts.getRawParameterValue(DRUM_KICK_PITCH_ID)->load();
    float kickDecay = apvts.getRawParameterValue(DRUM_KICK_DECAY_ID)->load();
    float snareTone = apvts.getRawParameterValue(DRUM_SNARE_TONE_ID)->load();
    float snareSnappy = apvts.getRawParameterValue(DRUM_SNARE_SNAPPY_ID)->load();
    float hatTone = apvts.getRawParameterValue(DRUM_HAT_TONE_ID)->load();
    float hatDecay = apvts.getRawParameterValue(DRUM_HAT_DECAY_ID)->load();
    
    for (auto* drum : drumVoices)
    {
        drum->setKickPitch(kickPitch);
        drum->setKickDecay(kickDecay);
        drum->setSnareTone(snareTone);
        drum->setSnareSnappy(snareSnappy);
        drum->setHatTone(hatTone);
        drum->setHatDecay(hatDecay);
    }
}

void ShoegazerAudioProcessor::triggerDrum(int midiNote, float velocity)
{
    // Find an inactive drum voice or steal the oldest
    DrumSynthesizer* drumToUse = nullptr;
    
    for (auto* drum : drumVoices)
    {
        if (!drum->isActive())
        {
            drumToUse = drum;
            break;
        }
    }
    
    if (drumToUse == nullptr)
        drumToUse = drumVoices[0]; // Steal first voice
    
    auto drumType = getDrumTypeFromMidiNote(midiNote);
    drumToUse->triggerDrum(drumType, velocity);
}

DrumSynthesizer::DrumType ShoegazerAudioProcessor::getDrumTypeFromMidiNote(int midiNote)
{
    // MIDI note mapping for drums (GM standard-ish)
    // C0 (24) = Kick, D0 (26) = Snare, F#0 (30) = Closed Hat, A#0 (34) = Open Hat, etc.
    switch (midiNote)
    {
        case 24: case 35: case 36: // Kick variations
            return DrumSynthesizer::Kick;
        case 26: case 38: case 40: // Snare variations
            return DrumSynthesizer::Snare;
        case 28: case 30: case 42: case 44: // Closed hat variations
            return DrumSynthesizer::ClosedHat;
        case 32: case 34: case 46: // Open hat variations
            return DrumSynthesizer::OpenHat;
        case 41: case 43: case 45: case 47: case 48: case 50: // Tom variations
            return DrumSynthesizer::Tom;
        case 49: case 52: case 55: case 57: // Crash/ride variations
            return DrumSynthesizer::Crash;
        case 37: case 82: // Rim/stick
            return DrumSynthesizer::Rim;
        case 39: // Clap
            return DrumSynthesizer::Clap;
        default:
            return DrumSynthesizer::Kick;
    }
}

void ShoegazerAudioProcessor::loadPreset(int presetIndex)
{
    auto presets = presetManager.getAllPresets();
    if (presetIndex >= 0 && presetIndex < presets.size())
    {
        const auto& preset = presets[presetIndex];
        currentPresetName = preset.name;
        
        // Load preset state into APVTS
        auto presetState = preset.state;
        for (int i = 0; i < presetState.getNumProperties(); ++i)
        {
            auto paramID = presetState.getPropertyName(i);
            auto value = presetState.getProperty(paramID);
            
            if (auto* param = apvts.getParameter(paramID.toString()))
                param->setValueNotifyingHost(value);
        }
    }
}

int ShoegazerAudioProcessor::getNumPresets() const
{
    return presetManager.getAllPresets().size();
}

juce::StringArray ShoegazerAudioProcessor::getPresetNames() const
{
    return presetManager.getPresetNames();
}

//==============================================================================
bool ShoegazerAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor *ShoegazerAudioProcessor::createEditor()
{
    return new ShoegazerAudioProcessorEditor(*this);
}

//==============================================================================
void ShoegazerAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void ShoegazerAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new ShoegazerAudioProcessor();
}
