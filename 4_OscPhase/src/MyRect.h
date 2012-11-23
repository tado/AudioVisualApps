#ifndef _MY_CIRCLE
#define _MY_CIRCLE

#include "ofMain.h"
#include "ofxSuperCollider.h"

class MyRect {
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
    MyRect(ofPoint pos = ofPoint(ofGetWidth()/2, ofGetHeight()/2), 
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