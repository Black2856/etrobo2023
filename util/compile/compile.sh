#!/bin/bash

# 現在のディレクトリを保存
current_dir=$(pwd)

cd $(dirname "$0")
# このshファイルが存在するディレクトリの絶対パスを取得
compile_dir=$(pwd)

# etrobo2023のpath
root_dir="../.."

cd $root_dir

chmod 755 "$compile_dir/RearCamera.sh"
$compile_dir/RearCamera.sh

# 元のディレクトリに戻る
cd "$current_dir"

exit 0