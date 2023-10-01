/*
 * クラス名:ReadSig
 * 作成日:2023/09/28
 * 作成者:船田
 */

#include "ReadSig.h"

void ReadSig::storeRoute(const char* filename) {
    // ファイルが存在するかどうかを確認
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);

        // ファイルオープン
        FILE* fileToProcess = fopen(filename, "r");
        if (fileToProcess == NULL) {
            printf("Failed to open the file %s\n", filename);
            return;
        }

        // ファイルメイン処理
        std::list<int> runRoute;
        char line[256];
        while (!feof(fileToProcess)) {
            int ch, i = 0;

            // 1行分のデータを読み取り
            while ((ch = fgetc(fileToProcess)) != EOF && ch != '\n') {
                line[i++] = ch;
            }
            line[i] = '\0';  // 終端文字を追加

            // ここで line に格納されたデータを処理します
            if (strcmp(line, "0\n") == 0) {
                runRoute.push_back(0);
            } else if (strcmp(line, "1\n") == 0) {
                runRoute.push_back(1);
            } else if (strcmp(line, "2\n") == 0) {
                runRoute.push_back(2);
            }

            // 最後の読み取りが EOF だった場合、ループを終了
            if (ch == EOF) {
                break;
            }
        }

        //　ファイル後処理(削除)
        fclose(fileToProcess);

        #ifdef MAKE_SIM //シミュレータ環境では動作しない
            remove(filename);
        #endif

        // 格納
        this->generalData.setRunRoute(runRoute);
        printf("[ ファイル読み込み ]走行ルートの取得に成功\n");

    } else {
        //printf("%s does not exist.\n", filename);
    }
}

void ReadSig::storeMinifigLabel(const char* filename) {
    // ファイルが存在するかどうかを確認
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);

        // ファイルオープン
        FILE* fileToProcess = fopen(filename, "r");
        if (fileToProcess == NULL) {
            printf("Failed to open the file %s\n", filename);
            return;
        }

        // ファイルメイン処理
        int degree = 0;
        char line[256];
        while (!feof(fileToProcess)) {
            int ch, i = 0;

            // 1行分のデータを読み取り
            while ((ch = fgetc(fileToProcess)) != EOF && ch != '\n') {
                line[i++] = ch;
            }
            line[i] = '\0';  // 終端文字を追加

            // ここで line に格納されたデータを処理します
            if (strcmp(line, "0d") == 0) {
                degree = 0;
            } else if (strcmp(line, "45d") == 0) {
                degree = 45;
            } else if (strcmp(line, "90d") == 0) {
                degree = 90;
            } else if (strcmp(line, "135d") == 0) {
                degree = 135;
            } else if (strcmp(line, "180d") == 0) {
                degree = 180;
            } else if (strcmp(line, "225d") == 0) {
                degree = 225;
            } else if (strcmp(line, "270d") == 0) {
                degree = 270;
            } else if (strcmp(line, "315d") == 0) {
                degree = 315;
            }

            // 最後の読み取りが EOF だった場合、ループを終了
            if (ch == EOF) {
                break;
            }
        }

        // ファイル後処理(削除)
        fclose(fileToProcess);

        #ifdef MAKE_SIM //シミュレータ環境では動作しない
            remove(filename);
        #endif

        // 格納
        this->generalData.setMinifigDegree(degree);
        printf("[ ファイル読み込み ]ミニフィグの角度の取得に成功\n");

    } else {
        //printf("%s does not exist.\n", filename);
    }
}

void ReadSig::main() {
    this->storeRoute(ROUTE_PATH);
    this->storeMinifigLabel(MINIFIG_LABEL_PATH);
}