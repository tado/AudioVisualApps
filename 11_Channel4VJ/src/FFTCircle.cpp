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
}

void FFTCircle::update(){

}

void FFTCircle::draw(){
    float w = (float)ofGetWidth()/ (float)fft_size / 2.0f;
	for (int i = 0; i < fft_size; i++) {
		
		//塗りのアルファ値でFFT解析結果を表現
		ofSetColor(ofColor::fromHsb(255 * i / fft_size, 255, 10));
        
		ofCircle(-w * i, 0, ((testApp*)ofGetAppPtr())->magnitude[i] * 10.0); //左
		ofCircle(w * i, 0, ((testApp*)ofGetAppPtr())->magnitude[i] * 10.0); //右
	}
}