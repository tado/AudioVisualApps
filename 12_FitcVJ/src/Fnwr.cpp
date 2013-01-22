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
    
    ofPushMatrix();
    //ofRotateZ(sin(ofGetElapsedTimef() * 0.3) * 45);
    ofRotateZ(ofGetElapsedTimef() * 10);
    float scale = sin(ofGetElapsedTimef() * 0.1) * 0.5 + 1.5;
    ofScale(scale, scale);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetHexColor(0x77c7d2);
    ofRect(-ofGetWidth(), -ofGetHeight(), ofGetWidth()*2, ofGetHeight()*2);
    //int br = ((testApp*)ofGetAppPtr())->avg_power * 63 + 63;
    int br = 640;
    ofSetColor(br, br, br);
    ofRotateX(180);
    fnwr.draw(-fnwr.width/2, -fnwr.height/2, 200);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofPopMatrix();
}