#pragma once

#include "ofxBox2d.h"
#include "ofxSuperCollider.h"

class CustomRect : public ofxBox2dRect {
public:
	CustomRect(int _num);
	~CustomRect();
	void update();
	
	int num;
    float soundSpeed; //音の再生スピード(ピッチ)
    float lfo; //円の伸縮スピード
	float amp;
	float radius;
	ofVec2f center;
    ofxSCSynth	*synth;
};