#pragma once

#include "ofxSvgCommand.h"

class ofxSvgClosePath : public ofxSvgCommand {
public:
	ofxSvgClosePath(bool relative = true) {
		this->relative = relative;
	}
	void draw(ofxSvgPathContext& context) const {
		ofxPoint2f& firstPoint = context.firstPoint;
		ofVertex(firstPoint.x, firstPoint.y);
		context.lastPoint = context.firstPoint;
	}
	ofxSvgClosePath* clone() const {
		return new ofxSvgClosePath(*this);
	}
};
