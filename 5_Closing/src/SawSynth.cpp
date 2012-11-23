#include "SawSynth.h"
#include "testApp.h"

SawSynth::SawSynth(int n){
    death = false;
    detune = ofRandom(-0.1, 0.1);
    nth = n;
    alpha = 0;
	alphaMax = 255;
    startTime = ofGetElapsedTimef();
    
    synth = new ofxSCSynth("mySaw");
    synth->set("gate", 1);
    synth->set("amp", 0.5);
    synth->set("rq", 1.0);
    synth->set("n", nth);
    synth->set("detune", detune);
    synth->create();
    
    freq = 20.0 * powf(1.5, nth);
    height = float(ofGetHeight()) / freq * 12.0;
}

SawSynth::~SawSynth() {
    synth->free();
}

void SawSynth::update(){
    if (!death) {
        alpha = (alphaMax/60.0 * (ofGetElapsedTimef() - startTime)) + 1;
		//alpha += 1;
        if (alpha > alphaMax) {
            alpha = alphaMax;
        }
    } else {
        alpha -= 1;
    }
    
    phase += detune * 10.0;
    if (phase > height) {
        phase -= height;
    }
    if (phase < height) {
        phase += height;
    }
}

void SawSynth::draw(){
    if (alpha > 0) {
        int n = ofGetWidth() / height + 1;
        ofSetColor(alpha);
        ofPushMatrix();
        ofTranslate(0, phase);
        ofSetLineWidth(2.0);
        for (int i = -1; i < n; i++) {
            ofLine(0, height * i, ofGetWidth(), height * i);
        }
        ofPopMatrix();
    } else {
        ((testApp*) ofGetAppPtr())->saws.pop_front();
    }
}

void SawSynth::clear(){
    
}