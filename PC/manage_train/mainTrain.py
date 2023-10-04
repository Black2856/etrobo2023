import requests
import time
from competitionSystem import CompetitionSystem
from parallelProcessing import ParallelProcessing

class Train(ParallelProcessing):
    def __init__(self):
        super().__init__()
        self.cs = CompetitionSystem()
        self.pwm = 30               # 規定速度
        self.accel_threshold = 5    # 加速度誤差範囲
        self.gyro_threshold = 30    # ジャイロ誤差範囲
        self.stop_time = 1.9        # 直線侵入後停止するまでの時間
        self.cycle = 1000 * 0.1     # 動作周期
        self.a = -1                 # 初回受信成功時に点数レーンにいた場合もう一周する

    def execute(self):
        self.cs.IoT_SET(self.pwm)
        data = self.cs.IoT_GET()
        # データの受信に失敗した場合
        if data == False:
            return
        
        # 加速度が一定値以上であった場合
        if data["accel"]["z"] > self.accel_threshold:
            if self.a < 0:
                self.a += 1
            return
        # ジャイロ値を360で割った余りが誤差範囲外であった場合
        if (data["gyro"]["z"] % 360) > self.gyro_threshold:
            return
        # 初回受信成功時に点数レーンだった場合もう一周する
        if self.a < 0:
            return
        # すべてのifを抜けた場合処理を終了
        self.stopThread()
        
    def stopThread(self):
        super().stopThread()
        # 一定時間経過後に停止処理を行う
        time.sleep(self.stop_time)
        # 停止に失敗した場合
        while not self.cs.IoT_SET(0):
            pass
        print("IoT列車を停止させました。")

class MainTrain(ParallelProcessing):
    """
    IoT列車管理
    """
    def __init__(self):
        super().__init__()
        self.__cycle = 500
        # IoT列車
        self.__train = Train()

    def __del__(self):
        self.__train.stopThread()

    def execute(self):
        # 生存確認 
        if self.__train.threadState == False:
            self.__train.stopThread()
            print("[ IoT列車管理 ]停止")
            self.stopThread()