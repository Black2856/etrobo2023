#!/bin/bash
# このshファイルが存在するディレクトリの絶対パスを取得
cd $(dirname "$0")
compile_dir=$(pwd)

# etrobo2023のpath
root_dir="../.."

cd $root_dir

chmod 755 "$compile_dir/RearCamera.sh"
$compile_dir/RearCamera.sh

exit 0