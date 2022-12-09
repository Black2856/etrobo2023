CFILE=$(basename $(pwd))

if [ "$1" != "-r" ]; then
    git fetch origin main
    git reset --hard origin/main
fi

cd ../

rm asp
make img=$CFILE
make start