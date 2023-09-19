/*
 * クラス名:Signal
 * 作成日:2023/05/12
 * 作成者:杉本
 */
#include "Signal.h"
#include "setting.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <errno.h>

Signal* Signal::instance = NULL;

Signal::Signal():
    sock(socket(AF_INET, SOCK_STREAM, 0)) {
        if (sock == -1) {
            printf("socket error\n");
        }
        // 構造体を全て0にセット
        memset(&addr, 0, sizeof(struct sockaddr_in));
        // サーバーのIPアドレスとポートの情報を設定
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(PC_IP_ADDRESS);
        addr.sin_port = htons((unsigned short)PC_PORT);
    }

Signal::~Signal() {
    close_s();
}

Signal& Signal::getInstance() {
    if (!instance) {
        instance = new Signal();
    }
    return *instance;
}

bool Signal::connect_s() {
    if (
        connect(
            this->sock,
            (struct sockaddr*)&this->addr,
            sizeof(struct sockaddr_in)
        ) == -1
    ) {
        perror("connect");
        close(this->sock);
        printf("connect error\n");
        return false;
    }
    printf("Finish connect!\n");
    return true;
}

void Signal::close_s() {
    // ソケットを閉じる
    close(this->sock);
}

bool Signal::sendItem(const void *buf, size_t len) {
    printf("data : %p\n" , buf);
    printf("len  : %ld\n", len);

    // データのサイズを先に送信
    if (send(this->sock, &len, sizeof(len), 0) == -1) {
        return false;
    }

    // データを送信
    if (send(this->sock, buf, len, 0) == -1) {
        return false;
    }
    return true;
}

bool Signal::sendImage(cv::Mat image) {
    // 画像データを一時的に格納するバッファ
    std::vector<uchar> buffer;
    //PNGでの出力用パラメータ
    std::vector<int> param(2);
    param[0] = cv::IMWRITE_PNG_COMPRESSION;
    param[1] = 3;//default(3)  0-9.
    // フレームをバッファにエンコード
    if(cv::imencode(".png", image, buffer, param)) {
        printf("Encoding succeed\n");
    } else {
        printf("Encoding failed\n");
    }

    return sendItem(buffer.data(), buffer.size());
}

bool Signal::sendString(const char* str) {
    return sendItem(str, strlen(str));
}
