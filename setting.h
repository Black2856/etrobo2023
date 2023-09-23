#ifndef SETTINGS_H
#define SETTINGS_H

// MAKE_SIMが定義されていた場合シミュレータ環境

// spikeポート設定
#define SONAR_SENSOR PORT_3
#define TOUCH_SENSOR PORT_1
#define GYRO_SENSOR PORT_4
#define COLOR_SENSOR PORT_2
#define LEFT_WHEEL PORT_C
#define RIGHT_WHEEL PORT_B

//汎用
#define PI 3.1415926535

// 走行体設定
#ifdef MAKE_SIM
    #define TREAD 150.0         // 車体トレッド幅（mm） spike = 126 EV3 = 150.0
    #define LEFT_WHEEL_POWER 1.0  //左車輪の出力量
    #define RIGHT_WHEEL_POWER 1.0 //右車輪の出力量
    #define TIRE_DIAMETER 100.0 // タイヤ直径（mm）
#define FRICTIONAL 1.25 //摩擦倍率
#else  //SPIKE
    #define TREAD 125.0
    #define LEFT_WHEEL_POWER 1.0
    #define RIGHT_WHEEL_POWER 1.0
    #define TIRE_DIAMETER 100.0 // タイヤ直径（mm）
#define FRICTIONAL 1.0 //zero4は0.8845 0.915 本番:0.9455
#endif // MAKE_SIM

#define CAMERA_NUMBER 0 // カメラデバイス番号（通常は0）を指定
#define CYCLE 1000 * 10 // 処理周期(usec)
#define IMG_QUEUE "Queue.txt" // 撮影待機リストファイル名
#ifdef MAKE_SIM
    #define IMG_PATH "/home/iwasaki/etrobo/workspace/img/" // 画像保存先path
    #define IMG_QUEUE_PATH "/home/iwasaki/etrobo/workspace/simdist/etrobo2023/__ev3rtfs/" IMG_QUEUE // 撮影待機リストファイル名
#else
    #define IMG_PATH "/home/robo/work/RasPike/sdk/workspace/img/" // 画像保存先path
    #define IMG_QUEUE_PATH "/home/robo/work/RasPike/sdk/workspace/" IMG_QUEUE // 撮影待機リスト
#endif
#define IMG_FILENAME_LEN 5 // ファイルネームの最大長
#define RECORD_LIMIT 1000  // センサーデータの最大記録数  記録秒数 = CYCLE * RECORD_LIMIT

// 通信設定
#define PC_IP_ADDRESS "192.168.10.8" // 受信時アドレス
#define RECV_PORT 8081 // 受信用port番号
#define SEND_PORT 8080 // 送信用port番号
#define RECV_PATH "/home/robo/work/RasPike/sdk/workspace/etrobo2023/spike/recvFile/" // 受信ファイル保存先path
//#define RECV_PATH "/home/iwasaki/etrobo/" // 受信ファイル保存先path
#define RECV_CYCLE 500 // 受信周期（ミリ秒単位）
#define SEND_CYCLE 500 // 送信周期（ミリ秒単位）

#endif  // SETTINGS_H