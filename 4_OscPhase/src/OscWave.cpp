//
//  OscWave.cpp
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/05.
//
//

#include "OscWave.h"

OscWave::OscWave(int _index, float _freq, float _pan, float _lfo, float _amp, float _alpha)
{
    index = _index;
    freq = _freq;
    pan = _pan;
    lfo = _lfo;
    amp = _amp;
    alpha = _alpha;
    
    lineWidth = 2;
    
    synth = new ofxSCSynth("simple_sine");
    synth->create();
    synth->set("gate", 1);
    synth->set("freq", freq);
	synth->set("lfoFreq",lfo);
    synth->set("pan", pan);
	synth->set("amp", amp);
    
    /*
     int w = 1024;
     int h = 768;
     
     oscImage.allocate(w, h, OF_IMAGE_GRAYSCALE);
     pixels = oscImage.getPixels();
     
     for (int i = 0; i < w * h; i++){
     pixels[i] = 0;
     }
     oscImage.update();
     */
}

void OscWave::update()
{
    /*
     float lfoLevel = 0.5 + sin(ofGetElapsedTimef() * lfo) * 0.5;
     for (int j = 0; j < oscImage.height; j++) {
     float level = 0.5 + sin(freq * j / float(ofGetHeight()) + ofGetElapsedTimef() * pan) * 0.5 * lfoLevel;
     int col = level * alpha;
     for (int i = 0; i < oscImage.width; i++) {
     pixels[j * oscImage.width + i] = col;
     }
     }
     oscImage.update();
     */
}

void OscWave::draw()
{
    /*
     switch (index % 3) {
     case 0:
     ofSetHexColor(0xff0000);
     break;
     case 1:
     ofSetHexColor(0x00ff00);
     break;
     case 2:
     default:
     ofSetHexColor(0x0000ff);
     break;
     }
     oscImage.draw(0, 0, ofGetWidth(), ofGetHeight());
     */
    
    ofSetLineWidth(lineWidth);
    
    float level;
    for (int i = 0; i < ofGetWidth(); i += lineWidth) {
        float lfoLevel = 0.5f * (sin(ofGetElapsedTimef() * lfo * PI * 2.0f) + 1.0f);
        float level = 0.5f * (sin(freq * i / ofGetWidth() / 8.0 + ofGetElapsedTimef() * pan * 10.0f) + 1.0f) * lfoLevel;
        int col = level * alpha;
        switch (index % 3) {
            case 0:
                ofSetColor(col, 0, 0);
                break;
            case 1:
                ofSetColor(0, col, 0);
                break;
            case 2:
            default:
                ofSetColor(0, 0, col);
                break;
        }
        ofLine(i, 0, i, ofGetHeight());
    }
    
    ofSetLineWidth(1);
}