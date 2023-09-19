import cv2
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

from treasureArea import TreasureArea
from treasureArea import BlockType

class BlockDetect:
    def __init__(self):
        #閾値 (360°100°100°)
        self.__decoyRange = [((187, 50, 25), (227, 100, 100))]
        self.__treasureRange = [
            ((330, 50, 25), (360, 100, 100)),
            ((0, 50, 25), (30, 100, 100))
        ]
        self.__imageSize = 300
        pass

    def findBlock(self, image, areaPoints):
        retTreasureArea = TreasureArea()
        if (None in areaPoints) or (len(areaPoints) != 4):
            return image, retTreasureArea
        
        warpedImg = self.__projectiveImage(image, areaPoints)
        blockColor = self.__getPointColor(warpedImg)

        retTreasureArea = self.__list2treasureArea(blockColor)
        return warpedImg, retTreasureArea
        #plt.imshow(warpedImg)

    def __projectiveImage(self, image, areaPoints):
        # Define the source and destination points
        size = self.__imageSize
        srcPts = np.array([areaPoints[0], areaPoints[1], areaPoints[2], areaPoints[3]], dtype=np.float32)
        dstPts = np.array([(0, size), (size, size), (size, 0), (0, 0)], dtype=np.float32)

        # Calculate the homography matrix
        H, _ = cv2.findHomography(srcPts, dstPts)

        # Apply the perspective transform
        warpedImg = cv2.warpPerspective(image, H, (self.__imageSize, self.__imageSize))

        return warpedImg

    def __getPointColor(self, warpedImg):
        #取得ポイントを計算
        getPoints = []
        countPoints = 4
        size = self.__imageSize - 1
        for i in range(countPoints):
            y = round(size / (countPoints - 1) * i)
            for j in range(countPoints):
                x = round(size / (countPoints - 1) * j)
                getPoints.append((x, y))

        # HSV値の正規化
        decoyRange = self.__normalizeHSV(self.__decoyRange)
        treasureRange = self.__normalizeHSV(self.__treasureRange)
        # ブロック判別
        image = cv2.cvtColor(warpedImg, cv2.COLOR_RGB2HSV)
        areaBlock = []
        for pos in getPoints:
            pixel = image[pos[0], pos[1]]
            if self.__checkPixel(pixel, treasureRange) == True:
                areaBlock.append('treasure')
            elif self.__checkPixel(pixel, decoyRange) == True:
                areaBlock.append('decoy')
            else:
                areaBlock.append('none')

        return areaBlock

    def __normalizeHSV(self, HSVranges):
        converted_ranges = [
            (
                tuple(map(int, np.round(np.multiply(min_HSV, np.array([180/360, 255/100, 255/100]))))),
                tuple(map(int, np.round(np.multiply(max_HSV, np.array([180/360, 255/100, 255/100])))))
            ) for min_HSV, max_HSV in HSVranges
        ]
        return converted_ranges
    
    def __checkPixel(self, pixelHSV, HSVranges):
        for HSVrange in HSVranges:
            HSVmin = HSVrange[0]
            HSVmax = HSVrange[1]
            if HSVmin[0] <= pixelHSV[0] <= HSVmax[0] and HSVmin[1] <= pixelHSV[1] <= HSVmax[1] and HSVmin[2] <= pixelHSV[2] <= HSVmax[2]:
                return True
        return False
    
    def __list2treasureArea(self, block):
        taBlock = TreasureArea()

        for i, o in enumerate(block):
            x = i % 4
            y = i // 4

            blockType = BlockType.none
            if o == 'decoy':
                blockType = BlockType.decoy
            elif o == 'treasure':
                blockType = BlockType.treasure

            taBlock.setBlockType((x, y), blockType)

        return taBlock
        
if __name__ == "__main__":
    blockDetect = BlockDetect()
    img = cv2.imread("./test.png")
    p = [(130, 388), (665, 162), (382, 41), (31, 112)]
    blockDetect.findBlock(img, p)