#ifndef GATES_H
#define GATES_H

#include "ofMain.h"

//論理ゲートのクラス
class Gates
{
public:
    Gates();

    //論理ゲートの名前...Noneはなにもなし、Off,Onは入力ビットの0,1、Qは出力結果
    enum Gate_name {NAND,AND,OR,NOT,None,Off,On,Q,NotQ,Clone};
    Gate_name gate_name;

    int inputGateID[2];  //入力に接続されているゲートのID
    int inputCount;      //現在の入力数
    int outputGateID[2]; //出力先のゲートのID
    int outputCount;     //現在の出力数

    void setup(Gate_name gate_arg);
    void draw();
    void inputconnectorSet_single(int x, int y);
    void inputconnectorSet_double(int x1, int y1, int x2, int y2);
    void outputconnectorSet(int x, int y);
    void mouseDragged(int x, int y);
    void mouseReleased();
    void getInput(int gateID);
    void getOutput(int gateID);

    //論理ゲートの位置座標
    int ptX;
    int ptY;

    int inputconnectorCount;  //入力コネクタの数
    int outputconnectorCount;  //出力コネクタの数
    //コネクタの位置座標
    int inputconnector_ptX[2];
    int inputconnector_ptY[2];
    int outputconnector_ptX[2];
    int outputconnector_ptY[2];

    //フラッグ
    int dragged_flag;
    int draw_flag;
    int inputconnector_flag[2],outputconnector_flag[2];

    //論理ゲート画像
    ofImage img_Gate;
    ofImage img_NAND, img_AND, img_OR, img_NOT;

    //入力ビット,Qのフォント
    ofTrueTypeFont font;
    int font_w,font_h;
    string font_ward;

    int runCount;

};

#endif // GATES_H
