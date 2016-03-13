#pragma once

#include "ofxSvgCommand.h"
#include "ofxSvgClosePath.h"

// does not implement multi-path paths
// (i.e., paths with multiple movetos)

class ofxSvgMoveTo : public ofxSvgCommand {
public:
	ofxVec2f offset;
	ofxSvgMoveTo(ofPoint point, bool relative = false) {
		offset.set(point.x, point.y);
		this->relative = relative;
	}
	ofxSvgMoveTo(const ofxSvgMoveTo& from) {
		offset.set(from.offset.x, from.offset.y);
	}
	void draw(ofxSvgPathContext& context) const {
		if(relative) {
			ofVertex(
				context.lastPoint.x + offset.x,
				context.lastPoint.y + offset.y);
			context.lastPoint += offset;
		} else {
			ofVertex(
				offset.x,
				offset.y);
			context.lastPoint.set(offset);
		}
		if(context.lastCommand == NULL ||
			typeid(*(context.lastCommand)) == typeid(ofxSvgClosePath))
			context.firstPoint = context.lastPoint;
	}
	ofxSvgMoveTo* clone() const {
		return new ofxSvgMoveTo(*this);
	}
};
