# Quick Start Guide - Shoegazer VST Plugin

## 🚀 Build Your Plugin (5 Minutes)

### Step 1: Open PowerShell

Right-click the `build.ps1` file and select "Run with PowerShell"

**OR**

Open PowerShell and run:

```powershell
cd D:\Projects\Audio\FL-Studio\Shoegazer
.\build.ps1
```

### Step 2: Install (Administrator Required)

If not running as admin, manually copy:

- **From**: `build\ShoegazerPlugin_artefacts\Release\VST3\Shoegazer.vst3`
- **To**: `C:\Program Files\Common Files\VST3\`

### Step 3: Load in FL Studio

1. Open FL Studio
2. Go to **Options → Manage Plugins → Find Plugins**
3. In Channel Rack, click **+** → **Shoegazer**
4. Done! 🎉

---

## 🎹 Your First Shoegaze Sound

### Thick Dreamy Pad

1. **Osc 1**: Set to "Rich"
2. **Osc 2**: Set to "Saw"
3. **Detune**: 0.15
4. **Unison**: 6
5. **Reverb Size**: 0.9
6. **Reverb Wet**: 0.5
7. **Delay Mix**: 0.3
8. Play a chord (C-E-G) → Instant shoegaze! 🌊

### Shimmering Lead

1. **Osc 1**: "Rich"
2. **Filter Cutoff**: 8000 Hz
3. **Attack**: 0.5s
4. **Chorus Mix**: 0.4
5. **Reverb Wet**: 0.3
6. Play melody → Ethereal! ✨

### Ambient Texture

1. **Unison**: 8
2. **Detune**: 0.2
3. **Reverb Size**: 1.0
4. **Delay Time**: 500ms
5. **Delay Feedback**: 0.7
6. Long notes → Atmospheric wash! 🎸

---

## 🛠️ Troubleshooting

### "CMake not found"

```powershell
winget install Kitware.CMake
```

### "Visual Studio not found"

Install Visual Studio 2022 Community (free) with "Desktop development with C++"

### "JUCE folder not found"

Make sure the JUCE folder exists at: `D:\Projects\Audio\FL-Studio\Shoegazer\JUCE\`

### "Plugin doesn't appear in FL Studio"

1. Check it's in: `C:\Program Files\Common Files\VST3\`
2. Rescan plugins in FL Studio
3. Restart FL Studio

---

## 🎯 Pro Tips

1. **CPU Saving**: Lower unison count if CPU is high
2. **Stereo Width**: Use Reverb Width for huge stereo image
3. **Movement**: Automate Filter Cutoff and Delay Feedback
4. **Layering**: Use multiple instances with different settings
5. **Rhythmic Effects**: Set Delay Time to match your tempo

---

## 📚 Learn More

- **Full Documentation**: See README.md
- **Build Details**: See BUILD.md
- **Complete Overview**: See PROJECT_SUMMARY.md

---

**Happy music making!** 🎵✨
