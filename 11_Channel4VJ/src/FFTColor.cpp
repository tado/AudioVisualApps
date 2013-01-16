//
//  FFTColor.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#include "FFTColor.h"
#include "testApp.h"

FFTColor::FFTColor(){
    fft_size = ((testApp*)ofGetAppPtr())->fft_size;
    magnitudeHigh = 0;
    magnitudeMid = 0;
    magnitudeLow = 0;
}

void FFTColor::update(){
    magnitudeHigh = 0;
    magnitudeMid = 0;
    magnitudeLow = 0;
}

void FFTColor::draw(){
	for (int i = 0; i < fft_size/3; i++) {
        magnitudeLow += powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.5);
	}
    for (int i = fft_size/3; i < fft_size/3 * 2; i++) {
        magnitudeMid += powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.5);
    }
    for (int i = fft_size/3 * 2; i < fft_size; i++) {
        magnitudeHigh += powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.5);
    }
    float scale = 0.3;
    ofSetColor(magnitudeLow * scale, 0, 0);
    ofRect(-ofGetWidth(), -ofGetHeight(), ofGetWidth()*2, ofGetHeight()*2);
    ofSetColor(0, magnitudeMid * scale, 0);
    ofRect(-ofGetWidth(), -ofGetHeight(), ofGetWidth()*2, ofGetHeight()*2);
    ofSetColor(0, 0, magnitudeHigh * scale);
    ofRect(-ofGetWidth(), -ofGetHeight(), ofGetWidth()*2, ofGetHeight()*2);
}