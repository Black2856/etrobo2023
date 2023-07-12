@echo off
setlocal

cd /d %~dp0

python util/fix/fix.py ./Makefile.inc
python util/fix/fix.py ./app.cfg

if "%~1"=="" (
    set comment="%date%_%time%"
) else (
    set comment="%~1"
)

git add . & ^
git commit -m %comment% & ^
git push -f

exit /b 0