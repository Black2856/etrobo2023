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
            
        def stopThread(self):
            super().stopThread()
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
        
        def stopThread(self):
            super().stopThread()
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
                        # exit.txtが存在した場合処理を終了する
                        if (filename == "exit.txt"):
                            os.remove(file_path)
                            self.stopThread()
                            return
            except OSError as e:
                print(f"エラー: {e}")
            # ファイルを送信
            for file in file_list:
                self.a += 1
                self.signal.sendFile(file_path)
                # 送信したファイルを削除
                try:
                    os.remove(file_path)
                except OSError as e:
                    print(f"{file_path} の削除に失敗しました。エラー: {e}")
            # 10個ファイルを送信したら終了
            if self.a >= 10:
                self.stopThread()
    
    # 受信用サーバ起動
    recv = Recv()
    recv.startThread()
    # 送信用サーバ起動
    send = Send()
    send.startThread()
    while (send.threadState):
        pass
    print("stop")
    recv.stopThread()