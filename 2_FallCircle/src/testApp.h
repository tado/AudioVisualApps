#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxSuperCollider.h"
#include "ofxSuperColliderServer.h"
//#include "CustomRect.h"

// -------------------------------------------------

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	// this is the function for contacts
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
	
	ofxBox2d box2d;
	deque <ofxBox2dCircle *> circles;
	ofxSCSynth *reverb;
	ofxSCSynth *perc;
	
	ofVec2f mouseDownLoc;
    bool mouseDowned;
};

