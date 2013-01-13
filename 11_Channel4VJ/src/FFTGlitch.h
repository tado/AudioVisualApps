//
//  FFTGlitch.h
//  Channel4VJ
//
//  Created by Atsushi Tadokoro on 1/14/13.
//
//
#pragma once

#include "ofMain.h"

class FFTGlitch {
public:
    FFTGlitch();
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
    int fft_size;
};
