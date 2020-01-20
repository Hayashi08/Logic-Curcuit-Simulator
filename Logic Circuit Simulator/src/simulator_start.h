#ifndef SIMULATOR_START_H
#define SIMULATOR_START_H
#include "ofMain.h"

//起動画面
class Simulator_Start
{
public:
    Simulator_Start();

    void draw();
    int mousePressed(int x, int y, int button);
    bool range(int maxX, int X, int minX, int maxY, int Y, int minY);

    ofTrueTypeFont title,switch_start;  //タイトルとStartスイッチ

    int title_w, title_h, title_x, title_y;  //タイトルのサイズと表示座標
    int start_w, start_h, start_x, start_y;  //Startスイッチのサイズと表示座標
};

#endif // SIMULATOR_START_H
