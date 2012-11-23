#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofBackgroundHex(0x000000);
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    //ofEnableSmoothing();
    //ofSetVerticalSync(true);
    
    ofxSuperColliderServer::init();
    
    fx = new ofxSCSynth("fx");
    fx->set("lpf", 1000);
    fx->set("amp", 1.5);
    fx->create();
    
    synthNum = 0;
    
    //ofHideCursor();
}

//--------------------------------------------------------------
void testApp::update(){
    for (int i = 0; i < saws.size(); i++) {
        saws[i]->update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    for (int i = saws.size()-1; i >= 0; i--) {
        saws[i]->draw();
    }
}

//--------------------------------------------------------------
void testApp::exit(){
    fx->free();
    for (int i = 0; i < saws.size(); i++) {
        saws[i]->synth->free();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (key == 'a') {
        SawSynth *s = new SawSynth(synthNum);
        saws.push_back(s);
        synthNum++;
    }
    if (key == 's') {
        if(saws.size()>0){
            saws[0]->synth->free();
            //saws.pop_front();
            saws[0]->death = true;
        }
    }
    if (key == 'd') {
        if(saws.size()>0){
            saws[saws.size()-1]->synth->free();
            saws.pop_back();
        }
    }
    if (key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //synth->create();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    //synth->free();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}