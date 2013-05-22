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
    int h = 2;
    float col = 64;
    ofTranslate(-1024/2, -768/2);
    int hue = int(((testApp*)ofGetAppPtr())->avg_power * 20) % 255;

    /*
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < 768; i++) {
            float br = audio_input[j * (768 / h) + i] * 1024;
            if (br > 255) {
                br = 255;
            }
            ofSetColor(ofColor::fromHsb(hue, 127, br));
            //ofSetColor(br);
            ofRect(1024/col * j, i * h, 1024/col, h);
        }
    }
     */
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < 768; i++) {
            float br = audio_input[(j * (768 / h) + i) % 2048] * 1024;
            if (br > 180) {
                br = 180;
            }
            ofSetColor(ofColor::fromHsb(hue, 120, br));
            //ofSetColor(br);
            ofRect(1024/col * j, i * h, 1024/col, h);
        }
    }
}