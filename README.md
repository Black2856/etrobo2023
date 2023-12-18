# etrobo2023
etrobo2023_program

## 準備

### clone
任意のフォルダへ移動し、以下のコマンドを実行してください。
```bash
git clone https://github.com/Black2856/etrobo2023
```

### ユーザー設定
許可されたユーザーしかcommitできません。<br>
commit権限が欲しい方は以下の手順を行ってください。<br>

1. 申請  
Slack等の連絡ツールでcommit権限が欲しい旨をご連絡ください。<br>
権限が付与され次第招待メールが届きますので、承認を行ってください。<br>

2. git設定  
以下のユーザー設定を行ってください。<br>
なお、登録する情報はアクセスしているgithubアカウントの情報でなければなりません。<br>
```bash
git config --global user.email "メールアドレス"
git config --global user.name "ユーザー名"
```
もしくはforkして自身のリポジトリを作成してください。

## 環境構築
spike側とPC側で両方必要になります。
- spike側<br>

    etrobo環境の構築<br>
    ./background_tasks/requirements.txtの実行<br>

- PC側<br>

    python環境の構築 (PC/install/のrequirements.txtまたはetrobo.ymlのインポート)<br>
    c++環境の構築 (PC/serch_route/c++環境構築.txt)<br>
    xlwingsのインストール (必須ではない util/scenario/scenario.xlsmのシート内)<br>


## 便利機能

### ファイル移動 (spike側のos)
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

makefileとapp.cfgの修正には
```bash
#<タグ名>
#</タグ名>
```
を用いることでタグ内のテキストをディレクトリ構成に合わせて修正します
※編集する前にpullを忘れずに

### 実行
raspberrypiで以下のコマンドを実行すると自動でmakefileとcfgの修正,pull,build,startを実行する
```bash
sh autostart.sh

```
raspberrypi側でも編集できますが、基本的にデバッグ用です

PC側の実行には./PC/main.ipynb　から実行できます。

## 各ファイルの簡易説明

etrobo2023<br>
├── app.cfg<br>
├── app.cpp<br>
├── app.h<br>
├── background_tasks<br>
├── PC<br>
├── setting.h<br>
├── spike<br>
├── util<br>
│      └── scenario<br>
│               └── scenario.xlsm<br>
└── 設計<br>
        └── ADV_004_ろぼ魂.pdf<br>
※説明するファイルのみ記述  

- `app.cfg`, `app.cpp`, `app.h`: spikeを動かす主要のソースコード。
- `spike/`: spikeを高度な制御を行うための各種ソースコードがある。
- `background_tasks/`: spike側のTOPPERSプラットフォーム下で制御を行わないソースコード類、撮影や送受信等。
- `PC/`: PCで動作させるソースコード類、主な機能は送受信、画像処理や経路探索。
- `setting.h`: spike制御用の設定ファイル。
- `util/`: 汎用スクリプトをまとめた便利機能。
- `util/scenario/scenario.xlsm`: spike動作定義をexcel上で記述できるツール。デプロイすることでコードを自動で改変する。
- `設計/`: プロジェクトの設計関連ドキュメント。
- `設計/ADV_004_ろぼ魂.pdf`: 設計の清書

各ディレクトリとファイルについての詳細な説明は、プロジェクトのドキュメンテーション、設計ディレクトリを参照してください。
