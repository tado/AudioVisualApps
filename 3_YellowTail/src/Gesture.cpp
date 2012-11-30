//
//  Gesture.cpp
//  emptyExample
//
//  Created by Tadokoro Atsushi on 2012/11/30.
//
//

#include "Gesture.h"

Gesture::Gesture() {
	jump.set(0, 0);
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
		
		/*
		if (pos[0].x < 0) {
			for (int i = 0; i < pos.size()-1; i++){
				pos[i].x += ofGetWidth();
			}
		}
		if (pos[0].y < 0) {
			for (int i = 0; i < pos.size()-1; i++){
				pos[i].y += ofGetHeight();
			}
		}
		if (pos[0].x > ofGetWidth()) {
			for (int i = 0; i < pos.size()-1; i++){
				pos[i].x -= ofGetWidth();
			}
		}
		if (pos[0].y > ofGetHeight()) {
			for (int i = 0; i < pos.size()-1; i++){
				pos[i].y -= ofGetHeight();
			}
		}
		 */
	}
}

void Gesture::draw(){
	ofNoFill();
	ofSetLineWidth(1);
	
	for (int i = 1; i < pos.size()-1; i++) {
		float dist = pos[i].distance(pos[i-1]);
		if (dist < ofGetHeight()/2) {
			//ofSetLineWidth(dist / 2.0f);
			ofLine(pos[i].x, pos[i].y ,pos[i-1].x, pos[i-1].y);
		}
	}
	
}

void Gesture::addPoint(ofVec2f _pos){
	pos.push_back(_pos);
	if (pos.size() > 0) {
		jump.x = _pos.x - pos[0].x;
		jump.y = _pos.y - pos[0].y;
	}
}