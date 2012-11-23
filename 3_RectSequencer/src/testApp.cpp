#include "testApp.h"

void testApp::setup() {
	ofxSuperColliderServer::init();
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackgroundHex(0x000000);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	pitchRatio[0]= 1.0;
    pitchRatio[1]= 9.0/8.0;
    pitchRatio[2]= 5.0/4.0;
    pitchRatio[3]= 4.0/3.0;
    pitchRatio[4]= 3.0/2.0;
    pitchRatio[5]= 5.0/3.0;
    pitchRatio[6]= 15.0/8.0;
	
	bDrawRect = false;
	
	reverb = new ofxSCSynth("fx");
    reverb->create();
}

void testApp::exit() {
	reverb->free();
}

void testApp::update() {
    for (int i=0; i<rects.size(); i++) {
        rects[i]->update();
    }
}

void testApp::draw() {
    ofSetColor(0, 0, 0, 20);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    for (int i=0; i<rects.size(); i++) {
        rects[i]->draw();
    }
    
    if (bDrawRect) {
        ofNoFill();
        ofSetColor(255, 255, 255, 63);
        ofRect(drawPos.x, drawPos.y, mouseX - drawPos.x, mouseY-drawPos.y);
    }
	
	string info = "";
	info += "rect count: "+ofToString(rects.size(),0)+"\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

void testApp::keyPressed(int key) {
	if(key == 'f') ofToggleFullscreen();
	if (key == 'd') {
		if (rects.size() > 0) {
			rects.pop_front();
		}
	}
	if (key == 'e') {
		if (rects.size() > 0) {
			rects.pop_back();
		}
	}
}

void testApp::keyReleased(int key) {
}

void testApp::mouseMoved(int x, int y ) {
	
}

void testApp::mouseDragged(int x, int y, int button) {

}

void testApp::mousePressed(int x, int y, int button) {
    bDrawRect = true;
    drawPos.x = x;
    drawPos.y = y;
}

void testApp::mouseReleased(int x, int y, int button) {
    bDrawRect = false;
    int zone = (ofGetHeight() - drawPos.y)/(ofGetHeight()/9);
    float thisFreq = 20 * pow(2.0, zone) * pitchRatio[int(ofRandom(0, 6))];
    if (thisFreq > 18000) {
        thisFreq = 18000;
    }
    MyRect *r = new MyRect(drawPos, 
                           mouseX - drawPos.x, 
                           mouseY - drawPos.y, 
                           ofRandom(1.0, 2.0),
                           thisFreq,
                           ofRandom(-1, 1),
                           (mouseY - drawPos.y)/1000.0
                           );
    rects.push_back(r);
}

void testApp::resized(int w, int h){

}

