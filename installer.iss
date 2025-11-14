; Shoegazer VST3 Plugin Installer
; Inno Setup Script

#define MyAppName "Shoegazer"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "Shahrvand"
#define MyAppURL "https://github.com/MNakhaeiR/FL-Plugin-Shoegazer"

[Setup]
AppId={{8F3A2B1C-4D5E-6F7A-8B9C-0D1E2F3A4B5C}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={commonpf}\Common Files\VST3
DisableDirPage=yes
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
OutputDir=build\installer
OutputBaseFilename=Shoegazer-Installer-v{#MyAppVersion}
SetupIconFile=
Compression=lzma
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=admin
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "build\ShoegazerPlugin_artefacts\Release\VST3\Shoegazer.vst3\*"; DestDir: "{commonpf}\Common Files\VST3\Shoegazer.vst3"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"

[Messages]
WelcomeLabel1=Welcome to the [name] Setup Wizard
WelcomeLabel2=This will install the Shoegazer VST3 plugin on your computer.%n%nShoegazer is a complete shoegaze production tool featuring:%n%n• Dual wavetable synthesizer with 8 factory presets%n• Drum synthesizer (kick, snare, hats, toms)%n• Sample player for drums and guitars%n• Professional effects chain (reverb, chorus, delay, distortion)%n%nThe plugin will be installed to:%nC:\Program Files\Common Files\VST3

[Code]
procedure CurPageChanged(CurPageID: Integer);
begin
  if CurPageID = wpFinished then
  begin
    WizardForm.FinishedLabel.Caption := 
      'Shoegazer has been successfully installed!' + #13#10#13#10 +
      'Next steps:' + #13#10 +
      '1. Open FL Studio' + #13#10 +
      '2. Go to Options > Manage plugins > Refresh' + #13#10 +
      '3. Add Shoegazer from Channel Rack' + #13#10#13#10 +
      'Quick start:' + #13#10 +
      '• Notes C2 and above play the synthesizer' + #13#10 +
      '• Notes below C2 trigger drums (C1=kick, D1=snare)' + #13#10 +
      '• All 32 parameters are automatable';
  end;
end;
