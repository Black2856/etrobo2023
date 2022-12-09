CFILE=$(basename $(pwd))

git fetch origin main
git reset --hard origin/main

cd ../
make img=$CFILE
make start