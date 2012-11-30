#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();
	ofSetFrameRate(60);
	ofEnableSmoothing();
	pressed = false;
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
	ofFill();
	ofSetColor(0, 31);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(255);
	for (int i = 0; i < gestures.size(); i++) {
		gestures[i]->draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f') {
		ofToggleFullscreen();
	}
	if (key == 'r') {
		gestures.clear();
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
	if (ofVec2f(x,y).distance(lastMouse) < 30) {
		gestures[gestures.size()-1]->addPoint(ofVec2f(x, y));
	}
	lastMouse.set(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	pressed = true;
	Gesture *g = new Gesture();

	g->addPoint(ofVec2f(x, y));
	gestures.push_back(g);
	
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