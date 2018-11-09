#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	chooseSoundFile();
	setUpGUI();

	//the size of the array must be a multiple of the value of "bands"
	fftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++) {
		fftSmooth[i] = 0;
	}
	bands = 512;
	beat.setLoop(true);

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSoundUpdate();

	//slices the spectrum into bands, each represented as a float between 0 and 1
	float* value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= 0.99;

		//takes the max, either the smoothed or the incoming
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	//draw the ofxGUI panel, set the volume and speed, and draw the shape if necessary
	gui.draw();
	beat.setVolume(volume);
	beat.setSpeed(speed);
	ofSetBackgroundColor(0);
	drawShape();
	printTime();

}

//--------------------------------------------------------------
void ofApp::printTime() {

	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Time: " + ofToString((double)beat.getPositionMS() / 1000.0), 10, 225);
	ofDrawRectangle(10, 200, 200, 10);
	ofSetColor(255, 165, 0);
	ofDrawRectangle(10, 200, (int)(200 * (beat.getPosition())), 10);

}

//--------------------------------------------------------------
void ofApp::drawShape() {

	//key_pressed is changed when buttons are clicked on the GUI panel 
	//and the corresponding shape is drawn
	switch (key_pressed) {
	case '1':
		for (int i = 0; i < bands; i++) {

			setColor(i);
			ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150));

		}
		break;
	case '2':
		for (int i = 0; i < bands; i++) {

			setColor(i);

			//four seperate rectangles, all coming from the center and moving out in each diagonal
			ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150), -(fftSmooth[i] * 150));
			ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150), (fftSmooth[i] * 150));
			ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, (fftSmooth[i] * 150), -(fftSmooth[i] * 150));
			ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, (fftSmooth[i] * 150), (fftSmooth[i] * 150));

		}
		break;
	case '3':
		for (int i = 0; i < bands; i++) {

			setColor(i);
			ofDrawTriangle((ofGetWidth() / 2) + (-(fftSmooth[i] * 150)), (ofGetHeight() / 2) + (-(fftSmooth[i] * 150)),
				(ofGetWidth() / 2) + (fftSmooth[i] * 150), (ofGetHeight() / 2) + (-(fftSmooth[i] * 150)),
				ofGetWidth() / 2, (ofGetHeight() / 2) + (fftSmooth[i] * 150));

		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::setUpGUI() {

	//tying the buttons to their corresponding functions
	circle.addListener(this, &ofApp::changeToCircle);
	square.addListener(this, &ofApp::changeToSquare);
	triangle.addListener(this, &ofApp::changeToTriangle);
	play.addListener(this, &ofApp::playFile);
	stop.addListener(this, &ofApp::stopFile);
	changeSong.addListener(this, &ofApp::changeFile);

	gui.setup();
	gui.add(circle.setup("Circle"));
	gui.add(square.setup("Square"));
	gui.add(triangle.setup("Triangle"));
	gui.add(play.setup("Play"));
	gui.add(stop.setup("Stop"));
	gui.add(changeSong.setup("Change Song"));
	gui.add(volume.setup("Volume", 0.2, 0.0, 0.5));
	gui.add(speed.setup("Speed", 1.0, -3.0, 3.0));

}

//--------------------------------------------------------------
void ofApp::setColor(int currentIteration) {

	//alternates between red, blue, green when drawing the shapes
	if (currentIteration % 3 == 0) {
		ofSetColor(0, 0, 255);
	}
	else if (currentIteration % 3 == 1) {
		ofSetColor(0, 255, 0);
	}
	else {
		ofSetColor(255, 0, 0);
	}

}

//--------------------------------------------------------------
void ofApp::changeToCircle() {

	key_pressed = '1';

}

//--------------------------------------------------------------
void ofApp::changeToSquare() {

	key_pressed = '2';

}

//--------------------------------------------------------------
void ofApp::changeToTriangle() {

	key_pressed = '3';

}

//--------------------------------------------------------------
void ofApp::playFile() {

	beat.play();

}

//--------------------------------------------------------------
void ofApp::stopFile() {

	beat.stop();

}

//--------------------------------------------------------------
void ofApp::changeFile() {

	beat.unload();
	chooseSoundFile();

}

//--------------------------------------------------------------
void ofApp::chooseSoundFile() {

	audio_file = ofSystemTextBoxDialog("**GO FULLSCREEN** Enter the name of the audio file you want to play. Type 'default' for a default file.", audio_file);
	if (audio_file == "default") {
		audio_file = "Sample_04.mp3";
	}

	//tests whether the beat is properly loaded, and continues to prompt the user for a file until it loads
	beat.loadSound(audio_file);
	while (!beat.isLoaded()) {
		audio_file = ofSystemTextBoxDialog("**GO FULLSCREEN** Not a valid file. Enter a valid flie or type 'default' for a default file.", audio_file);
		if (audio_file == "default") {
			audio_file = "Sample_04.mp3";
		}
		beat.loadSound(audio_file);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}