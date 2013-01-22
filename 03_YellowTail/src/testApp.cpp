#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofEnableSmoothing();

    max = 10;
	pressed = false;
    
    ofxSuperColliderServer::init();
    
    synth = new ofxSCSynth("yellow_fx");
    synth->create();
}

//--------------------------------------------------------------
void testApp::update(){
	for (int i = 0; i < gestures.size(); i++) {
		if (i != gestures.size()-1) {
			gestures[i]->update();
		} else if (!pressed) {
			gestures[i]->update();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    fade();
    
    ofNoFill();
	ofSetColor(255);
	for (int i = 0; i < gestures.size(); i++) {
		gestures[i]->draw();
	}
    
    ofDrawBitmapString("gestures num = " + ofToString(gestures.size()), 10, 20);
    ofDrawBitmapString("f: fullscreen, r: clear, d: pop_front", 10, 40);
}

void testApp::exit(){
    for (int i = 0; i < gestures.size(); i++) {
        gestures[i]->synth->free();
    }
    synth->free();
}

void testApp::fade(){
    ofFill();
	ofSetColor(0, 31);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}
	if (key == 'r') {
        for (int i = 0; i < gestures.size(); i++) {
            gestures[i]->synth->free();
        }
        gestures.clear();
	}
    if (key == 'd') {
        if (gestures.size() > 0) {
            gestures[0]->synth->free();
            //delete gestures[0];
            gestures.pop_front();
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if (ofVec2f(x,y).distance(lastMouse) > 1) {
        gestures[gestures.size()-1]->addPoint(ofVec2f(x, y));
    }
	lastMouse.set(x, y);
    pressed = true;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	pressed = true;

	Gesture *g = new Gesture();
	g->addPoint(ofVec2f(x, y));
	gestures.push_back(g);
    
    if (gestures.size() > max) {
        gestures[0]->synth->free();
        delete gestures[0];
        gestures.pop_front();
    }
	
	lastMouse.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	pressed = false;
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