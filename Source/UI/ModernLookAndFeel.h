#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 * Modern Look and Feel for the Shoegazer plugin
 * Features dark theme with glowing accents and smooth animations
 */
class ModernLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ModernLookAndFeel();
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override;
    
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          juce::Slider::SliderStyle style, juce::Slider& slider) override;
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown) override;
    
    void drawComboBox (juce::Graphics& g, int width, int height,
                      bool isButtonDown, int buttonX, int buttonY,
                      int buttonW, int buttonH, juce::ComboBox& box) override;
    
    juce::Label* createSliderTextBox (juce::Slider& slider) override;
    
    // Color scheme
    static juce::Colour getPrimaryColor() { return juce::Colour (0xff6b5ce7); }  // Purple
    static juce::Colour getSecondaryColor() { return juce::Colour (0xff4ecdc4); } // Cyan
    static juce::Colour getBackgroundColor() { return juce::Colour (0xff1a1a2e); } // Dark blue
    static juce::Colour getPanelColor() { return juce::Colour (0xff16213e); }     // Darker blue
    static juce::Colour getTextColor() { return juce::Colour (0xffeaeaea); }      // Light gray
    static juce::Colour getAccentColor() { return juce::Colour (0xffff6e6e); }    // Red-pink
};
