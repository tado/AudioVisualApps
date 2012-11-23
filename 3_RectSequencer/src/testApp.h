#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"
#include "ofxSuperColliderServer.h"
#include "MyRect.h"
#include "MyRotater.h"

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

	ofxSCSynth *reverb;
	bool bDrawRect;
    ofVec2f drawPos;
    deque <MyRect *> rects;
    float pitchRatio[7];
};

