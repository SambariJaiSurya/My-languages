@echo off
echo Building MAZ Programming Language Compiler...
g++ -std=c++20 -O2 -I src src/lexer/Lexer.cpp src/parser/Parser.cpp src/runtime/Environment.cpp src/runtime/Interpreter.cpp src/main.cpp -o maz.exe
if %ERRORLEVEL% EQU 0 (
    echo [Build Success] maz.exe generated successfully.
) else (
    echo [Build Failed] Compilation encountered errors.
    exit /b %ERRORLEVEL%
)

