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
    col = 80;
    avarage = new float[int(col)];
}

void FFTSinewave::update(){

    for (int i = 0; i < fft_size; i++) {
        magnitude[i] = powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.7)*3.0;
    }
    /*
    for (int j = 0; j < col; j++) {
        avarage[j] = 0;
        for (int i = 0; i < fft_size/4/col; i++) {
            avarage[j] += powf(((testApp*)ofGetAppPtr())->magnitude[j * int(col) + i], 1.5) * ofGetWidth()/2/col;
        }
    }
     */
}

void FFTSinewave::draw(){
    ofPushMatrix();
    ofEnableSmoothing();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    ofSetColor(255);
    int step = fft_size/col;
    for (int i = 1; i < fft_size; i += step) {
        float center = ofGetWidth()/2 + i;
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, 0);
        /*
        for (int j = 0; j < ofGetHeight(); j += 4) {
            ofPoint pos = ofPoint(sin(j/10.0*i + ofGetElapsedTimef()*10*i) * magnitude[i] + i/2, j);
            ofCircle(pos.x, pos.y, 1);
            ofCircle(-pos.x, pos.y, 1);
        }
         */
        ofSetLineWidth(2);
        ofNoFill();
        ofBeginShape();
        for (int j = 0; j < ofGetHeight(); j++) {
            ofPoint pos = ofPoint(sin((j+ofGetElapsedTimef()*(i + 100))/800.0*powf(i,0.5)) * magnitude[i] + i/2, j);
            ofVertex(pos.x, pos.y);
        }
        ofEndShape();
        ofBeginShape();
        for (int j = 0; j < ofGetHeight(); j++) {
            ofPoint pos = ofPoint(sin((j-ofGetElapsedTimef()*(i + 100))/800.0*powf(i,0.5)) * magnitude[i] + i/2, j);
            ofVertex(-pos.x, pos.y);
        }
        ofEndShape();
        ofFill();
        ofPopMatrix();
    }
    ofDisableSmoothing();
    ofPopMatrix();
}