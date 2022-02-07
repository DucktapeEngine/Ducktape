# clean the previous build directory
if (Test-Path -Path "./build") {
    Remove-Item -Path "./build" -Recurse -Force
}

Clear-Host
Write-Host "Setting up Ducktape for compiling..."
Write-Host "Choose your generator:"
Write-Host "1) Borland Makefiles"
Write-Host "2) MSYS Makefiles"
Write-Host "3) MinGW Makefiles (Default for Windows)"
Write-Host "4) NMake Makefiles"
Write-Host "5) NMake Makefiles JOM"
Write-Host "6) Unix Makefiles (Default for Linux)"
Write-Host "7) Watcom WMake"

$option = Read-Host "Enter your option (1,2,3,4,5,6,7)"
$generator = ""

if ($option -eq [string]::empty) {
    if ($env:OS) {
        $generator = "MinGW Makefiles"
    } else {
        $generator = "Unix Makefiles"
    }
} elseif ($option -eq 1) {
    $generator = "Borland Makefiles"
} elseif ($option -eq 2) {
    $generator = "MSYS Makefiles"
} elseif ($option -eq 3) {
    $generator = "MinGW Makefiles"
} elseif ($option -eq 4) {
    $generator = "NMake Makefiles"
} elseif ($option -eq 5) {
    $generator = "NMake Makefiles JOM"
} elseif ($option -eq 6) {
    $generator = "Unix Makefiles"
} elseif ($option -eq 7) {
    $generator = "Watcom WMake"
}

$compiler = Read-Host "Specify your compiler:"
Write-Host "(You may enter a path to your compiler or just the compiler's command name if the compiler path is already in your PATH environment variable)"
New-Item -Path 'build' -ItemType "directory" | Out-Null
Set-Location -Path "build"
cmake -G $generator -D CMAKE_CXX_COMPILER=$compiler ..
make