# etrobo2023
etrobo2023_program

## ファイル移動
ホームディレクトリから
```bash
source et.sh
```
を入力するとworkspaceに移動できます


## コミット
localで以下のコマンドを実行すると自動でadd,commit,pushを実行する(commit msgは現在日時)
```bash
commit.bat
```

## 実行
raspberrypiで以下のコマンドを実行すると自動でpull,build,startを実行する
```bash
sh autostart.sh
```

※コミットは強制pushなのでローカルにも保存しておくこと  
※編集する前にpullを忘れずに  
※ラズパイ側で編集するとsh autostart,shのpullに失敗するかも  
