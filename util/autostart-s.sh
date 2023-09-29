set -e  # エラーチェックを有効化

cd $(dirname "$0")

cd ../

CFILE=$(basename $(pwd))
# コマンドライン引数の処理
fetchFLG=0
simFLG=0



cd ../ 

mkdir -m 755 img || true
# background_tasksをバックグラウンドで実行
./$CFILE/background_tasks/background_tasks &

chmod -R 755 ./$CFILE


make start


kill %1