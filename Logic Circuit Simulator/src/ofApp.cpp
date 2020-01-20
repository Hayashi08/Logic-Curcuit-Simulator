#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowPosition(20,60);
    ofSetWindowTitle("Logic Circuit Simulator");  //ウィンドウにタイトルを表示
    display_id = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);  //背景は白

    switch (display_id) {
    case 0:  //起動画面
        start.draw();
        break;
    case 1:  //回路作成画面
        sim.draw();
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(display_id == 1){  //回路作成画面
        sim.mouseDragged(x, y, button);
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    switch(display_id){
    case 0:  //起動画面
        if(start.mousePressed(x, y, button) == 1){  //Startスイッチが押されたら
            display_id = 1;  //回路作成画面へ
        }
        break;
    case 1:  //回路作成画面
        sim.mousePressed(x, y, button);
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(display_id == 1){  //回路作成画面
        sim.mouseReleased(x, y, button);
    }

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
