#pragma once

#include "ofxColor.h"
#include "ofxSvgCommandHandle.h"

class ofxSvgPath {
private:
	float strokeWidth;
	bool hasFill, hasStroke;
	ofxColor fillColor, strokeColor;
	string fill, stroke;
	vector<ofxSvgCommandHandle> commandHandles;
public:
	ofxSvgPath(ofxXmlSettings& xml, int i) {
		setFill(xml.getAttribute("path", "fill", "none", i));
		setStroke(xml.getAttribute("path", "stroke", "none", i));
		setStrokeWidth(xml.getAttribute("path", "stroke-width", 1., i));
		setOpacity(xml.getAttribute("path", "opacity", 1., i));

		string d = xml.getAttribute("path", "d", "", i);

		istringstream handleData(d);
		handleData.setf(ios::skipws);
		while(!handleData.eof()) {
			char name;
			handleData >> name;
			ofxSvgCommandHandle command(name, handleData);
			commandHandles.push_back(command);
		}
	}
	ofxSvgPath(const ofxSvgPath& path) {
		strokeWidth = path.strokeWidth;
		hasFill = path.hasFill;
		hasStroke = path.hasStroke;
		fillColor = path.fillColor;
		strokeColor = path.strokeColor;
		fill = path.fill;
		stroke = path.stroke;
		commandHandles = path.commandHandles;
	}
	void setOpacity(float opacity) {
		fillColor.a = opacity * 255;
		strokeColor.a = opacity * 255;
	}
	void setStrokeWidth(float strokeWidth) {
		this->strokeWidth = strokeWidth;
	}
	void setFill(ofxColor fill) {
		fillColor = fill;
		hasFill = true;
	}
	void setFill(string fill) {
		this->fill = fill;
		hasFill = fill != "none";
		if(hasFill)
			fillColor = fill;
	}
	void noFill() {
		hasFill = false;
	}
	void setStroke(ofxColor stroke) {
		strokeColor = stroke;
		hasStroke = true;
	}
	void noStroke() {
		hasStroke = false;
	}
	void setStroke(string stroke) {
		this->stroke = stroke;
		hasStroke = stroke != "none";
		if(hasStroke)
			strokeColor = stroke;
	}
	void drawShape() const {
		ofxSvgPathContext context;
		ofBeginShape();
		for(int i = 0; i < commandHandles.size(); i++)
			commandHandles[i].draw(context);
		ofEndShape();
	}
	void draw() {
		ofPushStyle();

		if(fillColor.a != 255.)
			ofEnableAlphaBlending();
		if(hasFill) {
			ofFill();
			ofSetColor(fillColor);
			drawShape();
		}
		if(fillColor.a != 255.)
			ofDisableAlphaBlending();

		if(strokeColor.a != 255.)
			ofEnableAlphaBlending();
		if(hasStroke) {
			glLineWidth(strokeWidth);
			ofNoFill();
			ofSetColor(strokeColor);
			drawShape();
		}
		if(strokeColor.a != 255.)
			ofDisableAlphaBlending();

		ofPopStyle();
	}
};
