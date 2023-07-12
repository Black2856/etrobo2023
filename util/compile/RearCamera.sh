#!/bin/bash

devicepath="./spike/device/"

g++ "$devicepath"RearCamera.c -o "$devicepath"tekephoto -I/usr/include/opencv4/ -lopencv_core -lopencv_videoio -lopencv_imgcodecs

exit 0