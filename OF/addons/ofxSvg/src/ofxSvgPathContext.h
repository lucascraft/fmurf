#pragma once

#include "ofxSvgCommand.h"
#include "ofxVectorMath.h"

class ofxSvgCommand;

class ofxSvgPathContext {
public:
	ofxPoint2f firstPoint, lastPoint;
	ofxSvgCommand* lastCommand;
	ofxSvgPathContext() {
		lastCommand = NULL;
	}
};
