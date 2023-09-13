/*
 * クラス名:Signal
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#ifndef SIGNAL_H
#define SIGNAL_H

#include <opencv2/opencv.hpp>
#include <netinet/in.h>

class Signal{
public:
    // インスタンス取得
    static Signal& getInstance();

    bool connect_s();
    void close_s();
    bool sendImage(cv::Mat image);


private:
    Signal(); // プライベートコンストラクタ
    ~Signal();
    static Signal* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Signal(Signal const&);
    void operator=(Signal const&);

    // ソケット情報
    int clientSocket;
    // サーバーのアドレスとポートの設定
    sockaddr_in serverAddress{};
};

#endif // SIGNAL_H