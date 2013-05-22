//
//  Fnwr.h
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#pragma once
#include "ofMain.h"
//#include "fft.h"

class Fnwr {
public:
    Fnwr();
    void update();
    void draw();
    ofImage fnwr;
    
    int fft_size;
    float avg_power;
};

