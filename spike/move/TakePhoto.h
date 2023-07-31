/*
クラス名:TakePhoto
作成日:2023/07/31
作成者:杉本
*/
#ifndef TAKE_PHOTO_H
#define TAKE_PHOTO_H

#include "DeviceInOut.h"

class TakePhoto {
public:
    TakePhoto();
    /**
    * @param num 撮影枚数
    */
    void first(int num);
    bool execute(); // 撮影完了時trueを返す
private:
    DeviceInOut& device;
    int num;
};

#endif  // TAKE_PHOTO_H