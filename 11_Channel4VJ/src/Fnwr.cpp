//
//  Fnwr.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/12/13.
//
//

#include "Fnwr.h"
#include "testApp.h"
Fnwr::Fnwr(){
    fnwr.loadImage("FNWR1500.png");
}

void Fnwr::draw(){
    int br = ((testApp*)ofGetAppPtr())->avg_power * 63 + 63;
    ofSetColor(br, br, br);
    ofRotateX(180);
    fnwr.draw(-fnwr.width/2, -fnwr.height/2, 200);
}