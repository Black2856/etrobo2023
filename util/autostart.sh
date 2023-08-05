set -e  # エラーチェックを有効化

cd $(dirname "$0")

cd ../

CFILE=$(basename $(pwd))

if [ "$1" != "-r" ]; then
    git fetch origin main
    git reset --hard origin/main
fi

make -C background_tasks

cd ../

mkdir -m 755 img || true
# background_tasksをバックグラウンドで実行
./$CFILE/background_tasks/background_tasks &

chmod -R 755 ./etrobo2023

rm asp || true
make img=$CFILE
# etrobo2023をバックグラウンドで実行
make start &

# etrobo2023の終了を待つ
wait $!

# etrobo2023が終了した時点で、background_tasksも終了させる
kill %1