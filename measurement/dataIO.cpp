#include "dataIO.h"

using namespace std;
using namespace ev3api;

DataIO* DataIO::m_DataIO = NULL;

DataIO::DataIO(){
    strcpy(this->column[0], "time(ms)");
    clock.reset();
}

DataIO::~DataIO(){}

DataIO* DataIO::getInstance(){
    if (m_DataIO == NULL){
        m_DataIO = new DataIO();
    }
    return m_DataIO;
}

void DataIO::addData(const char *column, const char *val){
    addDataProcess(column, val);
}
void DataIO::addData(const char *column, const int val){
    char buf[20];
    sprintf(buf, "%d", val);
    addDataProcess(column, buf);
}
void DataIO::addData(const char *column, const float val){
    char buf[20];
    sprintf(buf, "%f", val);
    addDataProcess(column, buf);
}
void DataIO::addData(const char *column, const double val){
    char buf[20];
    sprintf(buf, "%lf", val);
    addDataProcess(column, buf);
}

void DataIO::addDataProcess(const char *column, const char *str){
    int f = -1;
    for(int i = 0; i < dataSize; i++){ //カラムがあるかどうかチェック
        if(strcmp(this->column[i], column) == 0){
            f = i;
            break;
        }
    }
    
    if(f != -1){ //データ追加
        strcpy(this->row[f], str);
        if(addedData == 0){
            addedData = 1;
        }
    }else{
        strcpy(this->column[columnIndex], column);
        strcpy(this->row[columnIndex], str);
        columnIndex++;
        addedData = 2;
    }
}

void DataIO::dataOutput(const char *fileName){
    if(addedData == 0){ //addDataされてなければファイルの更新をしない
        return;
    }

    addData("time(ms)", (int)(clock.now() / 1000) );
    if(addedData == 2){//列データ更新
        char buf[100];
        sprintf(buf,"column_%s",fileName);

        FILE *fp1 = fopen(buf, "w+");
        fseek(fp1, 0, SEEK_SET);
        for(int i = 0; i < dataSize; i++){
            fputs(column[i], fp1);
            fputs(",", fp1);
        }
        fclose(fp1);
    }

    FILE *fp2 = fopen(fileName, "a+");//行データ追加
    fputs("\n", fp2);
    for(int i = 0; i < dataSize; i++){
        fputs(row[i], fp2);
        fputs(",", fp2);
    }
    fclose(fp2);

    for(int i = 0; i < dataSize; i++){ //row初期化
        strcpy(row[i], "");
    }

    addedData = 0;
}

void DataIO::fileOutput(const char *fileName, const char *text){
    FILE *fp = fopen(fileName, "a+");
    fputs(text, fp);
    fputs("\n", fp);
    fclose(fp);
}