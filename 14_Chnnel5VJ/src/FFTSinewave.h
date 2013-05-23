//
//  FFTSinewave.h
//  Chnnel5VJ
//
//  Created by Atsushi Tadokoro on 5/24/13.
//
//

#pragma once
#include "ofMain.h"
#include "fft.h"

class FFTSinewave {
public:
    FFTSinewave();
    void update();
    void draw();
    void keyPressed(int key);
    
    int fft_size;
    float *audio_input;
    float col;
};
