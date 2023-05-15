import xlwings as xw

def decode():
    xw.Range('A1').value = 'test'

@xw.func
def kakezan(x, y):
    """x * yの値を返す"""
    return (x * y)