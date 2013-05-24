//
//  FFTSinewave.cpp
//  Chnnel5VJ
//
//  Created by Atsushi Tadokoro on 5/24/13.
//
//

#include "FFTSinewave.h"
#include "testApp.h"

FFTSinewave::FFTSinewave(){
    fft_size = ((testApp*)ofGetAppPtr())->fft_size;
    magnitude = new float[fft_size];
    col = 32;
}

void FFTSinewave::update(){
    for (int i = 0; i < fft_size; i++) {
        magnitude[i] = powf(((testApp*)ofGetAppPtr())->magnitude[i], 1.2);
    }
}

void FFTSinewave::draw(){
    
}