//
//  GlitchRect.h
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/05.
//
//

#ifndef __OscPhase__GlitchRect__
#define __OscPhase__GlitchRect__

#include "ofMain.h"
#include "ofxSuperCollider.h"

class GlitchRect {
public:
    GlitchRect(ofPoint pos, float width = 100.0, float height=100.0);
    void update();
    void draw();
    
    string compressedFilename;
    ofImage clipImage;
    ofPoint pos;
    float width;
    float height;  
    ofImageQualityType quality;
	ofImage caputerImage;
    int index;
    float glitchStart;
    float scale;
    float coin;
    int tempo;
    float amp;
    
    ofxSCSynth * synth;
    
};

#endif /* defined(__OscPhase__GlitchRect__) */
