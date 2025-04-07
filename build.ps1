$ErrorActionPreference = "Stop"

# Set MSYS2 mingw64 path for raylib includes/libs
$env:MSYS2_MINGW64_PATH = "C:/msys64/mingw64"

$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $projectRoot "build"
if (!(Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

Push-Location $buildDir

cmake .. -G "MinGW Makefiles"
mingw32-make

Pop-Location

