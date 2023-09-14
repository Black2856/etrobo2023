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

Signal* Signal::instance = NULL;

Signal::Signal():
    clientSocket(socket(AF_INET, SOCK_STREAM, 0)) {
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(PC_IP_ADDRESS);
        serverAddress.sin_port = htons(PC_PORT);
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
            this->clientSocket,
            reinterpret_cast<sockaddr*>(&this->serverAddress),
            sizeof(this->serverAddress)
        ) == -1
    ) {
        close(this->clientSocket);
        return false;
    }
    return true;
}

void Signal::close_s() {
    // ソケットを閉じる
    close(this->clientSocket);
}

bool Signal::sendItem(const void *buf, size_t len) {
    // データのサイズを先に送信
    if (send(this->clientSocket, &len, sizeof(len), 0) == -1) {
        return false;
    }

    // データを送信
    if (send(this->clientSocket, buf, len, 0) == -1) {
        return false;
    }
    return true;
}

bool Signal::sendImage(cv::Mat image) {
    // 画像データを一時的に格納するバッファ
    std::vector<uchar> buffer;
    // フレームをバッファにエンコード
    cv::imencode(".png", image, buffer);

    return sendItem(buffer.data(), buffer.size());
}

bool Signal::sendString(const char* str) {
    return sendItem(str, strlen(str));
}
