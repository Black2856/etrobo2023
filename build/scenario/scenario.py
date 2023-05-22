import xlwings as xw
import re

def aaa():
    xw.Range("A1").value = "title"
    for i in range(5):
        for j in range(5):
            xw.Range((i+1,j+1)).value = 2
            #source_range = xw.Range((i+1,j+1))
            #destination_range = xw.Range((i+10, j+10))
            #source_range.copy(destination_range)

def text_decode(string : str):
    lineString = ''.join(string.split())

    title = ""

    #titleの取得
    firstP = r'Scenario(.*?)={\"(.*?)\",{(.*?)}};'
    firstM = re.search(firstP, lineString)

    if firstM:
        title = firstM.group(1) 

    #rowの分割
    rowP = r'  (.*?)\n'
    rowM = re.findall(rowP, string)
    print(rowM)

    #columnの分割
    columnP = r'\{\{([^{}]+)\s*,\s{(.*?)}\s*\}\s*,*\s*(.*?);*}'
    columnM = re.findall(columnP, string)

    #columnの正規化
    data = []
    for column in columnM:
        contentsM = [column[0]]
        contentsM.append(re.split(r'\s*,\s*', column[1]))
        contentsM.append(re.findall(r'\[\]\(Judgement \*j\)\{return\s*(.*?.$)', column[2]))
        data.append(contentsM)
    return data, title

def decode():
    startCell = (2, 1)
    endCell = (10, 7)
    titleCell =  (2, 9)
    getString = (2, 11)

    #セルの削除
    #rangeToDelete = xw.Range(startCell, endCell) 
    #rangeToDelete.value = ''

    data, title = text_decode(xw.Range(getString).value)
    xw.Range(titleCell).value = title
    #セルのコピー処理
    for i, record in enumerate(data):
        xw.Range((startCell[0]+i, startCell[1]+0)).value = record[0]
        for j, arg in enumerate(record[1]):
            xw.Range((startCell[0]+i, startCell[1]+1+j)).value = arg
        xw.Range((startCell[0]+i, startCell[1]+6)).value = record[2]

    #セルの削除
    lastIdx = len(data)
    rangeToDelete = xw.Range((startCell[0]+lastIdx, startCell[1]), (startCell[0]+lastIdx, startCell[1]+6)) 
    rangeToDelete.value = ''


@xw.func
def test(x, y):
    """hello"""
    return 2 * (x + y)