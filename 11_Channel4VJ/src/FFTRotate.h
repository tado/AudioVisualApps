//
//  FFTRotate.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
#include "fft.h"

class FFTRotate {
public:
    FFTRotate();
    void update();
    void draw();

	float *circle_phase;
	float *locOffsetX, *locOffsetY;
    float *magnitude;
    float *magnitude_average, *magnitude_average_snapshot;
    int fft_size;
    float circleSize;
};


