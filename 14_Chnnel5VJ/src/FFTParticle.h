//
//  FFTParticle.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
#include "fft.h"

class FFTParticle {
public:
    static const unsigned NUM_BILLBOARDS = 2048;
    
    FFTParticle();
    void update();
    void draw();
    void reset();
	int fft_size;
	
	fft myfft; //FFTクラスのインスタンス
    
    ofImage texture; // パーティクルに貼るテクスチャイメージ
	ofVbo billboardVbo; // VBO
	ofVec3f billboardVerts[NUM_BILLBOARDS]; // 頂点座標情報
	ofFloatColor billboardColor[NUM_BILLBOARDS]; //頂点色情報
	ofVec3f billboardVels[NUM_BILLBOARDS]; // パーティクルの移動速度
    float *magnitude;
    float stiffness, damping, mass;
};


