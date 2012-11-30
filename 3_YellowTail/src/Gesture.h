//
//  Gesture.h
//  emptyExample
//
//  Created by Tadokoro Atsushi on 2012/11/30.
//
//

#pragma once
#include "ofMain.h"

class Gesture {
public:

	Gesture();
	void addPoint(ofVec2f pos);
	void update();
	void draw();
	vector<ofVec2f> pos;
	ofVec2f jump;

};
