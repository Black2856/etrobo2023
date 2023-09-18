import cv2

class WebCamera:
    def __init__(self, deviceID:int):
        """
        引数:deviceID -> カメラのID指定
        """
        self.__deviceID = deviceID
        self.__cap = cv2.VideoCapture(self.__deviceID)

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
