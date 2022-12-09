### makefileのinclude自動生成
import os
import glob
import re

# 抽出する拡張子
pattern = re.compile(r'\.cpp|\.h')

# ディレクトリ抽出
dirs = [os.path.dirname(x.replace('\\', '/')) for x in glob.glob('**/*/', recursive=True)]
print(dirs)

# ファイル抽出
files = [os.path.basename(x.replace('\\', '/')) for x in glob.glob('**/*', recursive=True) if pattern.search(x)]
print(files)

mk_files = set(["   " + x.split(".")[0] + ".o \\" for x in files])
mk_dirs1 = set(["   $(mkfile_path)" + x.split(".")[0] + " \\" for x in dirs])
mk_dirs2 = set(["   -I$(mkfile_path)" + x.split(".")[0] + " \\" for x in dirs])
dic = {
    'mk_files' : mk_files,
    'mk_dirs1' : mk_dirs1,
    'mk_dirs2' : mk_dirs2
    }

# makefileの中身取得 %変数%で置き換えする
f = open('makefile.txt', 'r')
data = f.readlines()
f.close()

pattern = "%(\w)+%"
text = []

for x in data:
    p = re.search(pattern, x)
    if p:
        insert_text = dic[p.group()[1:-1]]
        for y in insert_text:
            text.append(y + "\n")
    else:
        text.append(x)

f = open('makefile.inc', 'w')
for x in text:
    f.write(x)
f.close()
