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
#include <fstream>

Signal::Signal(int pcPort):
    sock(socket(AF_INET, SOCK_STREAM, 0)) {
        if (sock == -1) {
            printf("socket error\n");
        }
        // 構造体を全て0にセット
        memset(&addr, 0, sizeof(struct sockaddr_in));
        // サーバーのIPアドレスとポートの情報を設定
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(PC_IP_ADDRESS);
        addr.sin_port = htons((unsigned short)pcPort);
        this->pcPort = pcPort;
    }

Signal::~Signal() {
    close_s();
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
        printf("connect error\n");
        return false;
    }
    printf("Connected by ('" PC_IP_ADDRESS "', %d)\n", this->pcPort);
    return true;
}

void Signal::close_s() {
    // ソケットを閉じる
    close(this->sock);
}

void Signal::dispBool(bool b) {
    if(b) {
        printf("  Succeed\n");
    } else {
        printf("  Failed\n");
    }
}

bool Signal::sendItem(const void *buf, size_t len) {
    printf("  len  : %ld\n", len);

    // データのサイズ、実体を送信
    if (
        send(this->sock, &len, sizeof(len), 0) &&
        send(this->sock, buf, len, 0)
    ) {
        dispBool(true);
        return true;
    }
    dispBool(false);
    return false;
}

bool Signal::sendImage(cv::Mat image, const char* fileName) {
    printf("Send Image\n");
    // 画像データを一時的に格納するバッファ
    std::vector<uchar> buffer;
    //PNGでの出力用パラメータ
    std::vector<int> param(2);
    param[0] = cv::IMWRITE_PNG_COMPRESSION;
    param[1] = 3;//default(3)  0-9.
    // フレームをバッファにエンコード
    if(cv::imencode(".png", image, buffer, param)) {
        printf("  Encoding succeed\n");
    } else {
        printf("  Encoding failed\n");
    }
    // 画像、ファイル名送信
    return (sendItem(buffer.data(), buffer.size()) && sendString(fileName));

}

bool Signal::sendString(const char* str) {
    printf("  name : %s\n", str);
    return sendItem(str, strlen(str));
}

std::string Signal::recvString() {
    // データのサイズを受信
    int buffer_size;
    int bytesRead;
    bytesRead = recv(this->sock, &buffer_size, 8, 0);
    if (bytesRead == -1) {
        printf("Failed to recv string size\n");
        dispBool(false);
        return "";
    }
    printf("  len  : %d\n", buffer_size);
    // データを受信
    char buffer[buffer_size];
    bytesRead = recv(this->sock, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        printf("Failed to recv string\n");
        dispBool(false);
        return "";
    }

    // 文字列に変換
    buffer[bytesRead] = '\0';
    // stringに変換
    std::string text(buffer);
    printf("  data : %s\n", text.c_str());
    dispBool(true);
    return text;
}

bool Signal::recvFile() {
    printf("Recv File\n");
    // ファイルを受信
    std::string content = recvString();
    // ファイル名を受信
    std::string fileName = recvString();
    char path[150];
    sprintf(path, RECV_PATH "%s", fileName.c_str());
    // ファイルを保存
    std::ofstream file(path);
    if (!file.is_open()) {
        printf("File not published\n");
        return false;
    }
    file << content.c_str();
    file.close();
    return true;
}