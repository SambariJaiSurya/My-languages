Write-Host "Building MAZ Programming Language Compiler..." -ForegroundColor Cyan
g++ -std=c++20 -O2 -I src src/lexer/Lexer.cpp src/parser/Parser.cpp src/runtime/Environment.cpp src/runtime/Interpreter.cpp src/main.cpp -o maz.exe
if ($LASTEXITCODE -eq 0) {
    Write-Host "[Build Success] maz.exe generated successfully." -ForegroundColor Green
} else {
    Write-Host "[Build Failed] Compilation encountered errors." -ForegroundColor Red
    exit $LASTEXITCODE
}

