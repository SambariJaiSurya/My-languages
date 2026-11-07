@echo off
setlocal enabledelayedexpansion
title MAZ Language 1-Click Setup

echo ========================================================
echo        MAZ Programming Language 1-Click Setup
echo ========================================================
echo.

powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0setup.ps1"

echo.
echo ========================================================
echo   Setup finished! Press any key to exit.
echo ========================================================
pause >nul

