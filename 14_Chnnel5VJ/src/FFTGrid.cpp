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
    col = 8;
}

void FFTGrid::update(){
    audio_input = ((testApp*)ofGetAppPtr())->audio_input;
}

void FFTGrid::draw(){
    int h = 1;
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
            if (br > 200) {
                br = 200;
            }
            ofSetColor(ofColor::fromHsb(hue, 150, br));
            //ofSetColor(br);
            ofRect(1024/col * j, i * h, 1024/col, h);
        }
    }
}

void FFTGrid::keyPressed(int key){
    if (key == 'a') {
        col *= 2;
    }
    if (key == 's') {
        col /= 2;
        if (col < 2) {
            col = 2;
        }
    }
}