//
//  FFTFnwrGlitch.cpp
//  FFTMultiScene
//
//  Created by Atsushi Tadokoro on 1/12/13.
//
//

#include "FFTFnwrGlitch.h"
#include "testApp.h"

FFTFnwrGlitch::FFTFnwrGlitch(){
    //fnwr.loadImage("KatsuhiroChiba.png");
    fnwr.loadImage("chanel_logo2.png");
    
    // 頂点情報を初期化
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			myVerts[j * WIDTH + i].set(i,j, 0);
			myColor[j * WIDTH + i].set(1.0, 1.0, 1.0, 1.0);
		}
	}
    // 頂点バッファに位置と色の情報を設定
	myVbo.setVertexData(myVerts, NUM_PARTICLES, GL_DYNAMIC_DRAW);
	myVbo.setColorData(myColor, NUM_PARTICLES, GL_DYNAMIC_DRAW);
    
    /*
     stiffness = 0.8;
     damping = 0.9;
     mass = 4.0;
     */
    
    stiffness = 2.0;
    damping = 0.93;
    mass = 14.0;
}

void FFTFnwrGlitch::update(){
    // unsigned char *pixels = fnwr.getPixels();
    // ピクセルごとに処理
    pixels = fnwr.getPixels();
    zMax = 0;
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            
            // ピクセルノRGB値を取得
            float r = (float)pixels[j * fnwr.width * 3 + i * 3] / 256.0;
            float g = (float)pixels[j * fnwr.width * 3 + i * 3 + 1] / 256.0;
            float b = (float)pixels[j * fnwr.width * 3 + i * 3 + 2] / 256.0;
            
            // RGBから明度を算出
            float brightness = (r + g + b) / 3.0f;
            //float addZ = brightness * -100 + ((testApp*)ofGetAppPtr())->avg_power * brightness * -0.1;
            float addZ = ((testApp*)ofGetAppPtr())->avg_power * brightness * -2.0;
            
            float forceZ = stiffness * -myVerts[j * WIDTH + i].z + addZ;
            float accelerationZ = forceZ / mass;
            vec[i] = damping * (vec[i] + accelerationZ);
            myVerts[j * WIDTH + i].z += vec[i];
            
            //float z = brightness * -100 + ((testApp*)ofGetAppPtr())->avg_power * brightness * -40;
            if (myVerts[j * WIDTH + i].z < zMax) {
                zMax = myVerts[j * WIDTH + i].z;
            }
            
            // 明度から頂点の位置を設定
            //myVerts[j * WIDTH + i] = ofVec3f(i, j, z);
            
            // 頂点の色はカメラのピクセルの値をそのまま使用
            myColor[j * WIDTH + i] = ofFloatColor(r, g, b, 1.0);
        }
    }
    
    // VBOの座標と色の情報を更新
    myVbo.updateVertexData(myVerts, NUM_PARTICLES);
    myVbo.updateColorData(myColor, NUM_PARTICLES);
}

void FFTFnwrGlitch::draw(){
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDisableBlendMode();
    ofDisableLighting();
    ofPushMatrix();
    ofScale(5.0,5.0,2.0);
    ofRotateX(95);
    //ofRotateZ(160);
    //ofRotateY(ofGetElapsedTimef() * 7);
    ofRotateZ(ofGetElapsedTimef() * -0.5);
	// パーティクルのZ軸の位置によって大きさを変化させる
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    glPointSize(((testApp*)ofGetAppPtr())->avg_power * 40 + 1000);
    //ofTranslate(-320, -240, -zMax/2.0f);
    ofTranslate(-300, -300, -zMax/2.0f);
    glEnable( GL_POINT_SMOOTH );
    myVbo.draw(GL_POINTS, 0, NUM_PARTICLES);
    ofPopMatrix();
    ofEnableLighting();
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    glDisable(GL_POINT_SMOOTH);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}

void FFTFnwrGlitch::keyPressed(int key){
    
}

void FFTFnwrGlitch::resetCam(){
    
}