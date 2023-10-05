/*
クラス名:TakePhoto
作成日:2023/07/31
作成者:杉本
*/
#include "TakePhoto.h"
#include <stdio.h>

TakePhoto::TakePhoto():
    device(DeviceInOut::getInstance()){
    }

void TakePhoto::first(int num) {
    this->num = num;
    for(int i=1; i<=this->num; i++) {
        char fileName[5];

        sprintf(fileName, "%d", i);
        device.camera_addToQueue(fileName);
    }
    device.camera_takePhoto();
}

bool TakePhoto::execute(){
    if (device.camera_getQueueSize() != 0) {
        print("TakePhoto:false\n");
        return false;
    }
    print("TakePhoto:true\n");
    return true;
}