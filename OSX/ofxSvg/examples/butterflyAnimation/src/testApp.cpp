#include "testApp.h"

void testApp::setup(){
	ofBackground(255, 255, 255);
	Butterfly::addFile("Butterfly_001.svg");
	Butterfly::addFile("Butterfly_002.svg");
	Butterfly::addFile("Butterfly_003.svg");
	Butterfly::addFile("Butterfly_004.svg");
	for(int i = 0; i < 512; i++) {
		butterflies.push_back(Butterfly());
	}
}

void testApp::update(){
}

void testApp::draw(){
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(ofMap(mouseY, 0, ofGetHeight(), 180, 0), 1, 0, 0);
	ofRotate(ofMap(mouseX, 0, ofGetWidth(), 90, -90), 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	for(int i = 0; i < butterflies.size(); i++)
		butterflies[i].draw(ofGetElapsedTimef());
	glDisable(GL_DEPTH_TEST);
}

void testApp::keyPressed(int key) {
	ofSaveFrame();
}
