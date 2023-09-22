import os
from Signal import Signal
from parallelProcessing import ParallelProcessing

RECV_PORT = 8080 # 受信用PORT番号
SEND_PORT = 8081 # 送信用PORT番号
IMG_PATH    = os.path.dirname(os.path.abspath(__file__)) + "/../recv_image/" # 画像保存先path
FOLDER_PATH = os.path.dirname(os.path.abspath(__file__)) + "/../send_folder/" # 送信file保存先path

if __name__ == "__main__":
    class Recv(ParallelProcessing):
        def __init__(self):
            super().__init__()
            self.cycle = 500 #500msの周期で動作
            self.a = -1
            print("受信用サーバ起動")
            self.signal = Signal(RECV_PORT)
            
        def __del__(self):
            self.signal.close()
            
        def execute(self):
            if (self.a == -1):
                self.signal.open()
                self.a += 1
            self.a += 1
            self.signal.recvImage(IMG_PATH)
            # 10枚画像を受信したら終了
            if self.a >= 10:
                self.stopThread()
                
    class Send(ParallelProcessing):
        def __init__(self):
            super().__init__()
            self.cycle = 500 #500msの周期で動作
            self.a = -1
            print("送信用サーバ起動")
            self.signal = Signal(SEND_PORT)
            
        def __del__(self):
            self.signal.close()

        def execute(self):
            if (self.a == -1):
                self.signal.open()
                self.a += 1
            file_list = []
            # ディレクトリ内のファイルを確認
            try:
                for filename in os.listdir(FOLDER_PATH):
                    file_path = os.path.join(FOLDER_PATH, filename)
                    if os.path.isfile(file_path):
                        if (filename != ".gitkeep"):
                            file_list.append(filename)
            except OSError as e:
                print(f"エラー: {e}")
            # ファイルを送信
            for file in file_list:
                self.a += 1
                self.signal.sendFile(FOLDER_PATH + file)
            # 10個ファイルを送信したら終了
            if self.a >= 10:
                self.stopThread()
    
    # 受信用サーバ起動
    recv = Recv()
    recv.startThread()
    # 送信用サーバ起動
    recv = Send()
    recv.startThread()