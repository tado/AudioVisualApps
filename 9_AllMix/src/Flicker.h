//
//  Flicker.h
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/06.
//
//

#ifndef __OscPhase__Flicker__
#define __OscPhase__Flicker__

#include <iostream>
#include "ofMain.h"
#include "ofxSuperCollider.h"

class Flicker {
public:
    Flicker(float freq = 0.7, float level = 0.0);
    void update();
    void draw();
    
    float freq;
    float level;
    
    ofxSCSynth * synth;
};

#endif /* defined(__OscPhase__Flicker__) */
