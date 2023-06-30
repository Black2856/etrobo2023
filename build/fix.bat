@echo off

python ./build/fix.py ./Makefile.inc
python ./build/fix.py ./app.cfg

exit /b 0