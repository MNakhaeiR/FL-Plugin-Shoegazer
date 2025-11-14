#pragma once

#include <JuceHeader.h>
#include "ModernLookAndFeel.h"

//==============================================================================
/**
 * Custom animated slider with glow effects
 */
class AnimatedSlider : public juce::Slider,
                       private juce::Timer
{
public:
    AnimatedSlider() : juce::Slider(), juce::Timer()
    {
        Timer::startTimerHz(60);
    }

    void paint(juce::Graphics &g) override
    {
        // Add glow effect when interacting
        if (isMouseOverOrDragging())
        {
            glowAlpha = juce::jmin(glowAlpha + 0.05f, 0.4f);
        }
        else
        {
            glowAlpha = juce::jmax(glowAlpha - 0.02f, 0.0f);
        }

        if (glowAlpha > 0.01f)
        {
            auto bounds = getLocalBounds().toFloat().reduced(5);
            g.setColour(ModernLookAndFeel::getPrimaryColor().withAlpha(glowAlpha));
            g.fillRoundedRectangle(bounds, 10.0f);
        }

        juce::Slider::paint(g);
    }

private:
    void timerCallback() override
    {
        repaint();
    }

    float glowAlpha = 0.0f;
};

//==============================================================================
/**
 * Custom panel component with gradient background
 */
class GradientPanel : public juce::Component
{
public:
    GradientPanel(const juce::String &title = "") : panelTitle(title) {}

    void paint(juce::Graphics &g) override
    {
        auto bounds = getLocalBounds().toFloat();

        // Gradient background
        juce::ColourGradient gradient(
            ModernLookAndFeel::getPanelColor().brighter(0.1f), 0, 0,
            ModernLookAndFeel::getPanelColor().darker(0.2f), 0, (float)getHeight(),
            false);
        g.setGradientFill(gradient);
        g.fillRoundedRectangle(bounds, 10.0f);

        // Border
        g.setColour(ModernLookAndFeel::getPrimaryColor().withAlpha(0.3f));
        g.drawRoundedRectangle(bounds.reduced(1), 10.0f, 2.0f);

        // Title
        if (panelTitle.isNotEmpty())
        {
            g.setColour(ModernLookAndFeel::getTextColor());
            g.setFont(juce::Font(16.0f, juce::Font::bold));
            g.drawText(panelTitle, 15, 10, getWidth() - 30, 25, juce::Justification::centredLeft);
        }
    }

private:
    juce::String panelTitle;
};

//==============================================================================
/**
 * Label with custom styling
 */
class StyledLabel : public juce::Label
{
public:
    StyledLabel(const juce::String &text = "") : juce::Label({}, text)
    {
        setFont(juce::Font(14.0f, juce::Font::bold));
        setColour(juce::Label::textColourId, ModernLookAndFeel::getTextColor());
        setJustificationType(juce::Justification::centred);
    }
};
