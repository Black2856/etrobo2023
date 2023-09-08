from enum import Enum
import os
import re

class BlockType(Enum):
    none = 0
    decoy = 1
    treasure = 2

class SquareInfo:
    def __init__(self):
        self.__blockType = BlockType.none

    @property
    def blockType(self):
        return self.__blockType
    
    @blockType.setter
    def blockType(self, value:BlockType):
        self.__blockType = value

class TreasureArea:
    def __init__(self):
        #保存するファイル名
        self.__fileName = f'treasureBlockData.txt'
        self.__size = 4
        self.__square = [[SquareInfo() for i in range(self.__size)] for j in range(self.__size)]

    def display(self):
        for i, x in enumerate(self.__square):
            for j, y in enumerate(x):
                print(f'[{i}, {j}] {y.blockType}')

    #引数:pos -> 座標([int, int]), block -> 配置ブロック(BlockType)
    def setBlockType(self, pos:[int, int], block:BlockType):
        """ 
        引数:pos -> 座標([int, int]), block -> 配置ブロック(BlockType) \n
        指定座標に指定したタイプのブロックを配置する
        """
        self.__square[pos[0]][pos[1]].blockType = block

    def count(self, block:BlockType):
        """
        引数:block -> 数えるブロックの種類(BlockType) \n
        返り値:合計(int) \n
        指定したブロックの種類の合計値を返す
        """
        count = 0
        for x in self.__square:
            for y in x:
                if y.blockType == block:
                    count += 1
        return count
    
    def output(self, filePath:str):
        """
        引数:filePath -> 出力する指定ファイルパス \n
        トレジャーエリアのマス情報をファイルに出力する
        """
        
        #テキスト変換
        outputText = []
        for x in self.__square:
            for y in x:
                text = str(y.blockType)
                text = re.search(r'\.(\w+)$', text)
                outputText.append(text.group(1))

        #ファイル出力
        fullPath = os.path.join(filePath, self.__fileName)
        with open(fullPath, 'w') as f:
            for t in outputText:
                f.write(f'{t}\n')



if __name__ == "__main__":
    treasureArea = TreasureArea()
    treasureArea.setBlockType([1, 0], BlockType.decoy)
    treasureArea.display()
    print(treasureArea.count(BlockType.none))

    treasureArea.output("./")