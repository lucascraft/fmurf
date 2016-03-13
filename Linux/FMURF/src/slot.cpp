/*
 *  slot.cpp
 *
 *  openFrameworks
 *
 *  Created by lucas bigeardel on 16/02/10.
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

#include "ofMain.h"
#include "slot.h"
#include "smurf.h"
#include "ofxOsc.h"
#include "ofxTuio.h"


Slot::Slot(SlotPosition _position) {
	Slot(_position, PUSH, BOX);	
}

Slot::Slot(SlotPosition _position, SlotKind _kind) {
	Slot(_position, _kind, BOX);
}

Slot::Slot(SlotPosition _position, SlotKind _kind, SlotVisual _visual) {
	tuio = new ofxTuioContainer(_position, 0.0, 0.0);
	oscMsg = new std::vector<ofxOscMessage*>();
	position = _position;
	kind = _kind;
	visual = _visual;
	setRadius(10);
}

SlotKind Slot::getKind() {
	return kind;
}

SlotVisual Slot::getVisual() {
	return visual;
}

SlotPosition Slot::getPosition() {
	return position;
}




vector<ofxOscMessage*>* Slot::getOscMessages() {
	return oscMsg;
}

string Slot::getLabelFromSlotPosition() {
	std::string ret = "";
	switch (getPosition()) {
		case _A:
			ret = "A";
			break;
		case _B:
			ret = "B";
			break;
		case _C:
			ret = "C";
			break;
		case _D:
			ret = "D";
			break;
		case _E:
			ret = "E";
			break;
		case _F:
			ret = "F";
			break;
		case _G:
			ret = "G";
			break;
		case _H:
			ret = "H";
			break;
		case _I:
			ret = "I";
			break;
		case _J:
			ret = "J";
			break;
		case _K:
			ret = "K";
			break;
		case _L:
			ret = "L";
			break;
		case _M:
			ret = "M";
			break;
		case _N:
			ret = "N";
			break;
		case _O:
			ret = "O";
			break;
		case _P:
			ret = "P";
			break;
		default:
			break;
	};
	return ret;
	
}
int Slot::getOrderFromSlotPosition() {
	int ret = -1;
	switch (getPosition()) {
		case _A:
			ret = 0;
			break;
		case _B:
			ret = 1;
			break;
		case _C:
			ret = 2;
			break;
		case _D:
			ret = 3;
			break;
		case _E:
			ret = 4;
			break;
		case _F:
			ret = 5;
			break;
		case _G:
			ret = 6;
			break;
		case _H:
			ret = 7;
			break;
		case _I:
			ret = 8;
			break;
		case _J:
			ret = 9;
			break;
		case _K:
			ret = 10;
			break;
		case _L:
			ret = 11;
			break;
		case _M:
			ret = 12;
			break;
		case _N:
			ret = 13;
			break;
		case _O:
			ret = 14;
			break;
		case _P:
			ret = 15;
			break;
		default:
			break;
	};
	return ret;
	
}
void Slot::draw() {
	if (isSelected()) {
		ofFill();
	} else {
		ofNoFill();
	}
	
	ofCircle(getTuio()->getX()*ofGetWidth(), getTuio()->getY()*ofGetHeight(), getRadius());	
	
	ofDrawBitmapString(getLabelFromSlotPosition(), getTuio()->getX(), getTuio()->getY());
}
