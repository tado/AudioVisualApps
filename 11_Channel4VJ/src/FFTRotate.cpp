//
//  FFTRotate.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#include "FFTRotate.h"
#include "testApp.h"

FFTRotate::FFTRotate(){
    fft_size = ((testApp*)ofGetAppPtr())->fft_size;
    circle_phase = new float[fft_size];
}

void FFTRotate::update(){

}

void FFTRotate::draw(){
    //FFT変換の結果をもとに円を螺旋状に配置
	circleSize = ofGetHeight()/(float)fft_size/3;
    //ofPushMatrix();
	//ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < fft_size; i++){
        circle_phase[i] = ((testApp*)ofGetAppPtr())->magnitude[i];
        circle_phase[i] = powf(circle_phase[i], 0.25);
        
        float xx, yy;
        
        for (int j = 0; j < 6; j++) {
            ofSetColor((255-255*i/fft_size)/2,100*i/fft_size,255*i/fft_size);
            xx = cos(i/PI+circle_phase[i]/2.0) * i * circleSize;
            yy = sin(i/PI+circle_phase[i]/2.0) * i * circleSize;
            ofCircle(xx, yy, circle_phase[i]*6.0);
            ofRotateZ(180/6);
        }

    }
    //ofPopMatrix();
}