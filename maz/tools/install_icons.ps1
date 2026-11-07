Write-Host "Automating MAZ setup for VS Code & Antigravity..." -ForegroundColor Cyan

$source = "e:\coding stuff\my languages\maz\tools\vscode-extension"
$mazIcon = "e:\coding stuff\my languages\maz\tools\vscode-extension\icons\maz.svg"

# 1. Install extension into VS Code, Antigravity, and all variations
$targetDirs = @(
    "$env:USERPROFILE\.vscode\extensions\maz-language-support",
    "$env:USERPROFILE\.vscode-shared\extensions\maz-language-support",
    "$env:USERPROFILE\.antigravity-ide\extensions\maz-language-support",
    "$env:USERPROFILE\.antigravity\extensions\maz-language-support"
)

foreach ($target in $targetDirs) {
    try {
        $parent = Split-Path $target
        if (!(Test-Path $parent)) {
            New-Item -ItemType Directory -Force -Path $parent | Out-Null
        }
        Copy-Item -Recurse -Force $source $target -ErrorAction SilentlyContinue
        Write-Host "[OK] Installed extension to $target" -ForegroundColor Green
    } catch {
        Write-Host "[Warning] Could not copy to $target" -ForegroundColor Yellow
    }
}

# 2. Inject MAZ icon into Symbol Icons theme across all IDEs
$extensionRoots = @(
    "$env:USERPROFILE\.vscode\extensions",
    "$env:USERPROFILE\.antigravity-ide\extensions",
    "$env:USERPROFILE\.antigravity\extensions"
)

foreach ($root in $extensionRoots) {
    if (Test-Path $root) {
        $symbolExts = Get-ChildItem -Path $root -Filter "*miguelsolorio.symbols*" -Directory -ErrorAction SilentlyContinue
        foreach ($ext in $symbolExts) {
            $destIconDir = Join-Path $ext.FullName "dist\icons"
            if (Test-Path $destIconDir) {
                Copy-Item -Force $mazIcon (Join-Path $destIconDir "maz.svg")
            }
            $manifest = Join-Path $ext.FullName "dist\symbols.json"
            if (Test-Path $manifest) {
                try {
                    $json = Get-Content $manifest -Raw | ConvertFrom-Json
                    if (-not $json.iconDefinitions.maz) {
                        $json.iconDefinitions | Add-Member -NotePropertyName "maz" -NotePropertyValue @{ iconPath = "./icons/maz.svg" } -Force
                    }
                    if (-not $json.fileExtensions.maz) {
                        $json.fileExtensions | Add-Member -NotePropertyName "maz" -NotePropertyValue "maz" -Force
                    }
                    $json | ConvertTo-Json -Depth 10 | Set-Content $manifest
                    Write-Host "[OK] Injected MAZ icon into Symbol Icons theme!" -ForegroundColor Green
                } catch {}
            }
        }
    }
}

# 3. Automatically activate MAZ icon theme in VS Code & Antigravity settings
$settingsPaths = @(
    "$env:APPDATA\Code\User\settings.json",
    "$env:APPDATA\Antigravity\User\settings.json",
    "$env:APPDATA\Antigravity IDE\User\settings.json"
)

foreach ($settingsFile in $settingsPaths) {
    try {
        $parent = Split-Path $settingsFile
        if (!(Test-Path $parent)) {
            New-Item -ItemType Directory -Force -Path $parent | Out-Null
        }
        $settings = @{}
        if (Test-Path $settingsFile) {
            try {
                $raw = Get-Content $settingsFile -Raw
                if ($raw.Trim().Length -gt 0) {
                    $settings = $raw | ConvertFrom-Json -AsHashtable
                }
            } catch {}
        }
        $settings["workbench.iconTheme"] = "maz-icon-theme"
        if (-not $settings["files.associations"]) {
            $settings["files.associations"] = @{}
        }
        $settings["files.associations"]["*.maz"] = "maz"

        $settings | ConvertTo-Json -Depth 10 | Set-Content $settingsFile
        Write-Host "[OK] Activated MAZ icon theme in $settingsFile" -ForegroundColor Green
    } catch {
        Write-Host "[Warning] Could not update $settingsFile" -ForegroundColor Yellow
    }
}

Write-Host "`nSetup completely finished for both VS Code and Antigravity!" -ForegroundColor Green
