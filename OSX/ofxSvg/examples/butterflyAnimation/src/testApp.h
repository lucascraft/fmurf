#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "Butterfly.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	vector<Butterfly> butterflies;
};
