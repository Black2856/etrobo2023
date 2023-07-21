@echo off
setlocal

cd /d %~dp0
cd ../

python util/python/update.py ./Makefile.inc
python util/python/update.py ./app.cfg

if "%~1"=="" (
    set comment="%date%_%time%"
) else (
    set comment="%~1"
)

git add . & ^
git commit -m %comment% & ^
git push

exit /b 0