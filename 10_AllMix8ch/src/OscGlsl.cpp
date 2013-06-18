//
//  OscGlsl.cpp
//  OscPhase
//
//  Created by Atsushi Tadokoro on 6/19/13.
//
//

#include "OscGlsl.h"
#include "testApp.h"

OscGlsl::OscGlsl(int _index, float _freq, float _pan, float _lfo, float _amp, float _alpha){
    index = _index;
    freq = _freq;
    pan = _pan;
    lfo = _lfo;
    amp = _amp;
    alpha = _alpha;
    
    lineWidth = 2;
    
    synth = new ofxSCSynth("col_sine");
    synth->create();
    synth->set("gate", 1);
    synth->set("freq", freq);
	synth->set("lfoFreq",lfo);
    synth->set("pan", pan);
	synth->set("amp", amp);
    
    ((testApp*)ofGetAppPtr())->oscNum += 1.0;
}

void OscGlsl::update(){
    
}

void OscGlsl::draw(){
    
}