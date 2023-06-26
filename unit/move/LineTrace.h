/*
 * クラス名:LineTrace
 * 作成日:2023/06/26
 * 作成者:松尾
 */
#ifndef LINE_TRACE_H
#define LINE_TRACE_H

#include "unit.h"
#include "PIDControl.h"
#include "DeviceInOut.h"

class LineTrace {
public:
    LineTrace();
    void Trace(int pwm);
private:
    unit::pid_t mPID;
    PIDControl pidControl;
    DeviceInOut& device;
    //ここの書き方教えて
    //@船田↓
    // PID制御は計算クラスにインスタンス持たせるの？
    // 線つながってないけど
    
    // パッケージ間で参照してるからok、PID制御のヘッダーファイルをインクルードしてPID制御クラスをインスタンスしてどうのこうのする
    // PID制御クラスの担当は松尾氏だと思われ
    //PID制御クラスの操作で計算ってあるけどそれは松尾が考えるの？　←たしかスケジュールに書いてある
    //PID制御クラスの担当松尾です。計算って直線とカーブでPID値を分けるだけじゃだめ？ ←PID値はscene(脚本パッケージ)のインスタンスで決めるのでPIDはただ計算するクラスである
    //具体的に計算は何をする？　←単にPIDの計算をするクラスで計算メソッドの返り値は操作量(float)、クラス図に不備とかあるんで追加メンバー変数が必要だと思ったら追加してねん
    //承知byMK
}

#endif  // LINE_TRACE_H