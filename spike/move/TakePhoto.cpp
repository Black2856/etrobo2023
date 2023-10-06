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
    for(int i=1; i<=this->num; i++) {
        char fileName[5];

        sprintf(fileName, "%d", i);
        device.camera_addToQueue(fileName);
    }
    device.camera_takePhoto();
    time = device.clock_now();
}

bool TakePhoto::execute(){
    // 撮影失敗時走行再開
    if ((device.clock_now() - time) >= PHOTO_FAILED_TIME) {
        return true;
    }
    if (device.camera_getQueueSize() != 0) {
        return false;
    }
    return true;
}