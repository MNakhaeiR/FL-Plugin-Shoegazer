# Using the Shoegazer Plugin

## Quick Start

### Load the Plugin in FL Studio

1. Copy `Shoegazer.vst3` to your VST3 folder (or run as admin for auto-install)
2. Rescan plugins in FL Studio
3. Add to **Channel Rack** for synth/drums
4. Use Piano Roll for MIDI input

## MIDI Note Layout

### Synth Zone (C2 and above - MIDI 48+)

- Regular keyboard playing
- Full 16-voice polyphony
- Wavetable synthesis with effects

### Drum Zone (Below C2 - MIDI 24-35)

```
C0  (24) = Kick
D0  (26) = Snare  
F#0 (30) = Closed Hat
A#0 (34) = Open Hat
C1  (36) = Kick (GM standard)
D1  (38) = Snare (GM standard)
```

## Factory Presets

### Pads

- **Thick Pad** - Dense, lush texture (6 unison, heavy reverb)
- **Velvet Pad** - Smooth, slow-evolving (triangle+sine)

### Leads  

- **Shimmering Lead** - Bright, chorused attack
- **Distorted Lead** - Aggressive with high resonance

### Textures

- **Ambient Texture** - Maximum atmosphere (8 unison, long delay)
- **Noise Wall** - Chaotic distorted mass

### Bass

- **Dreamy Bass** - Deep, resonant low-end

### Plucks

- **Crystal Arp** - Ultra-bright, percussive

## Tips for Shoegaze Sound

1. **Layer presets** - Use multiple instances with different presets
2. **Automate reverb** - Increase wetness during builds
3. **Detune everything** - The "Detune" knob is your friend
4. **Drums below, synth above** - Play drums in C0-C1 range, melodies C2+
5. **Use delay feedback** - Create self-oscillating feedback loops
6. **Max unison** - 8 voices with 0.25 detune = instant wall of sound

## Current Parameters (32 total)

### Oscillators (4)

- Osc 1/2 Waveform (Sine/Saw/Square/Triangle/Rich)
- Detune (0.0-1.0)
- Unison Voices (1-8)

### Filter (2)

- Cutoff (20-20000 Hz)
- Resonance (0.1-2.0)

### Envelope (4)

- Attack/Decay/Sustain/Release

### Reverb (4)

- Size, Damping, Wet, Width

### Chorus (4)

- Rate, Depth, Feedback, Mix

### Delay (3)

- Time (10-2000ms), Feedback, Mix

### Distortion (2)

- Amount, Mix

### Drums (6)

- Kick: Pitch (30-120Hz), Decay
- Snare: Tone, Snappy
- Hat: Tone, Decay

### Master (1)

- Volume

## Known Limitations

- No preset browser UI yet (presets loaded programmatically)
- No visual drum pads (use MIDI controller or Piano Roll)
- No sample drag-drop UI (use code to load samples)

## Troubleshooting

**No sound?**

- Check Master Volume isn't at 0
- Verify MIDI notes: <C2 for drums, ≥C2 for synth
- Ensure Filter Cutoff isn't too low

**Drums not playing?**

- Play notes below C2 (MIDI 48)
- Try C1 (36) for kick, D1 (38) for snare

**Sounds thin?**

- Increase Unison Voices (3-8)
- Add Detune (0.1-0.3)
- Increase Reverb Size and Wet

**CPU too high?**

- Reduce Unison Voices
- Lower number of active voices
- Disable unused effects (set Mix to 0)
