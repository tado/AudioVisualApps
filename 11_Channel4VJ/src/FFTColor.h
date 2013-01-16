//
//  FFTColor.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
#include "fft.h"

class FFTColor {
public:
    FFTColor();
    void update();
    void draw();
    
    int fft_size;
    float magnitudeLow, magnitudeMid, magnitudeHigh;
};


