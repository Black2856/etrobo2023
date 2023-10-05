#!/bin/sh
set -e  # エラーチェックを有効化

# バックグラウンドで実行しているプロセスをプロセスグループとして指定
pgid=$(ps -o pgid= $$ | awk '{print $1}')

# プログラム終了時にバックグラウンドプロセスを強制終了
trap 'kill -- -$pgid' EXIT INT SEGV ABRT KILL

# shファイルの存在するディレクトリにcd
cd $(dirname "$0")

cd ../

CFILE=$(basename $(pwd))

# 初期値設定
# 0 == false
# 1 == true
fetchFLG=1 # fetchを行うか 
simFLG=0   # simulator環境か
makeFLG=1  # makeを行うか

# コマンドライン引数の処理
if [ "${1#-}" != "$1" ]; then
    # 文字列の長さを取得
    length=$(expr length "$1")
    # 文字列の一文字ずつ処理
    for i in $(seq 1 $length); do
        # i番目の文字を取得
        char=$(expr substr "$1" $i 1)
        
        if [ "$char" = "r" ]; then
            fetchFLG=0
        fi

        if [ "$char" = "s" ]; then
            simFLG=1
        fi

        if [ "$char" = "m" ]; then
            makeFLG=0
        fi
    done
fi
# makeする場合
if [ $makeFLG = 1 ]; then
    # fetchする場合
    if [ $fetchFLG = 1 ]; then
        git fetch origin main
        git reset --hard origin/main
    fi

    make -C background_tasks
fi

cd ../ 
# img保存用ディレクトリの作成
mkdir -m 755 img || true
# 撮影待機リストの初期化
echo 'iwasaki' | sudo -S rm "Queue.txt" || true
# background_tasksをバックグラウンドで実行
./$CFILE/background_tasks/background_tasks & 

chmod -R 755 ./$CFILE

# simulator環境の場合
if [ $simFLG = 1 ]; then
    cd ../
    make app=$CFILE sim up

else
    # makeする場合
    if [ $makeFLG = 1 ]; then
        rm asp || true
        make img=$CFILE
    fi
    # メインタスクを実行
    make start
fi

kill -- -$pgid

wait