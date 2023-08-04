/*
クラス名:TakePhoto
作成日:2023/07/31
作成者:杉本
*/
#include "TakePhoto.h"
#include "setting.h"
#include <stdio.h>

TakePhoto::TakePhoto():
    device(DeviceInOut::getInstance()){
    }

void TakePhoto::first(int num) {
    this->num = num;
    for(int i=0; i<this->num; i++) {
        char fileName[IMG_FILENAME_LEN];

        sprintf(fileName, "%d", i);
        device.camera_addToQueue(fileName);
    }
    device.camera_takePhoto();
}

bool TakePhoto::execute(){
    if (device.camera_getQueueSize() > 0) {
        return false;
    }
    return true;
}