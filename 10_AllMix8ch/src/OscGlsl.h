//
//  OscGlsl.h
//  OscPhase
//
//  Created by Atsushi Tadokoro on 6/19/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSuperCollider.h"

class OscGlsl{
public:
    OscGlsl(int index, float freq, float pan = 0.0, float lfo = 1.0, float amp = 0.4, float alpha = 63);
    void update();
    void draw();
    
    ofxSCSynth *synth;
    float freq;
    float pan;
    float lfo;
    float amp;
    int alpha;
    int index;
    int lineWidth;    
};

