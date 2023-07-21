#############################
### scenario変換
### 作成者 : 船田 直輝
#############################

import os
import pandas as pd
import numpy as np

expath = os.path.dirname(os.path.abspath(__file__))#scenario_convert.pyの場所

def loadSheet(filePath, manageSheetName):
    #etroboのディレクトリに移動する
    stackDir = os.getcwd()
    os.chdir(expath)
    os.chdir("../../")
    xls = pd.ExcelFile(filePath)
    os.chdir(stackDir)

    manageDF = pd.read_excel(xls, manageSheetName)
    scenarioDFs = [pd.read_excel(xls, i) for i in manageDF['シナリオ名']]
    return scenarioDFs

def showFunc(codeB):
    'カンマ追加'
    for i, itemi in enumerate(codeB):
        codeB[i] = f'        case {i}: {codeB[i]} break;'
    #    if i == len(codeB) - 1:
    #        codeB[i] = f'{codeB[i]}'
    #    else:
    #        codeB[i] = f'{codeB[i]}'

    #codeB.insert(0, f'std::function<bool(Judge& j)> list[{len(codeB)}] = {{')
    #codeB.append(f'}};')
    return codeB

def showMakeCode(scenarioDF, codeB):
    sc = convertSC(scenarioDF, '遷移条件', codeB)
    title = scenarioDF['タイトル'][0]
    className = 'Manage_scene'
    manageScenario = 'manage_scenario'

    codeA = []
    codeA.append(f'{className} {title}("{title}");')

    #遷移条件の生成
    scList = scenarioDF['遷移条件'].dropna()
    for i, itemi in enumerate(scList):
        string = f'func = [](Judge& j) {{return {itemi};}};'
        codeB.append(string)

    #引数に遷移条件を付与
    args = scenarioDF.loc[:, "引数1":"引数5"].apply(lambda x: [v for v in x if pd.notna(v)], axis=1)
    for i, itemi in enumerate(sc):
        if(itemi != -1):
            args[i].insert(0, itemi)

    #引数を文字列化
    stringArgs = []
    for i, itemi in enumerate(args):
        string = ""
        for j, itemj in enumerate(itemi):
            if j == len(itemi) - 1:
                string = f'{string}{itemj}'
            else:
                string = f'{string}{itemj}, '
        stringArgs.append(string)

    #構文の生成
    for i, row in scenarioDF.iterrows():
        string = f'{title}.make{row["動作"]}({stringArgs[i]});'
        codeA.append(string)

    codeA.append(f'{manageScenario}.add({title});')

    return codeA, codeB

def convertSC(scenarioDF, columnName, codeB):
    idx = len(codeB)

    # Create an array where each element is a number if the corresponding column is not NaN, otherwise NaN
    column_array = scenarioDF[columnName].notna().cumsum() - 1 + idx
    column_array[~scenarioDF[columnName].notna()] = -1
    # Convert the pandas Series to a NumPy array
    numpy_array = column_array.to_numpy()

    return numpy_array

def deploy(filePath):
    manageSheetName = '|シナリオ管理|'
    codeA = []
    codeB = []

    scenarioDFs = loadSheet(filePath, manageSheetName)
    
    for itemi in scenarioDFs:
        subCodeA, codeB = showMakeCode(itemi, codeB)
        codeA = codeA + subCodeA + [""]
    codeB = showFunc(codeB)

    return codeA, codeB

if __name__ == "__main__":
    codeA, codeB = deploy()
    print(codeA)
    print(codeB)