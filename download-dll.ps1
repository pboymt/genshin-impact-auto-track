# Check if directory cvAutoTrack exists
if (Test-Path -Path ".\cvAutoTrack") {
    # If it exists, skip download and exit
    Write-Host "cvAutoTrack directory already exists. Skipping download."
    exit 0
}

$latest_release = Invoke-WebRequest "https://api.github.com/repos/GengGode/GenshinImpact_AutoTrack_DLL/releases/latest"
$latest_release_url = $latest_release.content | ConvertFrom-Json | Select-Object -ExpandProperty assets | Select-Object -ExpandProperty browser_download_url
Write-Output "Downloading latest 'GenshinImpact_AutoTrack_DLL' release from $latest_release_url"
# Select 7z file
$latest_release_url = $latest_release_url | Where-Object { $_ -like "*7z" }
# Download 7z file
Invoke-WebRequest -Uri $latest_release_url -OutFile "cvAutoTrack.7z"
# Extract 7z file to cvAutoTrack
7z x cvAutoTrack.7z -o"cvAutoTrack" -y
# Remove 7z file
Remove-Item cvAutoTrack.7z