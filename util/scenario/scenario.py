import sys
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
sys.path.append('../python')
from update import process

def convert():
    process('./spike/scenario/func_list.h')
    process('./app.cpp')
    pass

if __name__ == "__main__":
    process('./spike/scenario/func_list.h')
    process('./app.cpp')