#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void chooseSoundFile();
	void setUpGUI();
	void drawShape();
	void setColor(int currentIteration);
	void printTime();

	//has a load and play function that allows sounds files from data folder to be used
	ofSoundPlayer beat;

	float* fftSmooth;

	//ofxGUI functions
	void changeToCircle();
	void changeToSquare();
	void changeToTriangle();
	void playFile();
	void stopFile();
	void changeFile();

	//ofxGUI variables
	ofxPanel gui;
	ofxButton play;
	ofxButton stop;
	ofxButton circle;
	ofxButton square;
	ofxButton triangle;
	ofxButton changeSong;
	ofxFloatSlider volume;
	ofxFloatSlider speed;

	//number of sounds in the sound spectrum to receive
	int bands;

	int current_band;
	int key_pressed;
	string audio_file;



};
