//
//  FFTCircle.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#include "FFTCircle.h"
#include "testApp.h"

FFTCircle::FFTCircle(){
    fft_size = ((testApp*)ofGetAppPtr())->fft_size;
    magnitude = new float[fft_size];
}

void FFTCircle::update(){
    for (int i = 0; i < fft_size; i++) {
        magnitude[i] = powf(((testApp*)ofGetAppPtr())->magnitude[i], 1.2);
    }
}

void FFTCircle::draw(){
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    float w = (float)ofGetWidth()/ (float)fft_size / 2.0f;
    for (int i = 0; i < fft_size; i++) {
        
        ofColor col;
        float br =  magnitude[i]*24;
        if (br > 160) {
            br = 160;
        }
        
        col.setHsb(i * 255.0f / (float)fft_size, 127, 255,br);
        ofSetColor(col);
        ofRect(ofGetWidth()/2 - w * i, 0, w, ofGetHeight());
        ofRect(ofGetWidth()/2 + w * i, 0, w, ofGetHeight());
        
        ofRect(0, ofGetHeight()/2-w * i, ofGetWidth(), w);
        ofRect(0, ofGetHeight()/2+w * i, ofGetWidth(), w);
    }
    ofPopMatrix();
}