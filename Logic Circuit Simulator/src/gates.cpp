#include "gates.h"

Gates::Gates()
{
    gate_name = None;

    inputGateID[0] = -1; inputGateID[1] = -1;
    inputCount = 0;
    outputGateID[0] = -1; outputGateID[1] = -1;
    outputCount = 0;

    ptX = 0;
    ptY = 0;
    draw_flag = 0;
    inputconnector_flag[0] = 0; inputconnector_flag[1] = 0;
    outputconnector_flag[0] = 0; outputconnector_flag[1] = 0;

    img_NAND.load("NAND.png");
    img_AND.load("AND.png");
    img_OR.load("OR.png");
    img_NOT.load("NOT.png");

    font.load("frabk.ttf", 55);

    font_ward = "None";
    dragged_flag = 1;

    runCount = 0;
}

//使用する論理ゲートの名前を受け取り、セットアップする
void Gates::setup(Gate_name gate_arg){

    switch (gate_arg) {
    case NAND:
        gate_name = NAND;
        img_Gate = img_NAND;
        inputconnectorCount = 2;
        outputconnectorCount = 1;
        break;
    case AND:
        gate_name = AND;
        img_Gate = img_AND;
        inputconnectorCount = 2;
        outputconnectorCount = 1;
        break;
    case OR:
        gate_name = OR;
        img_Gate = img_OR;
        inputconnectorCount = 2;
        outputconnectorCount = 1;
        break;
    case NOT:
        gate_name = NOT;
        img_Gate = img_NOT;
        inputconnectorCount = 1;
        outputconnectorCount = 1;
        break;
    case Off:
        gate_name = Off;
        font_ward = "0";
        inputconnectorCount = 0;
        outputconnectorCount = 1;
        break;
    case On:
        gate_name = On;
        font_ward = "1";
        inputconnectorCount = 0;
        outputconnectorCount = 1;
        break;
    case Q:
        gate_name = Q;
        font_ward = "Q";
        inputconnectorCount = 1;
        outputconnectorCount = 0;
        break;
    case NotQ:
        gate_name = NotQ;
        font_ward = "~Q";
        inputconnectorCount = 1;
        outputconnectorCount = 0;
        break;
    case Clone:
        gate_name = Clone;
        inputconnectorCount = 1;
        outputconnectorCount = 2;
        break;
    case None:
        gate_name = None;
        inputGateID[0] = 0; inputGateID[1] = 0;
        inputCount = 0;
        outputGateID[0] = 0; outputGateID[1] = 0;
        outputCount = 0;
        ptX = 0;  ptY = 0;
        draw_flag = 0;
        inputconnectorCount = 0;
        inputconnector_flag[0] = 0; inputconnector_flag[1] = 0;
        outputconnectorCount = 0;
        outputconnector_flag[0] = 0; outputconnector_flag[1] = 0;
        font_ward = "None";
        dragged_flag = 1;
        runCount = 0;
        break;
    default:
        break;
    }
}

//論理ゲートを描く
void Gates::draw(){

    if(draw_flag == 1){

        switch (gate_name) {
        case NAND:
        case AND:
            ofSetColor(ofColor::white);
            img_Gate.draw(ptX, ptY);
            inputconnectorSet_double(ptX, ptY + img_Gate.getHeight()*2/3, ptX, ptY + img_Gate.getHeight()/3);
            outputconnectorSet(ptX + img_Gate.getWidth(), ptY + img_Gate.getHeight()/2);
            break;
        case OR:
            ofSetColor(ofColor::white);
            img_Gate.draw(ptX, ptY);
            inputconnectorSet_double(ptX + 27, ptY + img_Gate.getHeight()*2/3, ptX + 27, ptY + img_Gate.getHeight()/3);
            outputconnectorSet(ptX + img_Gate.getWidth(), ptY + img_Gate.getHeight()/2);
            break;
        case NOT:
            ofSetColor(ofColor::white);
            img_Gate.draw(ptX, ptY);
            inputconnectorSet_single(ptX, ptY + img_Gate.getHeight()/2);
            outputconnectorSet(ptX + img_Gate.getWidth(), ptY + img_Gate.getHeight()/2);
            break;
        case Off:
        case On:
            ofSetColor(ofColor::black);
            font.drawString(font_ward, ptX, ptY);
            outputconnectorSet(ptX + font.stringWidth(font_ward) + 15, ptY - font.stringHeight(font_ward)/2);
            break;
        case Q:
        case NotQ:
            ofSetColor(ofColor::black);
            font.drawString(font_ward, ptX, ptY);
            inputconnectorSet_single(ptX - 15, ptY - font.stringHeight(font_ward)/2 + 15);
            break;
        case Clone:
            ofSetColor(ofColor::black);
            ofFill();
            ofDrawCircle(ptX, ptY, 10);
            ofNoFill();
            break;
        default:
            break;
        }
    }

}

//入力コネクタを1つセット
void Gates::inputconnectorSet_single(int x, int y){
    if(inputconnector_flag[0] == 1){
        ofSetColor(0,0,0);
        ofFill();
        ofDrawCircle(x, y, 10);
        ofNoFill();

        inputconnector_ptX[0] = x;
        inputconnector_ptY[0] = y;
    }
}

//入力コネクタを2つセット
void Gates::inputconnectorSet_double(int x1, int y1, int x2, int y2){
    if(inputconnector_flag[0] == 1){
        ofSetColor(0,0,0);
        ofFill();
        ofDrawCircle(x1, y1, 10);
        ofNoFill();

        inputconnector_ptX[0] = x1;
        inputconnector_ptY[0] = y1;
    }
    if(inputconnector_flag[1] == 1){
        ofSetColor(0,0,0);
        ofFill();
        ofDrawCircle(x2, y2, 10);
        ofNoFill();

        inputconnector_ptX[1] = x2;
        inputconnector_ptY[1] = y2;
    }
}

//出力コネクタをセット
void Gates::outputconnectorSet(int x, int y){
    if(outputconnector_flag[0] == 1){
        ofSetColor(0,0,0);
        ofFill();
        ofDrawCircle(x, y, 10);
        ofNoFill();

        outputconnector_ptX[0] = x;
        outputconnector_ptY[0] = y;
    }
}

void Gates::mouseDragged(int x, int y){
    if(dragged_flag == 1){
        switch (gate_name) {
        case NAND:
        case AND:
        case OR:
        case NOT:
            ptX = x - img_Gate.getWidth()/2;
            ptY = y - img_Gate.getHeight()/2;
            break;
        case Off:
        case On:
        case Q:
        case NotQ:
            ptX = x - font.stringWidth(font_ward)/2;
            ptY = y + font.stringHeight(font_ward)/2;
            break;
        case Clone:
            ptX = x;
            ptY = y;
        default:
            break;
        }

        draw_flag = 1;
    }
}

void Gates::mouseReleased(){
    if(dragged_flag == 1){
        dragged_flag = 0;

        for(int i = 0; i < inputconnectorCount; i++){
            inputconnector_flag[i] = 1;
        }

        if(outputconnectorCount > 0){
            outputconnector_flag[0] = 1;
            outputconnector_flag[1] = 1;
        }
    }
}

//入力コネクタに繋がっているゲートのIDを手に入れる
void Gates::getInput(int gateID){
    inputGateID[inputCount++] = gateID;
}
//出力先のゲートのIDを手に入れる
void Gates::getOutput(int gateID){
    outputGateID[outputCount++] = gateID;
}
