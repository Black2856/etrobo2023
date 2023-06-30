@echo off

call build/fix.bat

setlocal
if "%~1"=="" (
    set comment="%date%_%time%"
) else (
    set comment="%~1"
)
cd /d %~dp0 && ^
git add . & ^
git commit -m %comment% & ^
git push -f

exit /b 0