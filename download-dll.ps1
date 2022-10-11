param(
    [switch]$help = $false, # Show help
    [switch]$clean = $false, # Clean up the downloaded files
    [string]$version = "latest" # Version of the DLL to download
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

# Show the version to download
Write-Host "Downloading cvAutoTrack version $version"

$latest_release = Invoke-WebRequest "https://api.github.com/repos/GengGode/GenshinImpact_AutoTrack_DLL/releases/$version"
$latest_release_url = $latest_release.content | ConvertFrom-Json | Select-Object -ExpandProperty assets | Select-Object -ExpandProperty browser_download_url

# If the version is latest, show the latest release version
if ($version -eq "latest") {
    $latest_release_version = $latest_release.content | ConvertFrom-Json | Select-Object -ExpandProperty tag_name
    Write-Host "Latest release version: $latest_release_version"
}

# Select 7z file
$latest_release_url = $latest_release_url | Where-Object { $_ -like "*7z" }
Write-Output "Downloading latest 'GenshinImpact_AutoTrack_DLL' release from $latest_release_url"

# Download 7z file
Invoke-WebRequest -Uri $latest_release_url -OutFile "cvAutoTrack.7z"

# Extract 7z file to cvAutoTrack
7z x cvAutoTrack.7z -o"cvAutoTrack" -y

# Remove 7z file
Remove-Item cvAutoTrack.7z