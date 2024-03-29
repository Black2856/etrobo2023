import os
import cv2
import numpy as np
import socket
import struct

IP_ADDR = "0.0.0.0"
# 環境差調整用定数
SIZE_LEN = 4
FORMAT = "I"
class Signal:
    """
    Signalクラスは、ソケット通信を使用して画像、文字列、ファイルの送受信を行うためのクラスです。
    """
    def __init__(self, port:int):
        """
        Signalクラスのコンストラクタメソッド。
        ソケットを初期化し、タイムアウトとブロッキングを設定します。
        """
        self.__socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
        self.__conn = None
        self.__socket.setblocking(True)
        self.port = port

    def __del__(self):
        """
        Signalクラスのデストラクタメソッド。
        インスタンスが破棄される際にソケットをクローズします。
        """
        self.close()

        
    def open(self) -> bool:
        """
        サーバーとしてソケットをオープンし、クライアントからの接続を待ちます。

        Returns:
            bool: ソケットのオープンに成功した場合はTrue、それ以外はFalseを返します。
        """
        try:
            self.__socket.bind((IP_ADDR, self.port))
            self.__socket.listen(5)
            print("Server started : ", IP_ADDR, ":", self.port, sep='')
            self.__conn, addr = self.__socket.accept()
            print('Connected by', addr)
            return True
        except:
            return False

    def close(self) -> None:
        """
        ソケットをクローズし、リソースを解放します。
        """
        try:
            self.__conn.close()
            self.__socket.shutdown(socket.SHUT_RDWR)
            self.__socket.close()
        except:
            pass
        
    def __recvItem(self):
        """
        広範的なデータを受信する内部メソッド。

        Returns:
            bytes: 受信したバイナリデータを返します。
        """
        # データのサイズを受信
        buffer_size = self.__conn.recv(SIZE_LEN)
        print("  data size :", buffer_size)
        print(len(buffer_size))
        
        if(len(buffer_size) != SIZE_LEN):
            print("受信に失敗しました")
            return 0
        
        # バイナリデータを数値に変換
        buffer_size = struct.unpack(FORMAT, buffer_size)[0]
        print("  len       :", buffer_size)

        # データを受信
        data = b''
        while len(data) < buffer_size:
            packet = self.__conn.recv(buffer_size - len(data))
            if not packet:
                break
            data += packet
        print("  data top  :", data[:10])
        print("  data end  :", data[-10:])
        print("  Succeed")
        return data
    
    # 画像データを受信する関数
    def recvImage(self, path:str) -> None:
        """
        画像データを受信し、画像とファイル名を返します。

        Returns:
            tuple: 受信した画像データ（NumPy配列）とファイル名のタプルを返します。
        """
        print("Recv Image")
        # バイナリデータを受信
        binary_data = self.__recvItem()
        if binary_data == 0:
            return
        # 受信したデータをデコード
        frame_data = np.frombuffer(binary_data, dtype=np.uint8)

        # データを画像に変換
        frame = cv2.imdecode(frame_data, 1)
        # ファイル名受信
        text  = self.__recvString()
        if text == "":
            return
        # 画像を保存
        cv2.imwrite(f'{path}{text}', frame)
        
    
    # 文字列データを受信する関数
    def __recvString(self) -> str:
        """
        文字列データを受信し、デコードして文字列を返します。

        Returns:
            str: 受信した文字列データを返します。
        """
        print("Recv String")
        data = self.__recvItem()
        if data == 0:
            return ""
        # 受信したデータをデコード
        st = data.decode('utf-8')
        return st

    # 文字列を送信する関数
    def __sendString(self, text:str) -> None:
        """
        文字列データを送信します。

        Args:
            text (str): 送信する文字列データ。
        """
        print("Send String")
        data = text.encode('utf-8')
        size = struct.pack(FORMAT, len(data))
        print("  len       :", len(data))
        print("  data      :", data[:20])
        
        self.__conn.sendall(size)
        self.__conn.sendall(data)
        print("  Succeed")

    def sendFile(self, filePath:str) -> bool:
        """
        テキストファイルを送信します。
        ※テキストファイルはutf-8でエンコードしたものに限ります。

        Args:
            filePath (str): 送信するファイルのパス。

        Returns:
            bool: ファイルの送信に成功した場合はTrue、それ以外はFalseを返します。
        """
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
        self.__sendString(file_contents)
        self.__sendString(os.path.basename(filePath))
        return True


if __name__ == "__main__":
    signal = Signal(8080)
    signal.open()

    signal.recvImage()
    #string = signal.__recvString()
    signal.sendFile("requirements.txt")

    signal.close()