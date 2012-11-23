#ifndef _MY_ROTATER
#define _MY_ROTATER

#include "ofMain.h"
#include "ofxSuperCollider.h"

class MyRotater {
private:
    ofPoint pos;
    float width;
    float height;
    float scanSpeed;
    float scanPos;
    
    float freq;
    float pan;
    float amp;
    
    
public:
    MyRotater(ofPoint pos = ofPoint(ofGetWidth()/2, ofGetHeight()/2), 
           float width = 100.0, 
           float height=100.0, 
           float scanSpeed=5.0,
           float freq = 100.0,
           float pan = 0,
           float amp = 0.1
           );
    void update();
    void draw();    
    
    ofxSCSynth * perc;
};

#endif