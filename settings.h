#ifndef SETTINGS_H

#define DEBUG false
#define SIM false

//ポート割り当て
#ifndef PORT
#define LEFTWHEEL PORT_C
#define RIGHTWHEEL PORT_B
#define COLORSENSOR PORT_1
#define GYROSENSOR PORT_2
#define TOUCHSENSOR PORT_3
#define SONARSENSOR PORT_4
#define PORT
#endif

//シュミレータ環境の値
#define SIM_MIN_BRIGHTNESS 2
#define SIM_MAX_BRIGHTNESS 35
#define SIM_AVG_BRIGHTNESS 18

//色識別閾値
#define RED_THRESHOLD 2.0
#define GREEN_THRESHOLD 2.0
#define BLUE_THRESHOLD 1.7
#define YELLOW_THRESHOLD 2.5

#define SECOND_THRESHHOLD 1.25
#define BRIGHTNESS_THRESHHOLD 40 //0 ~ 255

//動作周期
#define ORDER_T 20
#define BLUETOOTH_T 100

//走行体情報
#define WHEEL 5 //車輪半径(cm)
#define BETWHEENWHEEL 15 //車輪間距離(cm)
#define ROTATE_CORRECTION 0.97//回転量の補正

#define SETTINGS_H
#endif