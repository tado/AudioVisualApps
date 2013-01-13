//
//  FFTBox.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/5/13.
//
//

#include "FFTBox.h"
#include "testApp.h"

FFTBox::FFTBox(){
    fft_size = ((testApp*)ofGetAppPtr())->fft_size;

    pos = new ofVec3f[fft_size];
    vec = new ofVec3f[fft_size];
    rot = new ofVec3f[fft_size];
    vecRot = new ofVec3f[fft_size];
    
    for (int i = 0; i < fft_size; i++) {
        rot[i] = ofVec3f(ofRandom(90), ofRandom(90), ofRandom(90));
        vecRot[i] = ofVec3f(ofRandom(-1, 1),ofRandom(-1, 1),ofRandom(-1, 1));
    }
    
    //ばねパラメータ
    stiffness = 2.0;
    damping = 0.4;
    mass = 20.0;
}

void FFTBox::update(){

}

void FFTBox::draw(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(31, 127, 255);
    for (int i = 0; i < fft_size; i++){
        //ばねの運動を計算
        float addFroce = ((testApp*)ofGetAppPtr())->magnitude[i] *20.0;
        float direction = ofRandom(360);
        float addX = cos(direction) * addFroce;
        float addY = sin(direction) * addFroce;
        float addZ = addFroce * 0.2;
        float forceX = stiffness * -pos[i].x + addX;
        float accelerationX = forceX / mass;
        vec[i].x = damping * (vec[i].x + accelerationX);
        float forceY = stiffness * -pos[i].y + addY;
        float accelerationY = forceY / mass;
        vec[i].y = damping * (vec[i].y + accelerationY);
        float forceZ = stiffness * -pos[i].z + addZ;
        float accelerationZ = forceZ / mass;
        vec[i].z = damping * (vec[i].z + accelerationZ);
        pos[i] += vec[i];
        // パーティクル描画
        float r = ((testApp*)ofGetAppPtr())->magnitude[i] * i / 12.0;
        //float r = 100;
        ofSetColor(ofColor::fromHsb(255 * i / fft_size, 255, 80));
        ofPushMatrix();
        ofTranslate(pos[i].x, pos[i].y, pos[i].z);
        ofRotateX(rot[i].x);
        ofRotateY(rot[i].y);
        ofRotateZ(rot[i].z);
        rot[i] += vecRot[i];
        ofBox(0, 0, 0, r);
        ofPopMatrix();
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //ofEnableBlendMode(OF_BLENDMODE_ADD);

}