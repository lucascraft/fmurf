/*
 *  gestures.h
 *
 *  openFrameworks
 *
 *  Copyright Lucas Bigeardel 2010. All rights reserved.
 *  This file is part of Fmurf.
 *
 *  Fmurf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Fmurf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fmurf.  If not, see <http://www.gnu.org/licenses/>
 *
 */

#ifndef _GESTURES
#define _GESTURES

#ifdef TARGET_OS_MAC

#include "ofMain.h"

#include "ofxTuio.h"

#include "ofxMouseGestureClassification.h"

enum SmurfGestureClassification {
	GESTURE_UNKNOWN, // -1
	GESTURE_SELECTION, // 1
	GESTURE_MULTIPLE_SELECTION, // 1
	GESTURE_CREATE_VIRTUAL_SMURF, // 2
	GESTURE_CREATE_SQUARE_FREQ_LINK, // 3
	GESTURE_CREATE_SIN_FREQ_LINK, // 4
	GESTURE_CREATE_TRIANGLE_FREQ_LINK, // 5
	GESTURE_CREATE_SWATOOTH_FREQ_LINK // 6
};

class SmurfGestures {
protected:
	SmurfGestureClassification latestGesture;
public:
	// the object used for recognition of a set of gestures
	ofMouseGestureClassification *classification;

	SmurfGestureClassification isMatching(vector<ofxTuioPoint> *points);
	SmurfGestureClassification convert(int _ofGestureClassification);
	string getGestureLabel(SmurfGestureClassification _ofGestureClassification);
	string getLatestGestureLabel();
	SmurfGestureClassification getLatestGesture();
	
	// CTOR
	SmurfGestures();
};
#endif

#endif