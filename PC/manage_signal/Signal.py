import os
import cv2
import numpy as np
import socket
import struct

IP_ADDR = "0.0.0.0"
PORT = 8080
IMG_PATH = "" # 画像保存先path
# 環境差調整用定数
SIZE_LEN = 8
if(SIZE_LEN == 4):
    FORMAT = "I"
elif(SIZE_LEN == 8):
    FORMAT = "Q"

class Signal:
    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.conn = None
        self.socket.settimeout(120)
        self.socket.setblocking(True)

    def __del__(self):
        self.close()

        
    def open(self) -> bool:
        try:
            self.socket.bind((IP_ADDR, PORT))
            self.socket.listen(1)
            print("Server started : ", IP_ADDR, ":", PORT, sep='')
            self.conn, addr = self.socket.accept()
            print('Connected by', addr)
            return True
        except:
            return False

    def close(self) -> None:
        try:
            self.conn.close()
            self.socket.shutdown(socket.SHUT_RDWR)
            self.socket.close()
        except:
            pass
        
    # 広範的データを受信する関数
    def __recvItem(self):
        # データのサイズを受信
        buffer_size = self.conn.recv(SIZE_LEN)
        print("  data size :", buffer_size)
        # バイナリデータを数値に変換
        buffer_size = struct.unpack(FORMAT, buffer_size)[0]
        print("  len       :", buffer_size)

        # データを受信
        data = b''
        while len(data) < buffer_size:
            packet = self.conn.recv(buffer_size - len(data))
            if not packet:
                break
            data += packet
        print("  data      :", data[:20])
        print("  Succeed")
        return data
    
    # 画像データを受信する関数
    def recvImage(self) -> (np.ndarray, str):
        print("Recv Image")
        # バイナリデータを受信
        binary_data = self.__recvItem()
        # 受信したデータをデコード
        frame_data = np.frombuffer(binary_data, dtype=np.uint8)

        # データを画像に変換
        frame = cv2.imdecode(frame_data, 1)
        # ファイル名受信
        text  = self.recvString()
        return (frame, text)
    
    # 文字列データを受信する関数
    def recvString(self) -> str:
        print("Recv String")
        data = self.__recvItem()
        # 受信したデータをデコード
        st = data.decode('utf-8')
        return st

    # 文字列を送信する関数
    def sendString(self, text) -> None:
        print("Send String")
        data = text.encode('utf-8')
        size = struct.pack(FORMAT, len(data))
        print("  len       :", len(data))
        print("  data      :", data[:20])
        
        self.conn.sendall(size)
        self.conn.sendall(data)
        print("  Succeed")

    def sendFile(self, filePath:str) -> bool:
        print("Send File")
        try:
            # ファイルを読み込みモードでオープン
            with open(filePath, 'r') as file:
                # ファイルからデータを読み込み
                file_contents = file.read()
                
                # ファイルの内容を表示
                print("File contents:")
                print(file_contents)
        except FileNotFoundError:
            print(f"{filePath} が見つかりません")
            return False
        except IOError:
            print("ファイルの読み込みエラーが発生しました")
            return False
        self.sendString(file_contents)
        self.sendString(os.path.basename(filePath))
        return True


if __name__ == "__main__":
    signal = Signal()
    signal.open()

    img, string = signal.recvImage()
    #string = signal.recvString()
    signal.sendFile("requirements.txt")

    signal.close()
        
    # 画像を保存
    cv2.imwrite(f'{string}', img)