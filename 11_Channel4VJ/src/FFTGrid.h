//
//  FFTGrid.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
#include "fft.h"

class FFTGrid {
public:
    FFTGrid();
    void update();
    void draw();
    
    int fft_size;
    float *audio_input;
};