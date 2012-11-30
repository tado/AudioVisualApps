#include "MyRotater.h"

MyRotater::MyRotater(ofPoint _pos, 
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

void MyRotater::update()
{
    scanPos += scanSpeed;
}

void MyRotater::draw()
{

}
