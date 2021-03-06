#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	// 画面設定
	ofBackgroundHex(0x000000);
	//glEnable(GL_DEPTH_TEST);
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// カメラ設定
	zoomTarget = zoom = 2000;
	cam.setDistance(zoom);
	
	// 頂点情報の初期化
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		
		// 移動速度
		billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
		
		// 初期位置
		billboardVerts[i].set(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
		
		// 色
		billboardColor[i].set(1, 1, 1, 0.7);
	}
	
	// VBOにパーティクルの色と座標を格納
	billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	
	// テクスチャー画像を設定
	ofDisableArbTex();
	
	// カメラキャプチャー初期化
	// myVideo.initGrabber(32, 28);
}

//--------------------------------------------------------------
void testApp::update() {
	/*
	// カメラ映像を更新
	myVideo.update();
	
	// もしカメラのフレームが更新されていたら
	if (myVideo.isFrameNew()) {
		
		// カメラの画像をキャプチャーし、テクスチャに設定
		texture.setFromPixels(myVideo.getPixels(), 
													myVideo.width, 
													myVideo.height, OF_IMAGE_COLOR);
	}
     */
	
    texture.loadImage("particle.png");
    
	// パーティクルの座標を更新
	float t   = (ofGetElapsedTimef()) * 0.9f;
	float div = 250.0;
	
	for (int i=0; i<NUM_BILLBOARDS; i++) {
		
		// ノイズを生成し移動速度に
		ofVec3f vec(ofSignedNoise(t, billboardVerts[i].y/div, billboardVerts[i].z/div),
								ofSignedNoise(billboardVerts[i].x/div, t, billboardVerts[i].z/div),
								ofSignedNoise(billboardVerts[i].x/div, billboardVerts[i].y/div, t));
		
		vec *= 0.3f;
		
		// 速度をもとにパーティクル位置を更新
		billboardVels[i] += vec;
		billboardVerts[i] += billboardVels[i];	
		billboardVels[i]  *= 0.94f;	
	}
	
	// VBOの頂点と色の情報を更新
	billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
	
	// カメラのズーム設定
	zoom += (zoomTarget - zoom) * 0.01;
	cam.setDistance(zoom);	
}

//--------------------------------------------------------------
void testApp::draw() {
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
	cam.begin();
	
	// パーティクル描画設定
	glDepthMask(GL_FALSE);
	ofEnablePointSprites();
	texture.getTextureReference().bind();
	
	// パーティクルのZ軸の位置によって大きさを変化させる
	static GLfloat distance[] = { 0.0, 0.0, 1.0 }; 
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
	glPointSize(20000);
	
	// パーティクルを描画
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	billboardVbo.draw(GL_POINTS, 0, NUM_BILLBOARDS);
	texture.getTextureReference().unbind();
	ofDisablePointSprites();
	glDepthMask(GL_TRUE);
	
	cam.end();
	ofPopMatrix();
	
	// ログを表示
	ofSetColor(255, 255, 255);
	string info = ofToString(ofGetFrameRate(), 2)+", ";
	info += "Particle Count: "+ofToString(NUM_BILLBOARDS)+"\n";
    info += "zoom: arrow_up, arrow_down";
	ofDrawBitmapString(info, 10, 20);
}

void testApp::keyPressed(int key){
	
	// fキーでフルスクリーン表示
	if(key == 'f') ofToggleFullscreen();
	
	// 上矢印キーで拡大
	if(key == OF_KEY_UP) 	zoomTarget -=10;
	
	// 下矢印キーで縮小
	if(key == OF_KEY_DOWN) 	zoomTarget +=10;
}