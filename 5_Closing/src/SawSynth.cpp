#include "SawSynth.h"
#include "testApp.h"

SawSynth::SawSynth(int n){
    death = false;
    detune = ofRandom(-0.1, 0.1);
    nth = n;
    alpha = 1;
    alphaMax = 127;
    //startTime = ofGetElapsedTimef();
    
    synth = new ofxSCSynth("mySaw");
    synth->set("gate", 1);
    synth->set("amp", 0.5);
    synth->set("rq", 1.0);
    synth->set("n", nth);
    synth->set("detune", detune);
    synth->create();
    
    freq = 20.0 * powf(1.5, nth);
    height = float(ofGetHeight()) / freq * 20.0;
    
    float direction;
    if (nth % 2 == 0) {
        direction = -1.0;
    } else {
        direction = 1.0;
    }
    detune = ofRandom(0.02, 0.04) * direction;
    ofSetLineWidth(4.0);
    //phase += detune * 10.0;
    deleteMode = 0;
}

SawSynth::~SawSynth() {
    synth->free();
}

void SawSynth::update(){
    if (!death) {
        //alpha = (alphaMax/60.0 * (ofGetElapsedTimef() - startTime)) + 1;
        //alpha += 0.04;
        alpha += 1.0;
        if (alpha > alphaMax) {
            alpha = alphaMax;
        }
    } else {
        alpha -= 1;
    }
    
    phase += detune * 10.0;
    if (phase > height) {
        phase  = 0;
    }
    if (phase < -height) {
        phase = 0;
    }
}

void SawSynth::draw(){
    if (alpha > 0) {
        int n = ofGetWidth() / height + 1;
        ofSetColor(alpha);
        ofPushMatrix();
        ofTranslate(0, phase);
        for (int i = -1; i < n + 1; i++) {
            ofLine(0, height * i, ofGetWidth(), height * i);
        }
        ofPopMatrix();
    } else {
        switch (deleteMode) {
            case 1:
                ((testApp*) ofGetAppPtr())->saws.pop_front();
                break;
            case 2:
                ((testApp*) ofGetAppPtr())->saws.pop_back();
            case 0:
            default:
                break;
        }
    }
}

void SawSynth::clear(){
    
}