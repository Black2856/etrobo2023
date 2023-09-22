set -e  # エラーチェックを有効化

cd $(dirname "$0")

cd ../

CFILE=$(basename $(pwd))
# コマンドライン引数の処理
fetchFLG=1
simFLG=0
#if [ "${1:0:1}" == "-" ]; then
#    # 文字列の長さを取得
#    length=${#1}
#    # 文字列の一文字ずつ処理
#    for ((i = 1; i < length; i++)); do
#        # i番目の文字を取得
#        char="${1:i:1}"
#        
#        if [ "$char" == "r" ]; then
#            fetchFLG=0
#        fi
#
#        if [ "$char" == "s" ]; then
#            simFLG=1
#        fi
#    done
#fi

if [ $fetchFLG == 1 ]; then
    git fetch origin main
    git reset --hard origin/main
fi

make -C background_tasks

cd ../ 

mkdir -m 755 img || true
# background_tasksをバックグラウンドで実行
./$CFILE/background_tasks/background_tasks &

chmod -R 755 ./$CFILE

if [ $simFLG == 1 ]; then
    cd ../
    make app=$CFILE sim up
else
    rm asp || true
    make img=$CFILE
    # etrobo2023をバックグラウンドで実行
    make start
fi

kill %1