#include "testApp.h"
#include "particle.h"
#include "ofMain.h"

// comparison routine for sort...
bool comparisonFunction(  particle * a, particle * b ) {
    return a->pos.x < b->pos.x;
}


//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    
    /*
     for (int i = 0; i < num; i++){
     particle * p = new particle();
     myParticles.push_back(p);
     myParticles[i]->pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
     myParticles[i]->vel.set(0,0);
     }
     */
    
    ofSetCircleResolution(32);
    ofSetRectMode(OF_RECTMODE_CENTER);
    pressed = false;
}

//--------------------------------------------------------------
void testApp::update(){
    /*
     if (myParticles.size() < num) {
     for (int i = 0; i < 10; i++) {
     particle * p = new particle();
     myParticles.push_back(p);
     myParticles[myParticles.size()-1]->pos.set(ofGetWidth()/2 + ofRandom(-20, 20), ofGetHeight()/2+ ofRandom(-20, 20));
     //myParticles[myParticles.size()-1]->pos.set(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
     myParticles[myParticles.size()-1]->vel.set(0,0);
     }
     }
     */
    
    //cout << ofGetFrameRate() << endl;
    
    // sort all the particle
    sort( myParticles.begin(), myParticles.end(), comparisonFunction );               // sort them!
    
    //ofBackground(0,0,0); //Grey background, NY style
    
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->resetForce();
    }
    
    
    for (int i = 0; i < myParticles.size(); i++){
        for (int j = i-1; j >= 0; j--){
            if ( fabs(myParticles[j]->pos.x - myParticles[i]->pos.x) >  40) break;
            myParticles[i]->addRepulsionForce( *myParticles[j], 40, 1.5f);
        }
    }
    
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), 0.4f);
        if (pressed) {
            myParticles[i]->addRepulsionForce( mouseX,mouseY, 200, 2.0);
        }
        myParticles[i]->addDampingForce();
        myParticles[i]->update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255,255,255);
    // then draw:
    
    for (int i = 0; i < myParticles.size(); i++){
        myParticles[i]->draw();
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == 'r') {
        myParticles.clear();
        for (int i = 0; i < num; i++){
            particle * p = new particle();
            //p->pos.set(ofGetWidth()/2 + ofRandom(-200, 200), ofGetHeight()/2+ ofRandom(-200, 200));
            p->pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
            p->vel.set(0,0);
            myParticles.push_back(p);
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    pressed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
    pressed = false;
}
