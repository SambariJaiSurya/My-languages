$ErrorActionPreference = "Continue"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Running MAZ Automated Test Suite " -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

$examples = Get-ChildItem -Path "examples/*.maz"
$passed = 0
$total = 0

foreach ($ex in $examples) {
    $total++
    Write-Host "Testing $($ex.Name)..." -NoNewline
    $output = & .\maz.exe run $ex.FullName 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host " [PASS]" -ForegroundColor Green
        $passed++
    } else {
        Write-Host " [FAIL]" -ForegroundColor Red
        Write-Host $output
    }
}

Write-Host "----------------------------------------"
$color = "Green"
if ($passed -ne $total) {
    $color = "Red"
}
Write-Host "Results: $passed / $total passed." -ForegroundColor $color
