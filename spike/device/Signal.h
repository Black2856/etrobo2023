/*
 * クラス名:Signal
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#ifndef SIGNAL_H
#define SIGNAL_H

#include <opencv2/opencv.hpp>
#include <netinet/in.h>
#include <string>

class Signal{
public:
    Signal(int pcPort);
    ~Signal();

    bool connect_s();
    void close_s();
    bool sendImage(cv::Mat image, const char* fileName);
    // 使用例
    // sendString("Hello World");
    bool sendString(const char* str);
    // 失敗時 "" を返却
    std::string recvString();
    bool recvFile();


private:
    // 広範的データを送信する関数
    bool sendItem(const void *buf, uint32_t len);
    void dispBool(bool b);
    // ソケット情報
    int sock;
    // サーバーのアドレスとポートの設定
    struct sockaddr_in addr;
    int pcPort;
};

#endif // SIGNAL_H