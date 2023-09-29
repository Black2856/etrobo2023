import os, sys
os.chdir(os.path.dirname(os.path.abspath(__file__)))
base = os.path.dirname(os.path.abspath(__file__))
sys.path.append(f"{base}../manage_signal")


import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.preprocessing.image import ImageDataGenerator, load_img, img_to_array
import matplotlib.pyplot as plt
import random
from sklearn.metrics import confusion_matrix
import time
import cv2
from hashids import Hashids
import random

from parallelProcessing import ParallelProcessing
from competitionSystem import CompetitionSystem

class Minifig(ParallelProcessing):
    def __init__(self, cycle):
        super().__init__()
        self.__cycle = cycle
        self.__model = keras.models.load_model(f'{base}/best_model_50epoch.h5')
        self.__label_name = ['0d', '135d', '180d', '225d', '270d', '315d', '45d', '90d']
        self.__minifigDataPath = f'{base}/../manage_signal/recv_image/'
        self.__saveImagePath = f'{base}/minifig_processed_data/'
        self.__savelabelPath = f'{base}/../manage_signal/send_folder/'
        self.__processCount = 0
        
        self.__competitionSystem = CompetitionSystem()

    def execute(self):
        ret, image, name = self.__loadImage()
        if ret != False:
            self.__processCount += 1
            print(f'[ minifig ]find minifig image')
            # 受信枚数が奇数の場合は判別する。偶数の場合は競技システムに送信する。
            if (self.__processCount % 2) == 1:
                label = self.__predictImage(name)
                self.__saveLabel(label)
                self.__saveImage(image, name)
                print(end=f'[ minifig ]predictLabel = ')
                print(f'\'{label}\'')
            else: # (self.__processCount % 2) == 0
                print(end=f'[ minifig ]image send to competitionSystem :)')
                filename = self.__saveImage(image, name)
                self.__competitionSystem.snap(f'{self.__saveImagePath}{filename}')


    def __loadImage(self):
        contents = os.listdir(self.__minifigDataPath)
        if '.gitkeep' in contents:
            contents.remove('.gitkeep')

        if len(contents) == 0:
            return False, None, None
        loadFile = contents[0]
        image = cv2.imread(F'{self.__minifigDataPath}{loadFile}')
        return True, image, loadFile

    def __saveImage(self, image, name):
        rand = round(random.uniform(0, 2**31-1))
        # min_lengthに最小桁数を指定
        hashids = Hashids(salt='imageNameSeed', min_length=16)
        fileName = f'{hashids.encode(rand)}.png'

        cv2.imwrite(f'{self.__saveImagePath}{fileName}', image)
        # 処理したファイルの削除
        file_to_delete = f'{self.__minifigDataPath}{name}'
        os.remove(file_to_delete)
        return fileName

    def __saveLabel(self, label):
        name = 'minifigLabel.txt'
        with open(f'{self.__savelabelPath}{name}', 'w') as file:
            file.write(label)

    def __predictImage(self, name):
        image = tf.io.read_file(f'{self.__minifigDataPath}{name}')
        images = []

        # 画像の正規化
        image = tf.image.decode_jpeg(image, channels=3)
        image = tf.image.resize(image, [380, 380])
        image = tf.cast(image, tf.float32) / 255.0 # rescale to [0, 1]
        images.append(image)
        images = tf.stack(images)

        ## 推定
        predictions = self.__model.predict(images)
        predLabels = np.argmax(predictions, axis=1)
        label = self.__label_name[predLabels[0]]
        return label
    
if __name__ == '__main__':
    minifig = Minifig(100)
    minifig.startThread()
    time.sleep(20)
    minifig.stopThread()