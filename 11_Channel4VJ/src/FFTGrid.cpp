//
//  FFTGrid.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#include "FFTGrid.h"
#include "testApp.h"

FFTGrid::FFTGrid(){
    audio_input = new float[((testApp*)ofGetAppPtr())->buffer_size];
}

void FFTGrid::update(){
    audio_input = ((testApp*)ofGetAppPtr())->audio_input;
}

void FFTGrid::draw(){
    int h = 3;
    float col = 8.0;
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    int hue = int(((testApp*)ofGetAppPtr())->avg_power * 24) % 255;

    for (int j = 0; j < col; j++) {
        for (int i = 0; i < ofGetHeight(); i++) {
            float br = audio_input[j * (ofGetHeight() / h) + i] * 1024;
            if (br > 255) {
                br = 255;
            }
            ofSetColor(ofColor::fromHsb(hue, 255, br));
            ofRect(ofGetWidth()/col * j, i * h, ofGetWidth()/col, h);
        }
    }
}