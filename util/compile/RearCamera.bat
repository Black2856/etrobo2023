@echo off
setlocal

set devicepath="%~1/spike/device/"

g++ %devicepath%RearCamera.c -o %devicepath%tekephoto -I/usr/include/opencv4/ -lopencv_core -lopencv_videoio -lopencv_imgcodecs

exit /b 0