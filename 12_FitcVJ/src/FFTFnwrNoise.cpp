//
//  FFTFnwrNoise.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/12/13.
//
//

#include "FFTFnwrNoise.h"
#include "testApp.h"

FFTFnwrNoise::FFTFnwrNoise(){
    fnwr.loadImage("FITC_logo.jpg");
    fft_size = ((testApp*)ofGetAppPtr())->fft_size;
    magnitude = new float[fft_size];
    pixels = fnwr.getPixels();
}

void FFTFnwrNoise::update(){
    for (int i = 0; i < fft_size; i++) {
        magnitude[i] = powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.1);
    }
}

void FFTFnwrNoise::draw(){   
    float br = 2.5;
    float pow = powf(((testApp*)ofGetAppPtr())->avg_power, 0.9) * 10.0;
    int skip = pow/4.0 + 2;
    ofRotateX(180);
    //ofScale(pow/100+1.2,pow/100+1.2);
    ofScale(1.2,1.2);
    ofTranslate(-fnwr.width/2, -fnwr.height/2);

    //ofSetRectMode(OF_RECTMODE_CENTER);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    for (int i = 0; i < fnwr.width; i+=skip) {
        for (int j = 0; j < fnwr.height; j+=skip) {
            int r = pixels[j * fnwr.width * 3 + i * 3] * br;
            int g = pixels[j * fnwr.width * 3 + i * 3 + 1]* br;
            int b = pixels[j * fnwr.width * 3 + i * 3 + 2]* br;
            
            ofSetColor(r, 0, 0);
            ofRect(i, int(j - magnitude[i] * pow / 4.0), skip, skip);
            ofSetColor(0, g, 0);
            ofRect(i, j, skip, skip);
            ofSetColor(0, 0, b);
            ofRect(i, int(j + magnitude[fft_size - i] * pow / 4.0), skip, skip);
        }
    }
    //ofSetRectMode(OF_RECTMODE_CORNER);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDisableLighting();
    ofSetColor(120,120,120,255-pow*3);
    fnwr.draw(0, 0);
    ofEnableLighting();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}