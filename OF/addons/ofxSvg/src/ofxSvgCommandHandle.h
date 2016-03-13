#pragma once

#include "ofxSvgCommand.h"
#include "ofxXmlSettings.h"

#include "ofxSvgPathContext.h"
#include "ofxSvgMoveTo.h"
#include "ofxSvgCurveTo.h"
#include "ofxSvgSmoothCurveTo.h"
#include "ofxSvgLineTo.h"
#include "ofxSvgHorizontalLineTo.h"
#include "ofxSvgVerticalLineTo.h"

inline float readFloat(istream& stream) {
	float x;
	stream >> x;
	if(stream.peek() == ',')
		stream.ignore(1);
	return x;
}

inline ofPoint readPoint(istream& stream) {
	ofPoint point;
	point.x = readFloat(stream);
	point.y = readFloat(stream);
	return point;
}

class ofxSvgCommandHandle {
protected:
	ofxSvgCommand* ptr;
public:
	ofxSvgCommandHandle() : ptr(NULL) {}
	ofxSvgCommandHandle(const ofxSvgCommandHandle& from) : ptr(NULL) {
		if(from.ptr != NULL)
			ptr = from.ptr->clone();
	}
	ofxSvgCommandHandle(char name, istream& data) : ptr(NULL) {
		read(name, data);
	}
	istream& read(char name, istream& data) {
		if(name == 'm' || name == 'M')
			ptr = new ofxSvgMoveTo(readPoint(data), name == 'm');
		if(name == 'c' || name == 'C') {
			ofPoint control1 = readPoint(data);
			ofPoint control2 = readPoint(data);
			ofPoint point = readPoint(data);
			ptr = new ofxSvgCurveTo(control1, control2, point, name == 'c');
		}
		if(name == 's' || name == 'S') {
			ofPoint control2 = readPoint(data);
			ofPoint point = readPoint(data);
			ptr = new ofxSvgSmoothCurveTo(control2, point, name == 's');
		}
		if(name == 'l' || name == 'L')
			ptr = new ofxSvgLineTo(readPoint(data), name == 'l');
		if(name == 'z' || name == 'Z')
			ptr = new ofxSvgClosePath();
		if(name == 'h' || name == 'H')
			ptr = new ofxSvgHorizontalLineTo(readFloat(data), name == 'h');
		if(name == 'v' || name == 'V')
			ptr = new ofxSvgVerticalLineTo(readFloat(data), name == 'v');
		if(ptr == NULL)
			cout << "error on command '" << name << "'" << endl;
		return data;
	}
	ofxSvgCommandHandle& operator=(const ofxSvgCommandHandle& from) {
		if(&from != this) {
			delete ptr;
			if(from.ptr != NULL)
				ptr = from.ptr->clone();
			else
				ptr = NULL;
		}
		return *this;
	}
	~ofxSvgCommandHandle() {
		if(ptr != NULL)
			delete ptr;
	}
	void draw(ofxSvgPathContext& context) const {
		ptr->draw(context);
		context.lastCommand = ptr;
	}
};
