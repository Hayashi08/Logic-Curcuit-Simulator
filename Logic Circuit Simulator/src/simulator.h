#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "ofMain.h"
#include "gates.h"

#define GATE_LIMIT 20  //論理ゲートの生成可能数

//回路作成画面
class Simulator
{
public:
    Simulator();

    void setup();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    bool range(int maxX, int X, int minX, int maxY, int Y, int minY);
    int gateOperate(int gateID);

    Gates gate[GATE_LIMIT];  //回路作成に使用する論理回路
    Gates gate_generate;     //論理回路を生成する場所
    Gates gate_arg;          //Gate_name(論理回路名)を引数として使うためのインスタンス

    //論理ゲート画像の大きさ・位置座標
    int NAND_w,NAND_h,NAND_x,NAND_y;
    int AND_w,AND_h,AND_x,AND_y;
    int OR_w,OR_h,OR_x,OR_y;
    int NOT_w,NOT_h,NOT_x,NOT_y;

    int Off_w,Off_h,Off_x,Off_y;
    int On_w,On_h,On_x,On_y;
    int Q_w,Q_h,Q_x,Q_y;
    int NotQ_w,NotQ_h,NotQ_x,NotQ_y;

    int Clone_w,Clone_h,Clone_x,Clone_y;

    int gateCount;  //論理ゲートのカウント
    int wireCount;  //ワイヤーのカウント

    //ワイヤー生成位置座標
    float wireInput_ptX[GATE_LIMIT], wireInput_ptY[GATE_LIMIT];
    float wireOutput_ptX[GATE_LIMIT], wireOutput_ptY[GATE_LIMIT];
    int wireInput_gateID[GATE_LIMIT], wireOutput_gateID[GATE_LIMIT];
    //ワイヤーの中間座標
    float line_x[4],line_y[4];

    int Q_ID,NotQ_ID;  //QがあるゲートID
    int output_flag;  //出力フラッグ
    int circuit_complete;  //回路が完成してるかどうかのフラッグ

    //計算結果
    int result, result_x, result_y;
    string result_st;

    ofImage img_Reset;  //RESETボタン
    ofImage img_Output; //OUTPUTボタン

    ofTrueTypeFont font_Output;  //計算結果のフォント

    int stateQ,stateNotQ;

};

#endif // SIMULATOR_H
