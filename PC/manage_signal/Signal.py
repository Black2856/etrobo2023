import os
import cv2
import numpy as np
import socket
import struct

IP_ADDR = "127.0.0.10"
PORT = 8080

class Signal:
    def __init__(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.socket.settimeout(120)
        self.close()

    def __del__(self):
        self.close()

        
    def connect(self) -> bool:
        self.socket.bind((IP_ADDR, PORT))
        self.socket.listen(5)
        print("Server started : ", IP_ADDR, ":", PORT, sep='')
        return True

    def close(self) -> None:
        try:
            self.socket.shutdown(socket.SHUT_RDWR)
            self.socket.close()
        except:
            pass
        
    # 広範的データを受信する関数
    def recvItem(self, conn):
        with conn:
            # データのサイズを受信
            buffer_size = conn.recv(4)
            buffer_size = struct.unpack('I', buffer_size)[0]
            # データを受信
            data = b''
            while len(data) < buffer_size:
                packet = conn.recv(buffer_size - len(data))
                if not packet:
                    break
                data += packet
        
        return data
    
    # 画像データを受信する関数
    def recvImage(self, conn):
        data = self.recvItem(conn)
        # 受信したデータをデコード
        frame_data = np.frombuffer(data, dtype=np.uint8)
        # データを画像に変換
        frame = cv2.imdecode(frame_data, 1)
        return frame
    
    # 文字列データを受信する関数
    def recvString(self, conn):
        data = self.recvItem(conn)
        # 受信したデータをデコード
        st = data.decode('utf-8')
        return st
    
    def accept(self):
        conn, addr = self.socket.accept()
        print('Connected by', addr)
        return conn
        

if __name__ == "__main__":
    signal = Signal()
    signal.connect()
    conn = signal.accept()
    print("通信成功")
    """
    
    image  = signal.recvImage(conn)
    string = signal.recvString(conn)
    """
    conn.close()
    signal.close()
        
    # 画像を保存
    #cv2.imwrite(f'{string}', image)