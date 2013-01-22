//
//  Gesture.cpp
//  emptyExample
//
//  Created by Tadokoro Atsushi on 2012/11/30.
//
//

#include "Gesture.h"

Gesture::Gesture() {
    length = 32;
	jump.set(0, 0);
    synth = new ofxSCSynth("yellow_sine");
    synth->set("amp", 0);
    synth->create();
}

void Gesture::update(){
	if (pos.size()>1) {
		for (int i = pos.size(); i > 0; i--) {
			pos[i].x = pos[i-1].x;
			pos[i].y = pos[i-1].y;
		}
		pos[0].x = pos[pos.size()-1].x - jump.x;
		pos[0].y = pos[pos.size()-1].y - jump.y;
		if (pos[0].x < 0) {
			pos[0].x += ofGetWidth();
		}
		if (pos[0].y < 0) {
			pos[0].y += ofGetHeight();
		}
		if (pos[0].x > ofGetWidth()) {
			pos[0].x -= ofGetWidth();
		}
		if (pos[0].y > ofGetHeight()) {
			pos[0].y -= ofGetHeight();
		}

        int freq = ofMap(pos[0].y, 0, ofGetHeight(), 2000, 800);
        float pan = ofMap(pos[0].x, 0, ofGetWidth(), -1.0, 1.0);
        synth->set("freq", freq);
        synth->set("pan", pan);
        synth->set("amp", 0.02);
    } else {
        
    }
}

void Gesture::draw(){
    if (pos.size()>1) {        
        for (int i = 1; i < pos.size(); i++) {
            float dist = pos[i].distance(pos[i-1]);
            if (pos[i].distance(pos[i-1]) < ofGetHeight()/2) {
                ofLine(pos[i].x, pos[i].y ,pos[i-1].x, pos[i-1].y);
            }
        }
    }
}

void Gesture::addPoint(ofVec2f _pos){
    pos.push_back(_pos);
    if (pos.size() > 1) {
        jump.x = _pos.x - pos[0].x;
        jump.y = _pos.y - pos[0].y;
    }
}