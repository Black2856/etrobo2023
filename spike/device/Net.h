/*
 * クラス名:Net
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#ifndef NET_H
#define NET_H

#include <opencv2/opencv.hpp>
#include <netinet/in.h>

class Net{
public:
    // インスタンス取得
    static Net& getInstance();

    bool open();
    void close();
    bool sendImage(cv::Mat image);


private:
    Net(); // プライベートコンストラクタ
    ~Net();
    static Net* instance; // シングルトンオブジェクトへのポインタ

    // コピーおよび代入演算子は禁止
    Net(Net const&);
    void operator=(Net const&);

    // ソケット情報
    int clientSocket;
    // サーバーのアドレスとポートの設定
    sockaddr_in serverAddress{};
};

#endif // NET_H