cd $(dirname "$0")

cd ../

CFILE=$(basename $(pwd))

if [ "$1" != "-r" ]; then
    git fetch origin main
    git reset --hard origin/main
fi

make -C background_tasks

cd ../
chmod -R 755 ./etrobo2023

rm asp
make img=$CFILE
make start