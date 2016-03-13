#pragma once

#include "ofxSvgCommand.h"

class ofxSvgVerticalLineTo : public ofxSvgCommand {
public:
	float y;
	ofxSvgVerticalLineTo(float y, bool relative = true) {
		this->y = y;
		this->relative = relative;
	}
	void draw(ofxSvgPathContext& context) const {
		ofxPoint2f& lastPoint = context.lastPoint;
		if(relative) {
			ofVertex(lastPoint.x, lastPoint.y + y);
			lastPoint.y += y;
		} else {
			ofVertex(lastPoint.x, y);
			lastPoint.y = y;
		}
	}
	ofxSvgVerticalLineTo* clone() const {
		return new ofxSvgVerticalLineTo(*this);
	}
};
