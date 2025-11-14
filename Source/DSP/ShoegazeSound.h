#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Shoegazer Voice - Polyphonic voice for the synthesizer
 * Generates lush, dreamy tones perfect for shoegaze music
 */
class ShoegazeSound : public juce::SynthesiserSound
{
public:
    ShoegazeSound() {}
    
    bool appliesToNote (int) override { return true; }
    bool appliesToChannel (int) override { return true; }
};
