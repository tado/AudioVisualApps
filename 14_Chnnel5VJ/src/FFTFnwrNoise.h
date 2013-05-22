//
//  FFTFnwrNoise.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
//#include "fft.h"

class FFTFnwrNoise {
public:
    FFTFnwrNoise();
    void update();
    void draw();
    ofImage fnwr;
    float *magnitude;
    int fft_size;
    unsigned char *pixels;
};

