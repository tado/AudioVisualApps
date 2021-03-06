//
//  OscWave.h
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/05.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSuperCollider.h"

class OscWave {
public:
    
    OscWave(int index, float freq, float pan = 0.0, float lfo = 1.0, float amp = 0.4, float alpha = 63);
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
