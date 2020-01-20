#include "simulator_start.h"

Simulator_Start::Simulator_Start()
{
    title.load("frabk.ttf", 80);
    switch_start.load("frabk.ttf", 60);

    //タイトルのサイズと表示座標のセット
    title_w = title.stringWidth("Logic Circuit Simulator");
    title_h = title.stringHeight("Logic Circuit Simulator");
    title_x = ofGetWidth()/2 - title_w/2;
    title_y = ofGetHeight()/3 + title_h/2;

    //Startスイッチのサイズと表示座標のセット
    start_w = switch_start.stringWidth("Start");
    start_h = switch_start.stringHeight("Start");
    start_x = ofGetWidth()/2 - start_w/2;
    start_y = ofGetHeight()*3/5 + start_h/2;
}

void Simulator_Start::draw(){

   //青色でタイトルを表示
   ofSetColor(0, 0, 255); 
   title.drawString("Logic Circuit Simulator", title_x, title_y);

   //黒色でStartスイッチを表示
   ofSetColor(0, 0, 0);
   switch_start.drawString("Start", start_x, start_y);

}

int Simulator_Start::mousePressed(int x, int y, int button){
    //Startスイッチが押されたかどうか
    if(range(start_x + start_w, x, start_x, start_y, y, start_y - start_h)){
        return 1;  //押された
    }else{
        return 0;  //押されてない
    }

}

//X,Yが指定範囲内にあるかを判定
bool Simulator_Start::range(int maxX, int X, int minX, int maxY, int Y, int minY){
    if((maxX >= X && X >= minX) && (maxY >= Y && Y >= minY)){
        return true;
    }
    return false;
}
