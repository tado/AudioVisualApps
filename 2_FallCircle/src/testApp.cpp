#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofxSuperColliderServer::init();
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackgroundHex(0x000000);
	ofSetCircleResolution(64);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 8.0);
	box2d.setFPS(30.0);
	box2d.createBounds();
	box2d.registerGrabbing();
	
	// register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
	
	reverb = new ofxSCSynth("fall_fx");
    reverb->create();
	
	mouseDowned = false;
}

void testApp::exit() {
	reverb->free();
}

void testApp::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		float pan = (e.b->GetBody()->GetPosition().x * OFX_BOX2D_SCALE / ofGetWidth() * 2.0 - 1.0);
		float mass2 = e.b->GetBody()->GetMass();
		float freq = log(12.0/mass2)*1000.0;
		if(freq < 120){
			freq = 120;
		}
		float decay = mass2*0.2;
		if (decay>1.0) {
			decay = 1.0;
		}
		float amp = 0.05;
		
		perc = new ofxSCSynth("fall_perc");
		perc->set("amp", amp);
		perc->set("freq", freq);
		perc->set("decay", decay);
		perc->set("pan", pan);
		perc->create();
	}
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {

}



//--------------------------------------------------------------
void testApp::update() {
	
	box2d.update();	

}


//--------------------------------------------------------------
void testApp::draw() {
	//circlesに格納された全ての図形を描画
	ofEnableSmoothing();
    for(int i=0; i<circles.size(); i++) {
		ofSetHexColor(0x3399ff);
		ofNoFill();
		ofCircle(circles[i]->getPosition().x, circles[i]->getPosition().y, circles[i]->getRadius());
		ofFill();
		ofCircle(circles[i]->getPosition().x, circles[i]->getPosition().y, circles[i]->getRadius());
		if (circles[i]->getPosition().y > ofGetHeight()) {
			circles[i]->destroy();
		}
    }
	ofDisableSmoothing();
	
	/*
	if(drawing.size()==0) polyLine.draw();
	else drawing.draw();
	 */
	
	//円を描く際のガイド表示
    if (mouseDowned) {
        ofNoFill();
        ofSetLineWidth(1);
        ofSetHexColor(0xcc0000);
        ofCircle(mouseDownLoc.x, mouseDownLoc.y, ofDist(mouseDownLoc.x, mouseDownLoc.y, mouseX, mouseY));
        //ofLine(mouseX, mouseY, mouseDownLoc.x, mouseDownLoc.y);
    }
	
	string info = "";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	if(key == 'f'){
		ofToggleFullscreen();
	}
	if (key == 'c') {
		ofxBox2dCircle *c =new ofxBox2dCircle();
		c->setPhysics(1.5, 0.7, 1.0); //物理パラメータを設定
		c->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(0.5,20));
		circles.push_back(c); //生成した円をcirclesベクターに追加
		mouseDowned = false;
	}
	if (key == 'd') {
		if (circles.size() > 0) {
			circles[0]->destroy();
			circles.pop_front();
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
	//drawing.addVertex(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

    mouseDownLoc.set(x, y);
    mouseDowned = true;

	/*
	if(polyLine.isBody()) {
		drawing.clear();
		polyLine.destroy();
	}
	
	drawing.addVertex(x, y);
	 */
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	//マウスをクリックすると新規にパーティクルを追加
	ofVec2f mouse (x, y);
    float r = mouseDownLoc.distance(mouse);

    if (r<4.0) {
        r = 4.0+ofRandom(0.0, 12.0);
    }

    ofxBox2dCircle *c =new ofxBox2dCircle();
    c->setPhysics(1.5, 0.7, 1.0); //物理パラメータを設定
    c->setup(box2d.getWorld(), mouseDownLoc.x, mouseDownLoc.y, r); //マウスの位置に円を設定
    circles.push_back(c); //生成した円をcirclesベクターに追加
    mouseDowned = false;

	/*
	drawing.setClosed(false);
	drawing.simplify();
	
	polyLine.addVertexes(drawing);
	polyLine.simplify();
	polyLine.setPhysics(0.0, 0.5, 0.5);
	polyLine.create(box2d.getWorld());
	
	drawing.clear();
	 */
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

