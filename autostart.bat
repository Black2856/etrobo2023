@echo off
setlocal ENABLEDELAYEDEXPANSION
set PATHLF=!cd:\=^

!

for /F "delims=\" %%a in ("!PATHLF!") do (set cDIR=%%a)
endlocal && set cDIR=%cDIR%


git pull
cd ../
make img=%cDIR%
make start