//
//  SawSynth.h
//  ofxSuperColliderTest
//
//  Created by Atsushi Tadokoro on 2012/10/03.
//
//


#pragma once

#include "ofMain.h"
#include "ofxSuperCollider.h"

class SawSynth {
public:
    SawSynth(int n);
    ~SawSynth();
    void update();
    void draw();
    void clear();
    
    ofxSCSynth *synth;
    int nth;
    float freq;
    float detune;
    float alpha;
    float startTime;
    float phase;
    float height;
    bool death;
	float alphaMax;
};
