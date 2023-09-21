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
    // インスタンス取得
    static Signal& getInstance();

    bool connect_s();
    void close_s();
    bool sendImage(cv::Mat image);
    // 使用例
    // sendString("Hello World");
    bool sendString(const char* str);
    std::string recvString();


private:
    Signal(); // プライベートコンストラクタ
    ~Signal();
    static Signal* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Signal(Signal const&);
    void operator=(Signal const&);

    // 広範的データを送信する関数
    bool sendItem(const void *buf, size_t len);
    void dispBool(bool b);
    // ソケット情報
    int sock;
    // サーバーのアドレスとポートの設定
    struct sockaddr_in addr;
};

#endif // SIGNAL_H