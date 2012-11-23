#include "MyRect.h"

MyRect::MyRect(ofPoint _pos, 
               float _width, 
               float _height, 
               float _scanSpeed, 
               float _freq, 
               float _pan,
               float _amp)
{
    pos = _pos;
    width = _width;
    height = _height;
    scanSpeed = _scanSpeed;
    freq = _freq;
    pan = _pan;
    amp  = _amp;
    
    scanPos = 0;
    
    perc = new ofxSCSynth("mySaw");
    perc->set("amp", amp);
    perc->set("freq", freq);
    perc->set("decay", width/scanSpeed/60.0);
    perc->set("pan", pan);
    perc->create();
}

void MyRect::update()
{
    scanPos += scanSpeed;
    if (scanPos > width) {
        scanPos -= width;
        
        perc = new ofxSCSynth("mySaw");
        perc->set("amp", amp);
        perc->set("freq", freq);
        perc->set("decay", width/scanSpeed/60.0);
        perc->set("pan", pan);
        perc->create();
    }
}

void MyRect::draw()
{
    ofFill();
    float a = 255 - scanPos/width*255.0;
    ofSetColor(32, 127, 255, a);
    ofRect(pos.x, pos.y, scanPos, height);
    
    /*
    ofNoFill();
    ofSetColor(63, 63, 63);
    ofRect(pos.x, pos.y, width, height);
     */
}

