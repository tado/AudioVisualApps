#pragma once

#include "ofMain.h"
#include "ofxSuperColliderServer.h"
#include "OscGlsl.h"
#include "MyRect.h"
#include "GlitchRect.h"
#include "Flicker.h"
#include "SawSynth.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int mode;
    ofxSCSynth *fx1;
    ofxSCSynth *fx2;
    deque<OscGlsl *> oscils;
    ofShader oscShader;
    ofFbo oscFbo;
    float oscNum;
    float oscFreq[100];
    
    bool bMousePressed;
    ofVec2f drawPos;
    float pitchRatio[7];
    deque<MyRect *> rects;
    
    bool flickerMode;
    Flicker * flicker;
    
    bool glitchMode;
    GlitchRect * glitch;
    
    int synthNum;
    deque<SawSynth *> saws;
};
