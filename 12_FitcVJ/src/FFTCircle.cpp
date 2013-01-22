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

}

void FFTCircle::draw(){
    float w = (float)ofGetWidth()/ (float)fft_size / 2.0f * 0.5;
	for (int i = 0; i < fft_size; i+=15) {
        magnitude[i] = powf(((testApp*)ofGetAppPtr())->magnitude[i], 0.5);
		
		//塗りのアルファ値でFFT解析結果を表現
		ofSetColor(ofColor::fromHsb(220 * i / fft_size, 255, 63));
        
		ofCircle(-w * i, 0, magnitude[i]*60); //左
		ofCircle(w * i, 0, magnitude[i]*60); //右
	}
}