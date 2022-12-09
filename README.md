# etrobo2023
etrobo2023_program

## 準備

### clone
任意のフォルダへ移動し、以下のコマンドを実行してください。
```bash
git clone https://github.com/Black2856/etrobo2023
```

### ユーザー設定
許可されたユーザーしかcommitできません。
commit権限が欲しい方は以下の手順を行ってください。

1. 申請  
Slack等の連絡ツールでcommit権限が欲しい旨をご連絡ください。  
権限が付与され次第招待メールが届きますので、承認を行ってください。

2. git設定  
以下のユーザー設定を行ってください。
なお、登録する情報はアクセスしているgithubアカウントの情報でなければなりません。
```bash
git config --global user.email "メールアドレス"
git config --global user.name "ユーザー名"
```

## 便利機能

### ファイル移動
ホームディレクトリから
```bash
et
```
を入力するとworkspaceに移動できます

### コミット
localで以下のコマンドを実行すると自動でmakefile.incを修正,add,commit,pushを実行する(commit msgは現在日時)
```bash
commit.bat
```
commit msgを手動で入力したい場合は以下のように入力してください
```bash
commit.bat "コメント"
```

※コミットは強制pushなのでローカルにも保存しておくこと  
※編集する前にpullを忘れずに

### 実行
raspberrypiで以下のコマンドを実行すると自動でpull,build,startを実行する
```bash
sh autostart.sh
```
raspberrypi側でも編集できますが、基本的にデバッグ用です