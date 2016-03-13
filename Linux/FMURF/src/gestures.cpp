/*
 *  gestures.cpp
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

#include "gestures.h"

SmurfGestures::SmurfGestures() {
	classification = new ofMouseGestureClassification();
}

SmurfGestureClassification SmurfGestures::convert(int _ofGestureClassification) {
	SmurfGestureClassification curGesture = GESTURE_UNKNOWN;
	if (_ofGestureClassification == 0) {
		curGesture = GESTURE_CREATE_SIN_FREQ_LINK;
	} else if (_ofGestureClassification == 1) {
		curGesture = GESTURE_CREATE_TRIANGLE_FREQ_LINK;
	} else if (_ofGestureClassification == 2) {
		curGesture = GESTURE_CREATE_SQUARE_FREQ_LINK;
	} else if (_ofGestureClassification == 3) {
		curGesture = GESTURE_SELECTION;
	} else if (_ofGestureClassification == 4) {
		curGesture = GESTURE_CREATE_VIRTUAL_SMURF;
	} 
	return curGesture;
}

string SmurfGestures::getGestureLabel(SmurfGestureClassification _ofGestureClassification) {
	string curGesture = "GESTURE_UNKNOWN";
	if (_ofGestureClassification == GESTURE_CREATE_SIN_FREQ_LINK) {
		curGesture = "GESTURE_CREATE_SIN_FREQ_LINK";
	} else if (_ofGestureClassification == GESTURE_CREATE_TRIANGLE_FREQ_LINK) {
		curGesture = "GESTURE_CREATE_TRIANGLE_FREQ_LINK";
	} else if (_ofGestureClassification == GESTURE_CREATE_SQUARE_FREQ_LINK) {
		curGesture = "GESTURE_CREATE_SQUARE_FREQ_LINK";
	} else if (_ofGestureClassification == GESTURE_SELECTION) {
		curGesture = "GESTURE_SELECTION";
	} else if (_ofGestureClassification == GESTURE_CREATE_VIRTUAL_SMURF) {
		curGesture = "GESTURE_CREATE_VIRTUAL_SMURF";
	} 
	return curGesture;
}

SmurfGestureClassification SmurfGestures::isMatching(vector<ofxTuioPoint> *points) {
	vector<ofMousePosition> *positions = new vector<ofMousePosition>();

	for (int i=0; i<points->size(); i++) {
		ofxTuioPoint pt = points->at(i);
		positions->push_back(ofMousePosition(pt.getX()*ofGetWidth(), pt.getY()*ofGetHeight()));
	}
	int _classification = classification->classify(*positions);
	delete positions;
	
	SmurfGestureClassification classif = convert(_classification);
	latestGesture = classif;
	return classif;
}

string  SmurfGestures::getLatestGestureLabel() {
	return getGestureLabel(getLatestGesture());
}

SmurfGestureClassification SmurfGestures::getLatestGesture() {
	return latestGesture;
}

