@echo off

if "%~1"=="" (
    exit /b 1
)

call %~dp0/RearCamera.bat "%~1"

exit /b 0