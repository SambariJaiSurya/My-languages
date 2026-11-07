# Search for the symbols extension folder
$paths = @(
    "$env:USERPROFILE\.antigravity-ide\extensions",
    "$env:USERPROFILE\.antigravity\extensions",
    "$env:USERPROFILE\.vscode\extensions",
    "$env:APPDATA\Antigravity\extensions",
    "$env:APPDATA\Code\User\extensions"
)

foreach ($p in $paths) {
    if (Test-Path $p) {
        Write-Host "Checking: $p"
        Get-ChildItem -Path $p -Filter "*symbol*" -ErrorAction SilentlyContinue | ForEach-Object {
            Write-Host "Found Symbol Icons at: $($_.FullName)" -ForegroundColor Green
        }
    }
}

