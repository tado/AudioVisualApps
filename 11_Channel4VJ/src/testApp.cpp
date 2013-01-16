#include "testApp.h"

void testApp::setup(){
	//画面基本設定
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetCircleResolution(64);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofHideCursor();
    
    //FFTのサイズとバッファサイズを設定
	fft_size = 1024;
	buffer_size = fft_size * 2;
    
	//FFTサイズにあわせて出力結果の配列を左右2ch分準備
	audio_input = new float[buffer_size];
	magnitude = new float[fft_size];
	phase = new float[fft_size];
	power = new float[fft_size];
    
    // Setup light
	light.setPosition(1000, 1000, 2000);
    cam.setDistance(500);
    cam.disableMouseInput();
    
    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(true);
    post.createPass<DofPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<EdgePass>()->setEnabled(false);
        
	//GUI setup
    /*
    gui.setup("control panel test", 0, 0, 340, 400);
    gui.addPanel("panel 1", 1);
    gui.addSlider("Audio Level", "audio_level", 1.0, 0.0, 10.0, false);
    gui.loadSettings("controlPanel.xml");
    gui.hide();
     */
    
    mode = 0;
    fnwr = new Fnwr();
    fftRotate = new FFTRotate();
    fftCircle = new FFTCircle();
    fftBox = new FFTBox();
    fftParticle = new FFTParticle();
    fftGlitch = new FFTGlitch();
    fftFnwrGlitch = new FFTFnwrGlitch();
    
    //ofSoundStreamListDevices();
    
    //Sound stream
    audioLevel = 1.0f;
    ofSoundStreamSetup(0, 1, this, 44100, buffer_size, 2);
}

void testApp::update() {
    //FFT変換
	avg_power = 0.0f;
	myfft.powerSpectrum(0, (int)fft_size, audio_input, buffer_size,	magnitude, phase, power, &avg_power);

    if (mode == 1) {
        fftCircle->update();
    }
    if (mode == 2) {
        fftRotate->update();
    }
    if (mode == 3) {
        fftBox->update();
    }
    if (mode == 4) {
        fftParticle->update();
    }
    if (mode == 5) {
        fftGlitch->update();
    }
    if (mode == 6) {
        fftFnwrGlitch->update();
    }
    
    //gui.update();
}

void testApp::draw() {
    light.enable();
    post.begin(cam);

    if (mode == 0) {
        fnwr->draw();
    }
    if (mode == 1) {
        fftCircle->draw();
    }
    if (mode == 2) {
        fftRotate->draw();
    }
    if (mode == 3) {
        fftBox->draw();
    }
    if (mode == 4) {
        fftParticle->draw();
    }
    if (mode == 5) {
        fftGlitch->draw();
    }
    if (mode == 6) {
        fftFnwrGlitch->draw();
    }
    post.end();
}

void testApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    /*
    if (key == 'c') {
        gui.toggleView();
        if (gui.hidden) {
            ofHideCursor();
        } else {
            ofShowCursor();
        }
    }
     */
    if (key == '0') {
        mode = 0;
    }
    if (key == '1') {
        mode = 1;
    }
    if (key == '2') {
        mode = 2;
    }
    if (key == '3') {
        mode = 3;
    }
    if (key == '4') {
        mode = 4;
        fftParticle->reset();
    }
    if (key == '5') {
        mode = 5;
    }
    if (key == '6') {
        mode = 6;
    }
    if (key == '-') {
        audioLevel /= 1.2;
    }
    if (key == '=') {
        audioLevel *= 1.2;
    }
    if (key == 'q') {
        post[0]->setEnabled(!post[0]->getEnabled());
    }
    if (key == 'w') {
        post[1]->setEnabled(!post[1]->getEnabled());
    }
    if (key == 'e') {
        post[2]->setEnabled(!post[2]->getEnabled());
    }
    if (key == 'r') {
        post[3]->setEnabled(!post[3]->getEnabled());
    }
    if (key == 't') {
        post[4]->setEnabled(!post[4]->getEnabled());
    }
    if (key == 'y') {
        post[5]->setEnabled(!post[5]->getEnabled());
    }
    if (key == 'u') {
        post[6]->setEnabled(!post[6]->getEnabled());
    }
}

void testApp::mouseDragged(int x, int y, int button){
    //gui.mouseDragged(x, y, button);
}

void testApp::mousePressed(int x, int y, int button){
    //gui.mousePressed(x, y, button);
}

void testApp::mouseReleased(int x, int y, int button){
    //gui.mouseReleased();
}

void testApp::audioIn(float * input, int bufferSize, int nChannels) {
    for (int i = 0; i < bufferSize; i++) {
        audio_input[i] = input[i] * audioLevel;
    }
}
