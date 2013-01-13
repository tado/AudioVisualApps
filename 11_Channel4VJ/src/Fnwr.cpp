//
//  Fnwr.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/12/13.
//
//

#include "Fnwr.h"

Fnwr::Fnwr(){
    fnwr.loadImage("FNWR1500.png");
}

void Fnwr::draw(){
    ofSetColor(ofRandom(127,1024),ofRandom(127,1024),ofRandom(127,1024));
    ofRotateX(180);
    fnwr.draw(-fnwr.width/2, -fnwr.height/2, 200);
}