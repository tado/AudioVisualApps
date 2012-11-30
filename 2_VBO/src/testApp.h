#pragma once
#include "ofMain.h"
#include "ofVbo.h"

#define	NUM_BILLBOARDS	40000

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofEasyCam cam; // カメラ
	float zoom; // 現在のズーム
	float zoomTarget; // ズーム目標
	ofImage texture; // パーティクルに貼るテクスチャイメージ	
	ofVbo billboardVbo; // VBO
	ofVec3f billboardVerts[NUM_BILLBOARDS]; // 頂点座標情報
	ofFloatColor billboardColor[NUM_BILLBOARDS]; //頂点色情報
	ofVec3f billboardVels[NUM_BILLBOARDS]; // パーティクルの移動速度

	ofVideoGrabber myVideo; // カメラ映像
};









