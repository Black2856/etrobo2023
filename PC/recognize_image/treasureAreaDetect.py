import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
base = os.path.dirname(os.path.abspath(__file__))

from webCamera import WebCamera

import numpy as np
import cv2
import time
import subprocess

from parallelProcessing import ParallelProcessing
from areaDetect import AreaDetect
from blockDetect import BlockDetect
from blockDetect import BlockType
from treasureArea import TreasureArea

class TreasureAreaDetect(ParallelProcessing):
    def __init__(self, cycle:float, cameraDevice):
        super().__init__()
        self.__webCamera = WebCamera(cameraDevice, (792, 432))
        self.__treasureArea = TreasureArea()
        self.__areaDetect = AreaDetect()
        self.__blockDetect = BlockDetect()

        # asterプログラムの初期化
        self.__treasureBlockDataPath = f"{base}/treasureBlockData.txt"
        outputPath = f"{base}/../manage_signal/send_folder/route.txt"
        self.__asterArgs = [os.path.abspath(self.__treasureBlockDataPath), os.path.abspath(outputPath)]
        self.__asterPath = [f"{base}/../search_route/aster.exe"]

        self.__areaPoints = [None]
        self.__decisionTime = 20
        self.__time = 0

        ### 画像取得方法(video か camera)
        self.__type = 'camera'
        
        if self.__type == 'video':
            self.__videoPath = f'{base}/1.mp4'
            self.__cap = cv2.VideoCapture(self.__videoPath)
        elif self.__type == 'camera':
            self.__webCamera.capture()

        self.cycle = cycle

    def __del__(self):
        del self.__webCamera
        del self.__treasureArea
        del self.__areaDetect 
        del self.__blockDetect

    def execute(self):
        if self.__type == 'camera':
            self.__camera()
        elif self.__type == 'video':
            self.__video()
        else:
            print("error:no type")

    def __video(self):
        ret, image = self.__cap.read()
        if not ret:
            self.stopThread()
            
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        image = self.__detect(image)
        

        # 表示
        frameRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        cv2.imshow('treasureArea : video', frameRGB)
        cv2.waitKey(1)

    def __camera(self):
        image = self.__webCamera.capture()
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        
        image = self.__detect(image)

        # 表示
        frameRGB = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        cv2.imshow('treasureArea : camera', frameRGB)
        cv2.waitKey(1)

    def __detect(self, image):
        ## エリア認識
        image, rawImage, areaPoints, areaLines = self.__areaDetect.detectArea(image)

        ## ブロックの認識
        taBlock = TreasureArea()
        if not(None in areaPoints):
            self.__areaPoints = areaPoints
            warpImage, taBlock = self.__blockDetect.findBlock(rawImage, areaPoints)
        elif not(None in self.__areaPoints):
            warpImage, taBlock = self.__blockDetect.findBlock(rawImage, self.__areaPoints)

        ## ブロック配置の決定
        #if taBlock.count(BlockType.none) != 16:
        #    taBlock.display()
        # 一定時間同じ配置を認識したら決定する
        if taBlock.count(BlockType.decoy) == 2 and taBlock.count(BlockType.treasure) == 1:
            self.__time += 1
            if self.__decisionTime <= self.__time:
                self.__decision(taBlock)
                # ルート計算プログラム呼び出し
                self.__searchRoute()
                self.stopThread()
        else:
            self.__time = 0

        return image
    
    def __decision(self, taBlock:TreasureArea):
        print("[ TreasureAreaDetect ]以下のブロック配置の決定がされました。")
        taBlock.display()
        taBlock.output(f'{base}/')

    def __searchRoute(self):
        asterEXE = subprocess.Popen(self.__asterPath + self.__asterArgs, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = asterEXE.communicate()
        if stderr == '':
            print("[ TreasureAreaDetect ]走行体のルート生成完了")
        else:
            print("[ TreasureAreaDetect ]走行体のルート生成失敗")
            print(stderr)

    def changeCamera(self, id):
        self.__webCamera = WebCamera(id, (792, 432))

if __name__ == "__main__":
    dta = TreasureAreaDetect(100)
    dta.startThread()
    time.sleep(10)
    dta.stopThread()
    del dta