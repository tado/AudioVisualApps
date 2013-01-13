//
//  FFTBox.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
#include "fft.h"

class FFTBox {
public:
    FFTBox();
    void update();
    void draw();
    
    // ばねのパラメータ
    float stiffness, damping, mass;
    //パーティクルの位置とスピード
    ofVec3f *pos, *vec;
    ofVec3f *rot, *vecRot;
    int fft_size;
};


