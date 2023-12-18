#############################
### scenario.xlsmからの実行ファイル
### 作成者 : 船田 直輝
#############################

import sys
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))
sys.path.append("../python")
from update import process

def convert():
    process('./spike/scenario/state_transition.cpp')
    process('./app.cpp')

if __name__ == "__main__":
    process('./spike/scenario/state_transition.cpp')
    process('./app.cpp')