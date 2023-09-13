import os
import cv2
import numpy as np
import socket
import struct

IP_ADDR = ""
PORT = 8080

class BlockingServerBase:
    def __init__(self):
        self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.__socket.settimeout(10)
        self.close()

    def __del__(self):
        self.close()

        
    def connect(self) -> None:
        self.__socket.bind((IP_ADDR, PORT))
        self.__socket.listen(1)
        print("Server started :", IP_ADDR)

    def close(self) -> None:
        try:
            self.__socket.shutdown(socket.SHUT_RDWR)
            self.__socket.close()
        except:
            pass
        
    def accept(self) -> None:
        conn, _ = self.__socket.accept()

        with conn:
            print('Connected by', IP_ADDR)
            buffer_size = conn.recv(4)
            buffer_size = struct.unpack('I', buffer_size)[0]
            # フレームデータを受信
            data = b''
            while len(data) < buffer_size:
                packet = conn.recv(buffer_size - len(data))
                if not packet:
                    break
                data += packet
            # 受信したデータをデコード
            frame_data = np.frombuffer(data, dtype=np.uint8)
            # データを画像に変換
            frame = cv2.imdecode(frame_data, 1)
            
            # 文字列の長さを受信
            str_size = conn.recv(4)
            str_size = struct.unpack('I', str_size)[0]

            # 文字列を受信
            received_str = conn.recv(str_size).decode('utf-8')
            
            # 画像を保存
            cv2.imwrite(f'{received_str}', frame)

        self.close()

