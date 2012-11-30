#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "particle.h"
#include "ofxSuperCollider.h"
#include "ofxSuperColliderServer.h"

class testApp : public ofSimpleApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void keyReleased (int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    vector <particle *> myParticles;
    const int num = 1000;
    bool pressed;
    ofxSCSynth *synth;
    bool ready;
};

#endif

