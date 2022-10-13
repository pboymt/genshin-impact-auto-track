# Read all declarations from the 'src/main.h' file
$declarations = Get-Content -Path src/main.h
# Filter out all declarations that are functions
$functions = $declarations | Where-Object { $_ -match '^Napi::' }
# Output all function N-API binding in $functions
foreach ($function in $functions) {
    $functionName = $function -replace '^Napi::\S+\s+', ''
    $oName = $functionName -replace '\(.*\);$', ''
    # Remove 'AT' from the function name
    $nName = $oName -replace '^AT', ''
    # Convert first character to lower case
    $nName = $nName.Substring(0, 1).ToLower() + $nName.Substring(1)
    # Output the function name
    Write-Host "exports.Set(""$nName"", Napi::Function::New(env, $oName));"
}

# Output all function TypeScript declarations in $functions
foreach ($function in $functions) {
    $functionName = $function -replace '^Napi::\S+\s+', ''
    $oName = $functionName -replace '\(.*\);$', ''
    # Remove 'AT' from the function name
    $nName = $oName -replace '^AT', ''
    # Convert first character to lower case
    $nName = $nName.Substring(0, 1).ToLower() + $nName.Substring(1)
    # Output the function name
    Write-Host "export function $nName(): unknown;"
}