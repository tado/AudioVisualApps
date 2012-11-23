//
//  Flicker.cpp
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/06.
//
//

#include "Flicker.h"

Flicker::Flicker(float _freq, float _level)
{
    freq = _freq;
    level = _level;
    
    //synth
    synth = new ofxSCSynth("sawbass");
    synth->set("amp", 1.0);
    synth->create();
}

void Flicker::update()
{
    if (level < 0) {
        level = 0;
    }
    float lpf = ofMap(level, 0.0, 1.0, 20, 1000);
    synth->set("lpf", lpf);
    
}

void Flicker::draw()
{
    ofSetColor(255 * level);
    int trig = int(ofGetElapsedTimef() * 1000) % int(freq * 1000);
    if (trig < int(freq * 500)) {
        ofRect(0, 0, ofGetWidth()/2, ofGetHeight());
    } else {
        ofRect(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
    }
}