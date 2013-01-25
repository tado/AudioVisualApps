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
    magnitude = new float[fft_size];
    rot = new float[fft_size];
    vec = new float[fft_size];

    /*
    stiffness = 0.8;
    damping = 0.9;
    mass = 4.0;
     */

    stiffness = 0.1;
    damping = 0.5;
    mass = 80.0;


    for (int i = 0; i < fft_size; i++) {
        rot[i] = 0;
        vec[i] = 0;
    }
}

void FFTColor::update(){
    magnitudeHigh = 0;
    magnitudeMid = 0;
    magnitudeLow = 0;
}

void FFTColor::draw(){

	for (int i = 0; i < fft_size/3; i++) {
        magnitudeLow += powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.25);
	}
    for (int i = fft_size/3; i < fft_size/3 * 2; i++) {
        magnitudeMid += powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.25);
    }
    for (int i = fft_size/3 * 2; i < fft_size; i++) {
        magnitudeHigh += powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.25);
    }
    
    float scale = 0.2;
    
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    for (int j = 0; j < ofGetHeight(); j += 40) {
        for (int i = 0; i < ofGetWidth(); i += 40) {
            ofPushMatrix();
            ofTranslate(i, j, 0);
            float add = (((testApp*)ofGetAppPtr())->avg_power);
            float force = stiffness * -rot[i] + add;
            float acceleration = force / mass;
            vec[i] = damping * (vec[i] + acceleration);
            rot[i] += vec[i];
            //ofRotateX(rot[i]);
            ofRotateX(rot[i] + i * 0.15);
            ofRotateY(rot[i]*1.5 + j * 0.15);
            //ofRotateY(rot[i]*(0.2 + i / 500.0));
            //ofRotateZ(rot[j]*(0.3 + j / 500.0));
            ofSetColor(magnitudeLow * scale, magnitudeMid * scale, magnitudeHigh * scale);
            ofBox(0, 0, 0, 30 + add * 0.8);
            if (add > 0) {
                ofNoFill();
                ofEnableSmoothing();
                ofSetLineWidth(2);
                ofSetColor(127, 127, 127);
                ofBox(0, 0, 0, 30 + add * 0.8);
                ofFill();
                ofSetLineWidth(1);
                ofDisableSmoothing();
            }
            ofPopMatrix();
        }
    }
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}