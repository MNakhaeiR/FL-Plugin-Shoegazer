# Shoegazer VST Plugin - Build and Install Script

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Shoegazer VST Plugin Builder" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$ProjectRoot = "D:\Projects\Audio\FL-Studio\Shoegazer"
$BuildDir = Join-Path $ProjectRoot "build"
$VST3InstallPath = "C:\Program Files\Common Files\VST3"

$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)

Write-Host "Project Root: $ProjectRoot" -ForegroundColor Yellow
Write-Host ""

Write-Host "[1/5] Creating build directory..." -ForegroundColor Green
if (Test-Path $BuildDir) {
    Write-Host "  Build directory exists, cleaning..." -ForegroundColor Yellow
    Remove-Item -Recurse -Force $BuildDir -ErrorAction SilentlyContinue
}
New-Item -ItemType Directory -Path $BuildDir -Force | Out-Null
Write-Host "  Build directory ready" -ForegroundColor Green
Write-Host ""

Write-Host "[2/5] Configuring with CMake..." -ForegroundColor Green
Set-Location $BuildDir
$cmakeOutput = cmake .. -G "Visual Studio 17 2022" -A x64 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "  CMake configuration failed!" -ForegroundColor Red
    Write-Host "  Error: $cmakeOutput" -ForegroundColor Red
    Write-Host ""
    Write-Host "Please ensure:" -ForegroundColor Yellow
    Write-Host "  - CMake 3.22+ is installed" -ForegroundColor Yellow
    Write-Host "  - Visual Studio 2022 is installed" -ForegroundColor Yellow
    Write-Host "  - JUCE folder exists in project root" -ForegroundColor Yellow
    exit 1
}
Write-Host "  CMake configured successfully" -ForegroundColor Green
Write-Host ""

Write-Host "[3/5] Building Release version..." -ForegroundColor Green
Write-Host "  This may take several minutes..." -ForegroundColor Yellow
$buildOutput = cmake --build . --config Release 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "  Build failed!" -ForegroundColor Red
    Write-Host "  Error: $buildOutput" -ForegroundColor Red
    exit 1
}
Write-Host "  Build completed successfully" -ForegroundColor Green
Write-Host ""

Write-Host "[4/5] Locating built VST3..." -ForegroundColor Green
$VST3Path = Join-Path $BuildDir "ShoegazerPlugin_artefacts\Release\VST3\Shoegazer.vst3"

if (Test-Path $VST3Path) {
    Write-Host "  VST3 found: $VST3Path" -ForegroundColor Green
} else {
    Write-Host "  VST3 not found at expected location!" -ForegroundColor Red
    exit 1
}
Write-Host ""

Write-Host "[5/5] Installation" -ForegroundColor Green
if ($isAdmin) {
    Write-Host "  Installing to: $VST3InstallPath" -ForegroundColor Yellow
    try {
        Copy-Item -Path $VST3Path -Destination $VST3InstallPath -Recurse -Force
        Write-Host "  VST3 installed successfully!" -ForegroundColor Green
        Write-Host ""
        Write-Host "========================================" -ForegroundColor Cyan
        Write-Host "  Build and Installation Complete!" -ForegroundColor Green
        Write-Host "========================================" -ForegroundColor Cyan
        Write-Host ""
        Write-Host "Next steps:" -ForegroundColor Yellow
        Write-Host "  1. Open FL Studio" -ForegroundColor White
        Write-Host "  2. Rescan plugins" -ForegroundColor White
        Write-Host "  3. Find Shoegazer in Channel Rack" -ForegroundColor White
    } catch {
        Write-Host "  Installation failed: $_" -ForegroundColor Red
    }
} else {
    Write-Host "  Not running as administrator" -ForegroundColor Yellow
    Write-Host "  VST3 built but not installed" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "To install manually:" -ForegroundColor Yellow
    Write-Host "  Copy from: $VST3Path" -ForegroundColor White
    Write-Host "  To: $VST3InstallPath" -ForegroundColor White
    Write-Host ""
    Write-Host "Or run this script as administrator" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Standalone executable:" -ForegroundColor Cyan
$StandalonePath = Join-Path $BuildDir "ShoegazerPlugin_artefacts\Release\Standalone\Shoegazer.exe"
if (Test-Path $StandalonePath) {
    Write-Host "  $StandalonePath" -ForegroundColor White
}

Write-Host ""
Set-Location $ProjectRoot
