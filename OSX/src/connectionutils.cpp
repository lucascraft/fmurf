/*
 *  connectionutils.cpp
 *  openFrameworks
 *
 *  Created by lucas bigeardel on 28/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#include "connectionutils.h"
#ifdef TARGET_OS_MAC

SConnectionVisual ConnectionsUtils::getVisualFromGesture(SmurfGestureClassification _classification) {
	if (_classification == GESTURE_CREATE_SIN_FREQ_LINK) {
		return CONNECTION_SIN_FREQ;
	} else if (_classification == GESTURE_CREATE_SQUARE_FREQ_LINK) {
		return CONNECTION_SQUARE_FREQ;
	}
	else if (_classification == GESTURE_CREATE_TRIANGLE_FREQ_LINK) {
		return CONNECTION_TRIANGLE_FREQ;
	}
	return CONNECTION_LINE;
}

float ConnectionsUtils::getConnectionAngle() {
	double x1, x2, y1, y2;
	
	x1 = 2*cos(PI/6);
	y1 = 2*sin(PI/6);
	x2 = 3*cos(PI/2);
	y2 = 3*sin(PI/2);
	
	return atan(y2/x2)-atan(y1/x1), PI/3;
}
#endif