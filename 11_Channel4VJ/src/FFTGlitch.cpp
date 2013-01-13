//
//  FFTGlitch.cpp
//  OscPhase
//
//  Created by Atsushi Tadokoro on 2012/09/05.
//
//

#include "FFTGlitch.h"
#include "testApp.h"

FFTGlitch::FFTGlitch()
{
    pos = ofPoint(0,0);
    width = ofGetWidth();
    height = ofGetHeight();
    
    //	quality = OF_IMAGE_QUALITY_BEST;
    //  quality = OF_IMAGE_QUALITY_HIGH;
	//  quality = OF_IMAGE_QUALITY_MEDIUM;
    //	quality = OF_IMAGE_QUALITY_LOW;
    quality = OF_IMAGE_QUALITY_WORST;
    
    //Jpeg圧縮したデータの保存ファイル名
	compressedFilename = "glitch.jpg";
    glitchStart = 0.2;
    scale = 3.0;
    coin = 20.0;
    tempo = 80;
    amp = 0.0;
    
    clipImage.allocate(width/scale, height/scale, OF_IMAGE_COLOR);
    clipImage.grabScreen(pos.x + width/2 - width/scale/2, pos.y + height/2 - height/scale/2, width/scale, height/scale);
}

void FFTGlitch::update()
{
    if (tempo < 100) {
        tempo = 100;
    }
    if (amp < 0) {
        amp = 0;
    }
    int icoin = int(coin);
    //if (int(ofRandom(icoin)) % icoin == 0) {
    if (int(ofGetElapsedTimef()*1000) % tempo < ofGetFrameRate()){
        scale = ofRandom(2.0, 4.0);
        clipImage.grabScreen(pos.x + width/2 - width/scale/2, pos.y + height/2 - height/scale/2, width/scale, height/scale);
        clipImage.saveImage(compressedFilename, quality);
        ofBuffer file = ofBufferFromFile(compressedFilename, true);
        int fileSize = file.size();
        char * buffer = file.getBinaryBuffer();
        
        for (int i = 0; i < ofRandom(1, 4); i++) {
            int whichByte = (int) ofRandom(fileSize * glitchStart, fileSize);
            int whichBit = ofRandom(8);
            char bitMask = 1 << whichBit;
            buffer[whichByte] |= bitMask;
        }
        
        ofBufferToFile(compressedFilename, file, true);
        clipImage.loadImage(compressedFilename);
    }
}

void FFTGlitch::draw()
{
    int gray = int(ofMap(amp, 0.0, 0.3, 0, 255));
    //ofSetColor(gray);
    int br = ((testApp*)ofGetAppPtr())->avg_power * 63;
    ofSetColor(br, br, br);
    
    if (clipImage.width > 0) {
        ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
        clipImage.draw(pos, width, height);
    } else {
        //synth
        clipImage.grabScreen(pos.x + width/2 - width/scale/2, pos.y + height/2 - height/scale/2, width/scale, height/scale);
    }
}