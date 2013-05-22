//
//  FFTFnwrGlitch.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"

class FFTFnwrGlitch {
public:
    static const unsigned int WIDTH  = 500;
    static const unsigned int HEIGHT  = 500;
    static const unsigned int NUM_PARTICLES  = WIDTH * HEIGHT;
    
    FFTFnwrGlitch();
    void update();
    void draw();
    void keyPressed(int key);
    void resetCam();
    ofVec3f interpolateByPct(float _pct, float _shaper);
    
    ofImage fnwr;
    ofVbo myVbo;
    ofVec3f myVerts[NUM_PARTICLES];
	ofFloatColor myColor[NUM_PARTICLES];
    float vec[NUM_PARTICLES];
    unsigned char *pixels;
    int zMax;
    float stiffness, damping, mass;
    ofVec3f camStart, camEnd, camCurrent;
    float camPct;
};

