#############################
### 並行処理クラス
### 作成者 : 船田 直輝
#############################
import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))

import threading
import time

class ParallelProcessing:
    """
    平行処理を管理するクラス \n
    実行間隔のcycleはexecute()関数の実行時間に応じて調整される。 \n
    ただし実行時間 > cycleの場合は処理落ちとして扱われる。
    """
    def __init__(self):
        """
        継承した場合はsuper().__init__()を必要とする
        """
        self.__cycle = 1
        self.__threadState = False
        self.__isThreading = False
        self.t = threading.Thread(target=self.__ThreadProcess)

    def startThread(self):
        """
        並行処理プログラムの開始 \n
        実行関数はexecute()
        """
        if self.__threadState == False:
            self.__threadState = True
            self.t.start()
        elif self.__threadState == True:
            print("warning:startThread() is already start in ParallelProcessing")

    def stopThread(self):
        """
        並行処理プログラムの停止
        """
        if self.__threadState == True:
            self.__threadState = False
            #self.t.join()
        elif self.__threadState == False:
            print("warning:stopThread() is already stop in ParallelProcessing")

    def __ThreadProcess(self):
        """
        並行処理時の基本処理
        """
        while self.__threadState == True:
            self.__startTime = time.time()
            self.__isThreading = True
            self.execute()
            self.__endTime = time.time()
            if self.__threadState == True:
                waitTime = self.cycle - (self.__endTime - self.__startTime)
                if waitTime < 0:
                    waitTime = 0
                time.sleep(waitTime)
        self.__isThreading = False

    def execute(self):
        """
        並行処理時の動作
        """
        print("test")
    @property
    def threadState(self) -> bool:
        """
        平行処理を実行するかどうか
        """
        return self.__threadState

    @property
    def threading(self) -> bool:
        """
        平行処理の実行中かどうか
        """
        return self.__isThreading
    @property
    def cycle(self) -> int:
        """
        実行間隔時間[ms](int)
        """
        return self.__cycle
    @cycle.setter
    def cycle(self, cycle:float):
        self.__cycle = cycle / 1000



if __name__ == "__main__":
    
    class Example1(ParallelProcessing):
        def __init__(self):
            super().__init__()
            self.cycle = 500 #500msの周期で動作
            self.a = 0

        def execute(self):
            self.a += 1
            print(f'test1 : {self.a}')
            if self.a >= 10:
                self.stopThread()

    class Example2(ParallelProcessing):
        def __init__(self):
            super().__init__()
            self.cycle = 250 #250msの周期で動作
            self.a = 0

        def execute(self):
            self.a += 1
            print(f'test2 : {self.a}')
            if self.a >= 15:
                self.stopThread()
    
    example1 = Example1()
    example2 = Example2()
    example1.startThread()
    example2.startThread()