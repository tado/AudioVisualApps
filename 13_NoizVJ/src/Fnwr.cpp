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
    fnwr.loadImage("noiz_logo.png");
}

void Fnwr::update(){
    avg_power = ((testApp*)ofGetAppPtr())->avg_power;
}

void Fnwr::draw(){
    float strength = 4.0;
    
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    ofBackgroundGradient(ofColor::fromHsb(0, 200, avg_power*strength), ofColor::fromHex(0x000000));
    ofPopMatrix();

    int br = 700;
    int num = 48;
    
    float time = ofGetElapsedTimef() + 1200;

    for (int i = 1; i <= num; i++) {
        ofPushMatrix();
        ofRotateZ(time * i / float(num) * 12);
        ofRotateY(time * i / float(num) * 15);
        ofRotateX(time * i / float(num) * 17);
        float scale = (sin(time * 0.3 * i / float(num)) + 1.5) * 0.75;
        ofScale(scale, scale);
        ofSetColor(br, br, br, 255/float(num) * 2.0);
        ofRotateX(180);
        fnwr.draw(-fnwr.width/2, -fnwr.height/2, -150);
        ofPopMatrix();
    }
    ofSetColor(255, 255, 255, 200);
    ofScale(1.25, 1.25);
    ofRotateX(180);
    fnwr.draw(-fnwr.width/2, -fnwr.height/2);
}