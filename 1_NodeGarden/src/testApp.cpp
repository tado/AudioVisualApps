#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofxSuperColliderServer::init();
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackgroundHex(0x000000);
	ofSetCircleResolution(32);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);

	particleImage.loadImage("emitter.png");
	dacImage.loadImage("particle.png");
	
	reverb = new ofxSCSynth("fx");
    reverb->create();

	dac.setPhysics(100.0, 0.1, 0.2);
	dac.fixture.filter.groupIndex = -1;
	dac.setup(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2, 1, 1);
	//dac.set(ofGetWidth()/2, ofGetHeight()/2);
}

void testApp::exit() {
	for(int i=0; i<boxes.size(); i++) {
		boxes[i].synth->free();
	}
	reverb->free();
}

//--------------------------------------------------------------
void testApp::update() {
	
	box2d.update();	
	//ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);
	for(int i=0; i<boxes.size(); i++) {
		boxes[i].update();
		boxes[i].addAttractionPoint(dac.getPosition(), 0.005);
		//dac.addAttractionPoint(boxes[i].getPosition(), 0.00005);
		boxes[i].center = dac.getPosition();
		ofVec2f p1 (boxes[i].getPosition());
		for (int j = i + 1; j < boxes.size(); j++) {
			boxes[j].addAttractionPoint(p1, 0.00001);			
		}
	}
}


//--------------------------------------------------------------
void testApp::draw() {
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	for(int i=0; i<boxes.size(); i++) {
		ofVec2f p1 (boxes[i].getPosition());
		for (int j = i + 1; j < boxes.size(); j++) {
			ofVec2f p2 (boxes[j].getPosition());
			float dist = p2.distance(p1);
			if (dist < 150) {
				int col = (150 - dist);
				ofSetColor(255, 255, 255, col * 2.0);
				ofLine(p1.x, p1.y, p2.x, p2.y);
			}
		}
	}
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetHexColor(0xcccccc);
	for(int i=0; i<boxes.size(); i++) {
		float radius = boxes[i].radius;
		particleImage.draw(boxes[i].getPosition() - radius, radius * 2.0, radius * 2.0);
	}
	
	float allAmp = 0;
	for (int i = 0; i < boxes.size(); i++) {
		allAmp += boxes[i].amp * 12.0;
	}

	float dacRadius = sin(ofGetElapsedTimef() * 100.0) * allAmp + allAmp * 3.0 + 40;
	ofVec2f offset (dacRadius, dacRadius);
	ofSetHexColor(0xffffff);
	dacImage.draw(dac.getPosition() - offset, dacRadius * 2.0, dacRadius * 2.0);
	
	string info = "";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	if(key == 'f') ofToggleFullscreen();
	if (key == 'd') {
		if (boxes.size()>0) {
			boxes[0].synth->set("amp", 0);
			boxes[0].synth->free();
			boxes[0].destroy();
			boxes.pop_front();
		}
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	if (button == 2) {
		dac.setPosition(x, y);
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	if(button == 0) {
		float w = 2;
		float h = 2;
		CustomRect rect(boxes.size());
		rect.setPhysics(10.0, 0.1, 0.5);
		rect.fixture.filter.groupIndex = -1;
		rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
		boxes.push_back(rect);
	}
	
	if (button == 2) {
		dac.setPosition(x, y);
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

