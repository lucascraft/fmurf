#pragma once

#include "ofxSvg.h"

class Butterfly {
protected:
	static vector<ofxSvg> shapes;

	ofxSvg* shape;

	float lowerTheta, upperTheta;
	float pausingIntentionality, flappingIntentionality;

	float pausingRate, flappingRate;
	float scale;
	ofxColor color;
public:
	ofxPoint3f position;

	static void addFile(string filename) {
		ofxSvg svg;
		svg.loadFile(filename);
		shapes.push_back(svg);
	}

	Butterfly() {
		int i = (int) (ofRandom(0, shapes.size()));
		shape = &(shapes[i]);

		pausingRate = ofRandom(1, 2);
		flappingRate = ofRandom(5, 15);
		lowerTheta = -30;
		upperTheta = 60;
		pausingIntentionality = 3;
		flappingIntentionality = 1.5;
		scale = ofRandom(.1, .5);

		position.set(
			ofRandom(-ofGetWidth(), ofGetWidth()) / 2,
			ofRandom(-ofGetHeight(), ofGetHeight()) / 2,
			ofRandom(-ofGetHeight(), ofGetHeight()) / 2);

		color = ofxColor(
			ofRandom(0, 255),
			255,
			255,
			128,
			OF_COLOR_HSV);
	}
	Butterfly(const Butterfly& from) {
		shape = from.shape;
		pausingRate = from.pausingRate;
		flappingRate = from.flappingRate;
		lowerTheta = from.lowerTheta;
		upperTheta = from.upperTheta;
		pausingIntentionality = from.pausingIntentionality;
		flappingIntentionality = from.flappingIntentionality;
		position = from.position;
		scale = from.scale;
		color = from.color;
	}
	void draw(float time) {
		float pausingState = tanh(sin(pausingRate * time * PI) * pausingIntentionality);
		float flappingState = tanh(sin(flappingRate * time * PI) * flappingIntentionality);
		float overallState = ofLerp(flappingState, 1, ofMap(pausingState, -1, 1, 0, 1));
		float theta = ofMap(overallState, -1, 1, lowerTheta, upperTheta);

		ofPushMatrix();
		ofTranslate(position.x, position.y, position.z);

		ofPushStyle();
		ofEnableAlphaBlending();
		ofSetColor(color);
		ofFill();

		ofPushMatrix();
		ofScale(-1, 1);
		ofRotate(theta, 0, -1, 0);
		shape->drawPlain(scale);
		ofPopMatrix();

		ofPushMatrix();
		ofRotate(theta, 0, -1, 0);
		shape->drawPlain(scale);
		ofPopMatrix();

		ofDisableAlphaBlending();
		ofPopStyle();

		ofPopMatrix();
	}
};
