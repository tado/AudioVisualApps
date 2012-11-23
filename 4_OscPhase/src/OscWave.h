//
//  OscWave.h
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/05.
//
//

#ifndef __OscPhase__OscWave__
#define __OscPhase__OscWave__

#include "ofMain.h"
#include "ofxSuperCollider.h"

class OscWave {
public:
    
    OscWave(int index, float freq, float pan = 0.0, float lfo = 1.0, float amp = 0.4, float alpha = 63);
    void update();
    void draw();
    
    ofxSCSynth *synth;
    ofImage oscImage;
    unsigned char * pixels;
    float freq;
    float pan;
    float lfo;
    float amp;
    int alpha;
    int index;
    int lineWidth;
};

#endif /* defined(__OscPhase__OscWave__) */
