#pragma once

#include "ofxSvgCommand.h"

class ofxSvgSmoothCurveTo : public ofxSvgCommand {
protected:
	ofxPoint2f control2, point;
public:
	ofxSvgSmoothCurveTo(ofPoint control2, ofPoint point, bool relative = true) {
		this->control2.set(control2);
		this->point.set(point);
		this->relative = relative;
	}
	void draw(ofxSvgPathContext& context) const {
		ofxPoint2f& lastPoint = context.lastPoint;
		ofxSvgCommand* lastCommand = context.lastCommand;
		ofxPoint2f control1;
		if(typeid(*lastCommand) == typeid(ofxSvgCurveTo)) {
			ofxSvgCurveTo* curveTo = dynamic_cast<ofxSvgCurveTo*>(lastCommand);
			control1 = curveTo->control2;
			control1.rotate(180, curveTo->point);
			control1 += lastPoint;
			control1 -= curveTo->point;
		} else if(typeid(*lastCommand) == typeid(ofxSvgSmoothCurveTo)) {
			ofxSvgSmoothCurveTo* curveTo = dynamic_cast<ofxSvgSmoothCurveTo*>(lastCommand);
			control1 = curveTo->control2;
			control1.rotate(180, curveTo->point);
			control1 += lastPoint;
			control1 -= curveTo->point;
		} else {
			control1 = lastPoint;
		}
		if(relative) {
			ofBezierVertex(
				control1.x, control1.y,
				lastPoint.x + control2.x, lastPoint.y + control2.y,
				lastPoint.x + point.x, lastPoint.y + point.y);
			lastPoint += point;
		} else {
			ofBezierVertex(
				control1.x, control1.y,
				control2.x, control2.y,
				point.x, point.y);
			lastPoint.set(point);
		}
	}
	ofxSvgSmoothCurveTo* clone() const {
		return new ofxSvgSmoothCurveTo(*this);
	}
};
