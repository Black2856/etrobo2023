CFILE=$(basename pwd)

git pull
cd ../
make img=$CFILE
make start