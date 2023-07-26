/*
クラス名:OnLineMove
作成日:2023/7/26
作成者:
*/
#ifdef ON_LINE_MOVE_H
#define ON_LINE_MOVE_H

class OnLineMove{
public:
    OnLineMove();
private:
    DeviceInOut& device;
    Calc& calc = Calc::getInstance();
    unit::calibration calibration;
    Manual manual;
};

#endif