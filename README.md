# etrobo2023
etrobo2023_program

##ファイル移動
source et.sh を入力すると移動できます


## commit
localで以下のコマンドを実行すると自動でadd,commit,pushを実行する(msgは現在日時)
```bash
commit.bat
```

raspberrypiで以下のコマンドを実行するとpullからstartまで自動で行う
```bash
sh autostart.sh
```

編集する前にpullを忘れずに(ラズパイ側で編集するとsh autostart,shのpullに失敗するかも) 
