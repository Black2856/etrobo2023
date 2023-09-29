/*
 * クラス名:readSig
 * 作成日:2023/09/28
 * 作成者:船田
 */

#include "ReadSig.h"

void ReadSig::processAndDeleteFile(const char* filename) {
    // ファイルが存在するかどうかを確認
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);

        // ファイルの内容を処理
        FILE* fileToProcess = fopen(filename, "r");
        if (fileToProcess == NULL) {
            printf("Failed to open the file %s\n", filename);
            return;
        }

        char ch;
        printf("Content of %s:\n", filename);
        while ((ch = fgetc(fileToProcess)) != EOF) {
            putchar(ch);
        }

        fclose(fileToProcess);

        // ファイルを削除
        if (remove(filename) != 0) {
            perror("Error deleting the file");
        } else {
            //printf("\n%s has been deleted successfully.\n", filename);
        }
    } else {
        printf("%s does not exist.\n", filename);
    }
}

// 2つの文字列を結合する関数
void ReadSig::concatenateStrings(char *result, const char *str1, const char *str2) {
    int i, j;

    // str1をresultにコピー
    for (i = 0; str1[i] != '\0'; i++) {
        result[i] = str1[i];
    }

    // str2をresultの終わりに追加
    for (j = 0; str2[j] != '\0'; j++) {
        result[i+j] = str2[j];
    }

    result[i+j] = '\0'; // 結合された文字列をヌル終端
}

void ReadSig::main() {
    char fullpath[256];
    this->concatenateStrings(fullpath, RECV_PATH, "test.txt");
    this->processAndDeleteFile(fullpath);
}