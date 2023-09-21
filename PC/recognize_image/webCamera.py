import os
os.chdir(os.path.dirname(os.path.abspath(__file__)))
# カメラの読み込み高速化
os.environ["OPENCV_VIDEOIO_MSMF_ENABLE_HW_TRANSFORMS"] = "0"

import cv2

class WebCamera:
    def __init__(self, deviceID:int, size):
        """
        引数:deviceID(int) -> カメラのID指定
             siez(int, int) -> 取得する解像度
        """
        width, height = size
        self.__deviceID = deviceID
        self.__cap = cv2.VideoCapture(self.__deviceID)
        self.__cap.set(cv2.CAP_PROP_FRAME_WIDTH, width)
        self.__cap.set(cv2.CAP_PROP_FRAME_HEIGHT, height)

    def __del__(self):
        self.__cap.release()

    def capture(self):
        """
        返り値:画像データ
        """
        #cap = cv2.VideoCapture(self.__deviceID)
        ret, frame = self.__cap.read()
        #cap.release()

        if ret:
           return frame
           #cv2.imwrite("webcam_image.jpg", frame)
