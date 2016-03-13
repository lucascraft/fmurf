#pragma once

#include "ofxSvgCommand.h"

class ofxSvgLineTo : public ofxSvgCommand {
public:
	ofxPoint2f point;
	ofxSvgLineTo(ofPoint point, bool relative = true) {
		this->point.set(point);
		this->relative = relative;
	}
	void draw(ofxSvgPathContext& context) const {
		ofxPoint2f& lastPoint = context.lastPoint;
		if(relative) {
			ofVertex(lastPoint.x + point.x, lastPoint.y + point.y);
			lastPoint += point;
		} else {
			ofVertex(point.x, point.y);
			lastPoint.set(point);
		}
	}
	ofxSvgLineTo* clone() const {
		return new ofxSvgLineTo(*this);
	}
};
