import os, sys
os.chdir(os.path.dirname(os.path.abspath(__file__)))
base = os.path.dirname(os.path.abspath(__file__))
sys.path.append(f"{base}../install")

from Signal import Signal
from ..install.parallelProcessing import ParallelProcessing

RECV_PORT = 8080 # 受信用PORT番号
SEND_PORT = 8081 # 送信用PORT番号
IMG_PATH    = base + "/recv_image/" # 画像保存先path
FOLDER_PATH = base + "/send_folder/" # 送信file保存先path

class Recv(ParallelProcessing):
    def __init__(self):
        super().__init__()
        self.cycle = 500 #500msの周期で動作
        self.a = -1
        self.b = 4 # 受信最大枚数
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
        # 指定枚数画像を受信したら終了
        if self.a >= self.b:
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
                    if (filename == ".exit"):
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

class MainSignal(ParallelProcessing):
    """
    通信機能の管理
    """
    def __init__(self):
        super().__init__()
        self.__cycle = 500
        # 受信用サーバ起動
        self.__recv = Recv()
        self.__recv.startThread()
        # 送信用サーバ起動
        self.__send = Send()
        self.__send.startThread()

    def __del__(self):
        self.__recv.stopThread()
        self.__send.stopThread()

    def execute(self):
        # 生存確認 
        if self.__send.threadState == False or self.__recv.threadState == False:
            self.__recv.stopThread()
            print("[ 通信 ]停止")
            self.stopThread()