#include "CustomRect.h"

CustomRect::CustomRect(int _num) {
	num = _num;
	//音程の配列を生成
	float notes[] = {1.0, 5.0/4.0, 4.0/3.0, 3.0/2.0};
	float base[] = {1.0, 2.0, 4.0, 6.0, 8.0, 16.0};
	lfo = ofRandom(0.01, 4.0);
	
	amp = 0;
	
	//音程を決める
	num = num % 100;
	soundSpeed = notes[num%4] * base[num%6] * pow(1.5, 1.0+int(num/16.0));
	synth = new ofxSCSynth("simple_sine");
	synth->set("freq", soundSpeed * 30);
	synth->set("lfoFreq", lfo);
	synth->set("amp", 0);
	synth->create();
}

CustomRect::~CustomRect() {
	//synth->free();
}

void CustomRect::update() {
	radius = sin(ofGetElapsedTimef() * lfo * 10.0) * 10 + 30;
	
	ofVec2f pos = getPosition();
	float dist = pos.distance(center);
	amp = (1.0 - dist/400.0)*0.2;
	if (amp < 0) {
		amp = 0;
	}
	synth->set("amp", amp);
	
	float pan = (pos.x / (float)ofGetWidth()) *2.0 - 1.0;
	synth->set("pan", pan);
}