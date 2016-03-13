#pragma once

#include "ofxVectorMath.h"
#include "ofxXmlSettings.h"
#include "ofxSvgPath.h"
#include "ofxDisplayList.h"

enum ofAnchorMode {
	OF_ANCHOR_CORNER,
	OF_ANCHOR_CENTER};

class ofxSvg {
protected:
	float width, height;
	ofxPoint2f anchor;
	vector<ofxSvgPath> paths;
	ofxDisplayList fullList, plainList;
	bool useDisplayList;
public:
	bool loadFile(string filename) {
		bool bLoaded = false;
		useDisplayList = true;

		ofxXmlSettings xml;
		bLoaded = xml.loadFile(filename);

		width = xml.getAttribute("svg", "width", 0., 0);
		height = xml.getAttribute("svg", "height", 0., 0);
		float xAnchor = xml.getAttribute("svg", "x", 0., 0);
		float yAnchor = xml.getAttribute("svg", "y", 0., 0);
		anchor.set(xAnchor, yAnchor);

		xml.pushTag("svg");
		loadPaths(xml);
		xml.popTag();
		
		return bLoaded;
	}
	void loadPaths(ofxXmlSettings& xml) {
		int totalPaths = xml.getNumTags("path");
		for(int i = 0; i < totalPaths; i++)
			paths.push_back(ofxSvgPath(xml, i));
		int totalGroups = xml.getNumTags("g");
		for(int i = 0; i < totalGroups; i++) {
			xml.pushTag("g", i);
			loadPaths(xml);
			xml.popTag();
		}
	}
	void setUseDisplayList(bool useDisplayList) {
		this->useDisplayList = useDisplayList;
	}
	int size() const {
		return paths.size();
	}
	ofxSvgPath& getPath(int i) {
		return paths[i];
	}
	float getWidth() {
		return width;
	}
	float getHeight() {
		return height;
	}
	void setAnchor(ofPoint& anchor) {
		this->anchor = anchor;
	}
	void setAnchor(ofAnchorMode mode) {
		if(mode == OF_ANCHOR_CORNER) {
			anchor.x = 0;
			anchor.y = 0;
		} else if(mode == OF_ANCHOR_CENTER) {
			anchor.x = width / 2;
			anchor.y = height / 2;
		}
	}
	ofxPoint2f& getAnchor() {
		return anchor;
	}

	void draw(float x, float y) {
		draw(x, y, width, height);
	}
	void draw(float scale) {
		draw(0, 0, width * scale, height * scale);
	}
	void draw(float x, float y, float width, float height) {
		ofPushMatrix();
		ofTranslate(x, y);
		ofScale(width / this->width, height / this->height);
		draw();
		ofPopMatrix();
	}
	void draw() {
		if(!useDisplayList || !fullList.draw()) {
			fullList.begin();
			ofPushMatrix();
			ofTranslate(-anchor.x, -anchor.y);
			for(int i = 0; i < size(); i++)
				paths[i].draw();
			ofPopMatrix();
			fullList.end();
		}
	}

	void drawPlain(float x, float y) {
		drawPlain(x, y, width, height);
	}
	void drawPlain(float scale) {
		drawPlain(0, 0, width * scale, height * scale);
	}
	void drawPlain(float x, float y, float width, float height) {
		ofPushMatrix();
		ofTranslate(x, y);
		ofScale(width / this->width, height / this->height);
		drawPlain();
		ofPopMatrix();
	}
	void drawPlain() {
		if(!plainList.draw()) {
			plainList.begin();
			ofPushMatrix();
			ofTranslate(-anchor.x, -anchor.y);
			for(int i = 0; i < size(); i++)
				paths[i].drawShape();
			ofPopMatrix();
			plainList.end();
		}
	}

	void update() {
		fullList.update();
		plainList.update();
	}
};
