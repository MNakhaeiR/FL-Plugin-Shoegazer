#include "ModernLookAndFeel.h"

ModernLookAndFeel::ModernLookAndFeel()
{
    setColour(juce::ResizableWindow::backgroundColourId, getBackgroundColor());
    setColour(juce::Slider::thumbColourId, getPrimaryColor());
    setColour(juce::Slider::rotarySliderFillColourId, getPrimaryColor());
    setColour(juce::Slider::rotarySliderOutlineColourId, getPanelColor());
    setColour(juce::Slider::trackColourId, getSecondaryColor());
    setColour(juce::Slider::backgroundColourId, getPanelColor());
    setColour(juce::TextButton::buttonColourId, getPanelColor());
    setColour(juce::TextButton::textColourOffId, getTextColor());
    setColour(juce::ComboBox::backgroundColourId, getPanelColor());
    setColour(juce::ComboBox::textColourId, getTextColor());
    setColour(juce::ComboBox::outlineColourId, getPrimaryColor().withAlpha(0.5f));
    setColour(juce::Label::textColourId, getTextColor());
}

void ModernLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height,
                                         float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                                         juce::Slider &slider)
{
    auto radius = (float)juce::jmin(width / 2, height / 2) - 10.0f;
    auto centreX = (float)x + (float)width * 0.5f;
    auto centreY = (float)y + (float)height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // Outer glow
    g.setColour(getPrimaryColor().withAlpha(0.2f));
    g.fillEllipse(rx - 5, ry - 5, rw + 10, rw + 10);

    // Fill circle
    g.setColour(getPanelColor());
    g.fillEllipse(rx, ry, rw, rw);

    // Outline
    g.setColour(getPrimaryColor().withAlpha(0.5f));
    g.drawEllipse(rx, ry, rw, rw, 2.0f);

    // Arc for value
    juce::Path valueArc;
    valueArc.addCentredArc(centreX, centreY, radius, radius,
                           0.0f, rotaryStartAngle, angle, true);

    g.setColour(getPrimaryColor());
    g.strokePath(valueArc, juce::PathStrokeType(3.0f, juce::PathStrokeType::curved,
                                                juce::PathStrokeType::rounded));

    // Pointer
    juce::Path pointer;
    auto pointerLength = radius * 0.6f;
    auto pointerThickness = 3.0f;
    pointer.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    pointer.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

    // Pointer glow
    g.setColour(getSecondaryColor().withAlpha(0.8f));
    g.fillPath(pointer);

    g.setColour(getSecondaryColor());
    g.fillEllipse(centreX - 4, centreY - 4, 8, 8);
}

void ModernLookAndFeel::drawLinearSlider(juce::Graphics &g, int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         juce::Slider::SliderStyle style, juce::Slider &slider)
{
    auto trackWidth = juce::jmin(6.0f, (float)(style == juce::Slider::LinearVertical ? width : height) * 0.25f);

    juce::Point<float> startPoint(style == juce::Slider::LinearVertical ? (float)x + (float)width * 0.5f : (float)x,
                                  style == juce::Slider::LinearVertical ? (float)(y + height) : (float)y + (float)height * 0.5f);

    juce::Point<float> endPoint(style == juce::Slider::LinearVertical ? startPoint.x : (float)(x + width),
                                style == juce::Slider::LinearVertical ? (float)y : startPoint.y);

    juce::Path backgroundTrack;
    backgroundTrack.startNewSubPath(startPoint);
    backgroundTrack.lineTo(endPoint);
    g.setColour(getPanelColor().brighter(0.2f));
    g.strokePath(backgroundTrack, juce::PathStrokeType(trackWidth, juce::PathStrokeType::curved,
                                                       juce::PathStrokeType::rounded));

    juce::Path valueTrack;
    juce::Point<float> minPoint, maxPoint;

    auto kx = style == juce::Slider::LinearVertical ? startPoint.x : sliderPos;
    auto ky = style == juce::Slider::LinearVertical ? sliderPos : startPoint.y;

    minPoint = startPoint;
    maxPoint = {kx, ky};

    valueTrack.startNewSubPath(minPoint);
    valueTrack.lineTo(maxPoint);
    g.setColour(getPrimaryColor());
    g.strokePath(valueTrack, juce::PathStrokeType(trackWidth, juce::PathStrokeType::curved,
                                                  juce::PathStrokeType::rounded));

    // Thumb
    auto thumbWidth = trackWidth * 2.0f;
    g.setColour(getSecondaryColor());
    g.fillEllipse(juce::Rectangle<float>(thumbWidth, thumbWidth).withCentre({kx, ky}));

    g.setColour(getSecondaryColor().brighter(0.5f));
    g.fillEllipse(juce::Rectangle<float>(thumbWidth * 0.5f, thumbWidth * 0.5f).withCentre({kx, ky}));
}

void ModernLookAndFeel::drawButtonBackground(juce::Graphics &g, juce::Button &button,
                                             const juce::Colour &backgroundColour,
                                             bool shouldDrawButtonAsHighlighted,
                                             bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
    auto baseColour = backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
                          .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting(shouldDrawButtonAsDown ? 0.2f : 0.05f);

    // Glow effect when highlighted
    if (shouldDrawButtonAsHighlighted)
    {
        g.setColour(getPrimaryColor().withAlpha(0.3f));
        g.fillRoundedRectangle(bounds.expanded(2), 6.0f);
    }

    g.setColour(baseColour);
    g.fillRoundedRectangle(bounds, 6.0f);

    g.setColour(getPrimaryColor().withAlpha(0.5f));
    g.drawRoundedRectangle(bounds, 6.0f, 1.0f);
}

void ModernLookAndFeel::drawComboBox(juce::Graphics &g, int width, int height,
                                     bool isButtonDown, int buttonX, int buttonY,
                                     int buttonW, int buttonH, juce::ComboBox &box)
{
    auto cornerSize = 6.0f;
    juce::Rectangle<int> boxBounds(0, 0, width, height);

    g.setColour(getPanelColor());
    g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

    g.setColour(getPrimaryColor().withAlpha(0.5f));
    g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

    juce::Rectangle<int> arrowZone(width - 30, 0, 20, height);
    juce::Path path;
    path.startNewSubPath((float)arrowZone.getX() + 3.0f, (float)arrowZone.getCentreY() - 2.0f);
    path.lineTo((float)arrowZone.getCentreX(), (float)arrowZone.getCentreY() + 3.0f);
    path.lineTo((float)arrowZone.getRight() - 3.0f, (float)arrowZone.getCentreY() - 2.0f);

    g.setColour(getSecondaryColor());
    g.strokePath(path, juce::PathStrokeType(2.0f));
}

juce::Label *ModernLookAndFeel::createSliderTextBox(juce::Slider &slider)
{
    auto *l = LookAndFeel_V4::createSliderTextBox(slider);
    l->setColour(juce::Label::textColourId, getTextColor());
    l->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    l->setColour(juce::Label::outlineColourId, juce::Colours::transparentBlack);
    l->setJustificationType(juce::Justification::centred);
    return l;
}
