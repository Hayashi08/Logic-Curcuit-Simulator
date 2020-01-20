#include "simulator.h"

Simulator::Simulator()
{
    gateCount = -1;
    wireCount = 0;

    output_flag = 0;
    circuit_complete = 0;

    //ゲートの位置座標の初期化
    NAND_w = gate_generate.img_NAND.getWidth();
    NAND_h = gate_generate.img_NAND.getHeight();
    NAND_x = 0; NAND_y = ofGetHeight() - NAND_h;

    AND_w = gate_generate.img_AND.getWidth();
    AND_h = gate_generate.img_AND.getHeight();
    AND_x = NAND_w + 15; AND_y = ofGetHeight() - AND_h;

    OR_w = gate_generate.img_OR.getWidth();
    OR_h = gate_generate.img_OR.getHeight();
    OR_x = AND_x + AND_w + 15; OR_y = ofGetHeight() - OR_h;

    NOT_w = gate_generate.img_NOT.getWidth();
    NOT_h = gate_generate.img_NOT.getHeight();
    NOT_x = OR_x + OR_w + 15; NOT_y = ofGetHeight() - NOT_h;

    Off_w = gate_generate.font.stringWidth("0");
    Off_h = gate_generate.font.stringHeight("0");
    Off_x = NOT_x + NOT_w + 15; Off_y = ofGetHeight() - 15;

    On_w = gate_generate.font.stringWidth("1");
    On_h = gate_generate.font.stringHeight("1");
    On_x = Off_x + Off_w + 15; On_y = ofGetHeight() - 15;

    Q_w = gate_generate.font.stringWidth("Q");
    Q_h = gate_generate.font.stringHeight("Q");
    Q_x = On_x + On_w + 15; Q_y = ofGetHeight() - 15;

    Q_w = gate_generate.font.stringWidth("Q");
    Q_h = gate_generate.font.stringHeight("Q");
    Q_x = On_x + On_w + 15; Q_y = ofGetHeight() - 15;

    NotQ_w = gate_generate.font.stringWidth("~Q");
    NotQ_h = gate_generate.font.stringWidth("~Q");
    NotQ_x = Q_x + Q_w + 15; NotQ_y = ofGetHeight() - 15;

    Clone_w = 20;
    Clone_h = 20;
    Clone_x = NotQ_x + NotQ_w + 45; Clone_y = ofGetHeight() - 40;

    for(int i = 0; i < 20; i++){
        wireInput_ptX[i] = 0; wireInput_ptY[i] = 0;
        wireOutput_ptX[i] = 0; wireOutput_ptY[i] = 0;
    }

    img_Reset.load("Reset.png");
    img_Output.load("OUTPUT.png");

    font_Output.load("frabk.ttf",50);

    stateQ = 0;
    stateNotQ = 1;

    NotQ_ID = -1;
}

void Simulator::draw(){
    ofSetColor(255,255,255);

    //Resetボタン
    img_Reset.draw(0, 0);

    //OUTPUTボタン
    img_Output.draw(ofGetWidth() - img_Output.getWidth(), 0);

    //NANDゲート
    gate_generate.img_NAND.draw(NAND_x,NAND_y);
    //ANDゲート
    gate_generate.img_AND.draw(AND_x,AND_y);
    //ORゲート
    gate_generate.img_OR.draw(OR_x,OR_y);
    //NOTゲート
    gate_generate.img_NOT.draw(NOT_x,NOT_y);

    //入力bit,Qの生成位置
    ofSetColor(ofColor::black);
    gate_generate.font.drawString("0", Off_x,Off_y);
    gate_generate.font.drawString("1", On_x, On_y);
    gate_generate.font.drawString("Q", Q_x, Q_y);
    gate_generate.font.drawString("~Q", NotQ_x, NotQ_y);

    //Cloneの生成位置
    ofFill();
    ofDrawCircle(Clone_x, Clone_y, 10);
    ofNoFill();

    //配置した論理ゲートの描画
    for(int i = 0; i <= gateCount; i++){
            gate[i].draw();
    }

    //論理回路の出力を計算
    if(output_flag == 1){

        //回路が完成しているかチェック
        if(circuit_complete == 1){
            for(int i = 0; i <= gateCount; i++){
                //入力のチェック
                for(int j = 0; j < gate[i].inputconnectorCount; j++){
                    if(gate[i].inputconnector_flag[j] == 1){
                        circuit_complete = 0;
                        break;
                    }
                }
                //出力のチェック
                for(int j = 0; j < gate[i].outputconnectorCount; j++){
                    if(gate[i].outputconnector_flag[j] == 1){
                        circuit_complete = 0;
                        break;
                    }
                }
                //未完成だったら反復を脱出
                if(circuit_complete == 0){
                    break;
                }
            }
        }

        //完成(計算結果を出力)
        if(circuit_complete == 1){

            result = gateOperate(Q_ID);
            result_st = "Q is " + ofToString(result);
            result_x = ofGetWidth() - img_Output.getWidth();
            result_y = img_Output.getHeight() + font_Output.stringHeight(result_st);
            ofSetColor(ofColor::blue);
            font_Output.drawString(result_st, result_x, result_y);

            if(NotQ_ID >= 0){
                result = result ^ 1;
                result_st = "~Q is " + ofToString(result);
                result_y += font_Output.stringHeight(result_st);
                font_Output.drawString(result_st, result_x, result_y);

            }

            for(int i = 0; i <= gateCount; i++){
                gate[i].runCount = 0;
            }
        }
        //未完成(計算をせず注意を表示)
        else{
            result_st = "Circuit is incomplete!";
            result_x = ofGetWidth() - font_Output.stringWidth(result_st);
            result_y = img_Reset.getHeight() + font_Output.stringHeight(result_st);
            ofSetColor(ofColor::red);
            font_Output.drawString(result_st, result_x, result_y);
        }

    }

    //ワイヤーの描画
    for(int i = 0; i < wireCount; i++){

        if(wireInput_ptX[i] != 0 && wireOutput_ptX[i] != 0){

            //位置補正
            if(gate[wireInput_gateID[i]].inputconnectorCount == 1){

                if(abs(wireOutput_ptY[i] - wireInput_ptY[i]) <= 55){
                    gate[wireInput_gateID[i]].ptY +=  wireOutput_ptY[i] - wireInput_ptY[i];
                    wireInput_ptY[i] += wireOutput_ptY[i] - wireInput_ptY[i];
                }

                if(gate[wireInput_gateID[i]].gate_name == gate_arg.Q){
                    Q_ID = wireInput_gateID[i];
                }else if(gate[wireInput_gateID[i]].gate_name == gate_arg.NotQ){
                    NotQ_ID = wireInput_gateID[i];
                }

            }

            ofSetLineWidth(3);
            //ofSetColor(ofColor::black);
            if(output_flag == 1){
                if(gateOperate(wireOutput_gateID[i]) == 1 && output_flag == 1){
                    ofSetColor(ofColor::red);
                }else{
                    ofSetColor(ofColor::black);
                }
                for(int i = 0; i <= gateCount; i++){
                    gate[i].runCount = 0;
                }
            }else{
                ofSetColor(ofColor::black);
            }


            if(wireInput_ptX[i] >= wireOutput_ptX[i]){
                if(gate[wireOutput_gateID[i]].gate_name == gate_arg.Clone){
                    line_x[0] = wireOutput_ptX[i];
                }else{
                    line_x[0] = (wireInput_ptX[i] - wireOutput_ptX[i])/2 + wireOutput_ptX[i];
                }
                line_y[0] = wireOutput_ptY[i];
                line_x[1] = line_x[0];
                line_y[1] = wireInput_ptY[i];
                ofLine(wireOutput_ptX[i], wireOutput_ptY[i], line_x[0], line_y[0]);
                ofLine(line_x[0], line_y[0], line_x[1], line_y[1]);
                ofLine(line_x[1], line_y[1], wireInput_ptX[i], wireInput_ptY[i]);
            }else{
                if(gate[wireOutput_gateID[i]].gate_name == gate_arg.Clone){
                    line_x[0] = wireOutput_ptX[i];
                }else{
                    line_x[0] = wireOutput_ptX[i] + 60;
                }
                line_y[0] = wireOutput_ptY[i];
                line_x[1] = line_x[0];
                line_y[1] = wireOutput_ptY[i] - (wireOutput_ptY[i] - wireInput_ptY[i])/3;
                line_x[2] = wireInput_ptX[i] - 60;
                line_y[2] = wireInput_ptY[i] + (wireOutput_ptY[i] - wireInput_ptY[i])/3;
                line_x[3] = line_x[2];
                line_y[3] = wireInput_ptY[i];
                ofLine(wireOutput_ptX[i], wireOutput_ptY[i], line_x[0], line_y[0]);
                ofLine(line_x[0], line_y[0], line_x[1], line_y[1]);
                ofLine(line_x[1], line_y[1], line_x[2], line_y[2]);
                ofLine(line_x[2], line_y[2], line_x[3], line_y[3]);
                ofLine(line_x[3], line_y[3], wireInput_ptX[i], wireInput_ptY[i]);
            }

        }
    }

}

void Simulator::mousePressed(int x, int y, int button){

    //NANDゲートを使用  
    if(range(NAND_w, x, NAND_x, ofGetHeight(), y, NAND_y)){
        gateCount++;
        gate[gateCount].setup(gate_arg.NAND);
    }
    //ANDゲートを使用
    else if(range(AND_x + AND_w, x, AND_x, ofGetHeight(), y, AND_y)){
        gateCount++;
        gate[gateCount].setup(gate_arg.AND);
    }
    //ORゲートを使用
    else if(range(OR_x + OR_w, x, OR_x, ofGetHeight(), y, OR_y)){
        gateCount++;
        gate[gateCount].setup(gate_arg.OR);
    }
    //NOTゲートを使用
    else if(range(NOT_x + NOT_w, x, NOT_x, ofGetHeight(), y, NOT_y)){
        gateCount++;
        gate[gateCount].setup(gate_arg.NOT);
    }
    //0bitを使用
    else if(range((Off_x + Off_w), x, Off_x, Off_y, y, (Off_y - Off_h))){
        gateCount++;
        gate[gateCount].setup(gate_arg.Off);
    }
    //1bitを使用
    else if(range((On_x + On_w), x, On_x, On_y, y, (On_y - On_h))){
        gateCount++;
        gate[gateCount].setup(gate_arg.On);
    }
    //Qを使用
    else if(range((Q_x + Q_w), x, Q_x, Q_y, y, (Q_y - Q_h))){
        gateCount++;
        gate[gateCount].setup(gate_arg.Q);
    }
    //~Qを使用
    else if(range((NotQ_x + NotQ_w), x, NotQ_x, NotQ_y, y, (NotQ_y - NotQ_h))){
        gateCount++;
        gate[gateCount].setup(gate_arg.NotQ);
    }
    //Cloneを使用
    else if(range(Clone_x + 10, x, Clone_x - 10, Clone_y + 10, y, Clone_y - 10)){
        gateCount++;
        gate[gateCount].setup(gate_arg.Clone);
    }

    //コネクタをクリック
    for(int i = 0; i <= gateCount; i++){

        //Cloneの場合
        if(gate[i].gate_name == gate_arg.Clone){

            if(range(gate[i].ptX + 10, x, gate[i].ptX - 10, gate[i].ptY + 10, y, gate[i].ptY - 10)){

                if(wireOutput_ptX[wireCount] != 0 && gate[i].inputconnector_flag[0] == 1){
                    wireInput_ptX[wireCount] = gate[i].ptX;
                    wireInput_ptY[wireCount] = gate[i].ptY;
                    wireInput_gateID[wireCount] = i;
                    gate[i].inputconnector_flag[0] = 0;
                }else if(wireInput_ptX[wireCount] != 0 && gate[i].outputconnector_flag[1] == 1){
                    wireOutput_ptX[wireCount] = gate[i].ptX;
                    wireOutput_ptY[wireCount] = gate[i].ptY;
                    wireOutput_gateID[wireCount] = i;
                    if(gate[i].outputconnector_flag[0] == 1){
                        gate[i].outputconnector_flag[0] = 0;
                    }else{
                        gate[i].outputconnector_flag[1] = 0;
                    }
                }

            }

        }else{
            //入力コネクタ
            for(int j = 0; j < gate[i].inputconnectorCount; j++){

                if(range(gate[i].inputconnector_ptX[j] + 10, x, gate[i].inputconnector_ptX[j] - 10,
                         gate[i].inputconnector_ptY[j] + 10, y, gate[i].inputconnector_ptY[j] - 10)
                        && gate[i].inputconnector_flag[j] == 1){

                    wireInput_ptX[wireCount] = gate[i].inputconnector_ptX[j];
                    wireInput_ptY[wireCount] = gate[i].inputconnector_ptY[j];
                    wireInput_gateID[wireCount] = i;
                    gate[i].inputconnector_flag[j] = 0;

                }

            }
            //出力コネクタ
            for(int j = 0; j < gate[i].outputconnectorCount; j++){

                if(range(gate[i].outputconnector_ptX[j] + 10, x, gate[i].outputconnector_ptX[j] - 10,
                         gate[i].outputconnector_ptY[j] + 10, y, gate[i].outputconnector_ptY[j] - 10)
                        &&  gate[i].outputconnector_flag[j] == 1){

                        wireOutput_ptX[wireCount] = gate[i].outputconnector_ptX[j];
                        wireOutput_ptY[wireCount] = gate[i].outputconnector_ptY[j];
                        wireOutput_gateID[wireCount] = i;
                        gate[i].outputconnector_flag[j] = 0;

                }

            }

        }

    }
    //ワイヤーの接続を確認
    if(wireInput_ptX[wireCount] != 0 && wireOutput_ptX[wireCount] != 0){
        gate[wireInput_gateID[wireCount]].getInput(wireOutput_gateID[wireCount]);
        gate[wireOutput_gateID[wireCount]].getOutput(wireInput_gateID[wireCount]);
        wireCount++;
    }

    //入力bitを反転
    for(int i = 0; i <= gateCount; i++){
        if(gate[i].gate_name == gate_arg.Off && gate[i].dragged_flag == 0){
            if(gate[i].outputconnector_flag[0] == 0){
                if(range(gate[i].ptX + Off_w, x, gate[i].ptX, gate[i].ptY, y, gate[i].ptY - Off_h)){
                    gate[i].setup(gate_arg.On);
                }
            }
        }
        else if(gate[i].gate_name == gate_arg.On && gate[i].dragged_flag == 0){
            if(gate[i].outputconnector_flag[0] == 0){
                if(range(gate[i].ptX + On_w, x, gate[i].ptX, gate[i].ptY, y, gate[i].ptY - On_h)){
                    gate[i].setup(gate_arg.Off);
                }
            }
        }
    }

    //RESETボタン
    if(range(img_Reset.getWidth(), x, 0, img_Reset.getHeight(), y, 0)){
        for(int i = 0; i <= gateCount; i++){
            gate[i].setup(gate_arg.None);
        }
        for(int i = 0; i <= wireCount; i++){
            wireInput_ptX[i] = 0; wireInput_ptY[i] = 0;
            wireOutput_ptX[i] = 0; wireOutput_ptY[i] = 0;
        }
        gateCount = -1;
        wireCount = 0;
        output_flag = 0;
        stateQ = 0; stateNotQ = 1;
    }

    //OUTPUTボタン
    if(gateCount >= 0){
        if(range(ofGetWidth(), x, (ofGetWidth() - img_Output.getWidth()), img_Output.getHeight(), y, 0)){
            output_flag = 1;
            circuit_complete = 1;
        }
    }

}

//X,Yが指定範囲内にあるかを判定
bool Simulator::range(int maxX, int X, int minX, int maxY, int Y, int minY){
    if((maxX >= X && X >= minX) && (maxY >= Y && Y >= minY)){
        return true;
    }
    return false;
}

void Simulator::mouseDragged(int x, int y, int button){
    //ドラッグしているゲートの位置座標の更新
    gate[gateCount].mouseDragged(x,y);
}

void Simulator::mouseReleased(int x, int y, int button){
    //ドラッグの終了
    gate[gateCount].mouseReleased();
}

//論理回路演算
int Simulator::gateOperate(int gateID){
    int input, input1, input2,  output;

    //フィードバック処理
    gate[gateID].runCount++;
    if(gate[gateID].runCount > 1 && gate[gateID].gate_name != gate_arg.Clone){

        int nextID = gate[gateID].outputGateID[0];
        for(int i = 0; i < 2; i++){
            if(gate[gate[nextID].outputGateID[i]].gate_name == gate_arg.Q){
                return stateQ;
            }else if(gate[gate[nextID].outputGateID[i]].gate_name == gate_arg.NotQ){
                return stateNotQ;
            }else if(gate[gate[nextID].outputGateID[i]].gate_name == gate_arg.Clone){
                int nextID2 = gate[nextID].outputGateID[i];
                for(int j = 0; j < 2; j++){
                    if(gate[gate[nextID2].outputGateID[j]].gate_name == gate_arg.Q){
                        return stateQ;
                    }else if(gate[gate[nextID2].outputGateID[j]].gate_name == gate_arg.NotQ){
                        return stateNotQ;
                    }
                }
            }
        }

    }

    switch (gate[gateID].gate_name) {
    case gate_arg.Q:
        input = gateOperate(gate[gateID].inputGateID[0]);
        output = input;
        stateQ = output;
        stateNotQ = stateQ ^ 1;
        break;
    case gate_arg.NotQ:
        output = stateNotQ;
        break;
    case gate_arg.NAND:
        input1 = gateOperate(gate[gateID].inputGateID[0]);
        input2 = gateOperate(gate[gateID].inputGateID[1]);
        output = (input1 & input2) ^ 1;
        break;
    case gate_arg.AND:
        input1 = gateOperate(gate[gateID].inputGateID[0]);
        input2 = gateOperate(gate[gateID].inputGateID[1]);
        output = input1 & input2;
        break;
    case gate_arg.OR:
        input1 = gateOperate(gate[gateID].inputGateID[0]);
        input2 = gateOperate(gate[gateID].inputGateID[1]);
        output = input1 | input2;
        break;
    case gate_arg.NOT:
        input = gateOperate(gate[gateID].inputGateID[0]);
        output = input ^ 1;
        break;
    case gate_arg.Off:
        output = 0;
        break;
    case gate_arg.On:
        output = 1;
        break;
    case gate_arg.Clone:
        input = gateOperate(gate[gateID].inputGateID[0]);
        output = input;
        break;
    default:
        break;
    }

    return output;
}

