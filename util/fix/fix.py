#############################
### include自動生成
### 作成者 : 船田 直輝
#############################

###指定したファイルのタグ要素内をリポジトリ内のincludeファイル要素を更新する

import os
import glob
import re
import sys

# コマンドライン引数の受け取り [1]:ファイルパス
args = sys.argv
file_path = args[1]
print(file_path + " を更新中...")

# 抽出する拡張子
pattern_ext = re.compile(r'\.c$|\.cpp$|\.h$')

# ディレクトリ抽出
dirs = [os.path.dirname(x.replace('\\', '/')) for x in glob.glob('**/*/', recursive=True)]

# ファイル抽出
files = set([os.path.basename(x.replace('\\', '/')) for x in glob.glob('**/*', recursive=True) if pattern_ext.search(x)])

# 除外するファイル名
pattern_file = re.compile(r'app|RearCamera|Net')
# 除外するフォルダ名
pattern_folder = re.compile(r'util|設計')

##### タグ置換要素の作成
# 拡張子前の名前が同じであるファイルをカウント
file_count = {}
for file in files:
    file_name = file.split(".")[0]
    if (file_name in file_count):
        file_count[file_name] += 1
    else:
        file_count[file_name] = 1

# ファイル数が2以上であり除外ファイルでないファイル名
mk_files0 = [key for key, value in file_count.items() if value >= 2 and not(pattern_file.search(key))]

mk_files = [f"    {x}.o \\" for x in mk_files0]

att_mod = [f"ATT_MOD(\"{x}.o\");" for x in mk_files0]

# 除外フォルダでないフォルダ名
mk_dirs0 = [x.split('.')[0] for x in dirs if not(pattern_folder.search(x))]

mk_dirs1 = [f"    $(mkfile_path){x} \\" for x in mk_dirs0]

mk_dirs2 = [f"    -I$(mkfile_path){x} \\" for x in mk_dirs0]

# 昇順に並び替え
mk_files = sorted(list(mk_files))
mk_dirs1 = sorted(list(mk_dirs1))
mk_dirs2 = sorted(list(mk_dirs2))
att_mod  = sorted(list(att_mod))

# 先頭行を追加
mk_files.insert(0, 'APPL_CXXOBJS += \\')
mk_dirs1.insert(0, 'APPL_DIRS += \\')
mk_dirs2.insert(0, 'INCLUDES += \\')
att_mod.insert( 0, 'ATT_MOD("app.o");')

dic = {
    'mk_files' : mk_files,
    'mk_dirs1' : mk_dirs1,
    'mk_dirs2' : mk_dirs2,
    'att_mod' : att_mod
    }
#####

# "#<タグ名>　～　#</タグ名>" の間を更新する
f = open(file_path, 'r')
data = f.readlines()
f.close()

pattern_tag_start = "<(\w)+>"
text = []
tag_in = False

# タグ内の初期化
for x in data:
    if tag_in == False:
        p = re.search(pattern_tag_start, x)
        if p:
            tag_in = True
            pattern_tag_end = "</" + p.group()[1:-1] + ">"
            text.append(x)
            text.append("%" + p.group()[1:-1] + "%")
        else:
            text.append(x)
    else:
        p = re.search(pattern_tag_end, x)
        if p:
            tag_in = False
            text.append(x)
data = text

# 置換要素の更新
pattern_var = "%(\w)+%"
text = []

for x in data:
    p = re.search(pattern_var, x)
    if p:
        insert_text = dic[p.group()[1:-1]]
        for y in insert_text:
            text.append(y + "\n")
    else:
        text.append(x)

# 書き込み
f = open(file_path, 'w')
for x in text:
    f.write(x)
f.close()
