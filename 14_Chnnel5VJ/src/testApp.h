#pragma once

#include "ofMain.h"
//#include "ofxControlPanel.h"
#include "ofxPostProcessing.h"
#include "Fnwr.h"
#include "FFTCircle.h"
#include "FFTRotate.h"
#include "FFTBox.h"
#include "FFTParticle.h"
#include "FFTGlitch.h"
#include "FFTFnwrGlitch.h"
#include "FFTColor.h"
#include "FFTGrid.h"
#include "FFTFnwrNoise.h"
#include "FFTTracer.h"
#include "FFTSinewave.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
	void keyPressed  (int key);
	void audioIn(float * input, int bufferSize, int nChannels);
    
    //FFTの入出力の値を確保
    float *audio_input;
	float *magnitude, *phase, *power;
	float *magnitude_average, *magnitude_average_snapshot;
	float avg_power;

	//バッファーサイズとFFTサイズ
	int buffer_size;
	int fft_size, max_fft_size;
	
	fft myfft; //FFTクラスのインスタンス
    
    int mode;
    //ofxControlPanel gui;
    Fnwr *fnwr;
    FFTCircle *fftCircle;
    FFTSinewave *fftSinewave;
    //FFTRotate *fftRotate;
    FFTBox *fftBox;
    //FFTParticle *fftParticle;
    FFTGlitch *fftGlitch;
    FFTFnwrGlitch *fftFnwrGlitch;
    FFTColor *fftColor;
    FFTGrid *fftGrid;
    FFTFnwrNoise *fftFnwrNoise;
    FFTTracer *fftTracer;
    
    // scene stuff
    ofxPostProcessing post;
    ofEasyCam cam;
    ofLight light;
    float audioLevel;
};
