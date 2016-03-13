#pragma once

#include "ofxSvgPathContext.h"

class ofxSvgCommand {
	friend class ofxSvgCommandHandle;
protected:
	bool relative;
	virtual ofxSvgCommand* clone() const = 0;
public:
	ofxSvgCommand() : relative(true) {}
	virtual void draw(ofxSvgPathContext& context) const = 0;
};
