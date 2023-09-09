#############################
### 並行処理クラス
### 作成者 : 船田 直輝
#############################

import threading
import time

class ParallelProcessing:
    def __init__(self):
        """
        継承した場合はsuper().__init__()を必要とする
        """
        self.__cycle = 1
        self.__threadState = False
        self.t = threading.Thread(target=self.__ThreadProcess)

    def startThread(self):
        """
        並行処理プログラムの開始 \n
        実行関数はexecute()
        """
        self.__threadState = True
        self.t.start()

    def stopThread(self):
        """
        並行処理プログラムの停止
        """
        self.__threadState = False
        self.t.join()

    def __ThreadProcess(self):
        """
        並行処理時の基本処理
        """
        while self.__threadState == True:
            self.execute()
            time.sleep(self.__cycle)

    def execute(self):
        """
        並行処理時の動作
        """
        print("test")

    @property
    def cycle(self) -> int:
        """
        実行間隔時間[ms](int)
        """
        return self.__cycle
    @cycle.setter
    def cycle(self, cycle:float):
        self.__cycle = cycle / 1000



### 並行処理クラスの使用例
if __name__ == "__main__":
    
    class Example(ParallelProcessing):
        def __init__(self):
            super().__init__()
            self.cycle = 500 #500msの周期で動作
            self.a = 0
        
        def manage(self):
            self.startThread()
            while True:
                if self.a >= 10:
                    self.stopThread()
                    return

        def execute(self):
            self.a += 1
            print(f'test : {self.a}')
    
    example = Example()
    example.manage()
