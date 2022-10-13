param(
    [switch]$help = $false, # Show help
    [switch]$clean = $false, # Clean up the downloaded files
    [string]$version = "" # Version of the DLL to download
)

# Help
if ($help) {
    # Set output color to green and bold
    $host.ui.rawui.foregroundcolor = "green"
    Write-Host ""
    Write-Host "从 Github 下载 GenshinImpact_AutoTrack_DLL 的构建"
    Write-Host ""
    Write-Host "使用方法: pwsh download-dll.ps1 [-help] [-clean] [-version <version>]"
    Write-Host "参数："
    Write-Host "  -help: 显示帮助"
    Write-Host "  -clean: 清理下载的文件，若不清空将会跳过下载流程"
    Write-Host "  -version: 下载的构建版本, 默认为 latest"
    Write-Host "    latest: 下载最新版本并显示版本号"
    Write-Host "    <version>: 下载指定版本"
    # Reset output color
    $host.ui.rawui.foregroundcolor = "white"
    exit
}

# Check if directory cvAutoTrack exists
if (Test-Path -Path ".\cvAutoTrack") {
    # If $clean is true, remove the directory
    if ($clean) {
        Remove-Item -Path ".\cvAutoTrack" -Recurse -Force
        Write-Host "Removed cvAutoTrack directory."
    }
    # Else if it exists, skip download and exit
    else {
        Write-Host "cvAutoTrack directory already exists. Skipping download."
        exit 0
    }
}

# Check if $version is empty
if ($version -eq "") {
    # Get cvAutoTrack version from package.json
    $package = Get-Content -Path ".\package.json" | ConvertFrom-Json
    # $cvAutoTrackVersion = $package.cvAutoTrackVersion
    # Check field cvAutoTrackVersion exists
    if ($package.cvAutoTrackVersion) {
        $version = $package.cvAutoTrackVersion
    }
    else {
        Write-Host "cvAutoTrackVersion field not found in package.json. Using latest."
        $version = "latest"
    }
}


# Show the version to download
Write-Host "Downloading cvAutoTrack version $version"

# If $version is semver
if ($version -match "^\d+\.\d+\.\d+$") {
    $version = "tags/$version"
}

$latest_release = Invoke-WebRequest "https://api.github.com/repos/GengGode/GenshinImpact_AutoTrack_DLL/releases/$version"
$latest_release_url_list = $latest_release.content | ConvertFrom-Json | Select-Object -ExpandProperty assets | Select-Object -ExpandProperty browser_download_url

# If the version is latest, show the latest release version
if ($version -eq "latest") {
    $latest_release_version = $latest_release.content | ConvertFrom-Json | Select-Object -ExpandProperty tag_name
    Write-Host "Latest release version: $latest_release_version"
}

# Select 7z file
$latest_release_url_7z = $latest_release_url_list | Where-Object { $_ -like "*7z" }
Write-Output "Downloading latest 'GenshinImpact_AutoTrack_DLL' release from $latest_release_url_7z"

# Download 7z file
Invoke-WebRequest -Uri $latest_release_url_7z -OutFile "cvAutoTrack.7z"

# Extract 7z file to cvAutoTrack
7z x cvAutoTrack.7z -o"cvAutoTrack" -y

# Remove 7z file
Remove-Item cvAutoTrack.7z

# Download TEST_cvAutoTrack_Cpp.exe to cvAutoTrack
$latest_release_url_exe = $latest_release_url_list | Where-Object { $_ -like "*TEST_cvAutoTrack_Cpp.exe" }
Write-Output "Downloading latest 'TEST_cvAutoTrack_Cpp.exe' release from $latest_release_url_exe"
Invoke-WebRequest -Uri $latest_release_url_exe -OutFile "cvAutoTrack\TEST_cvAutoTrack_Cpp.exe"
