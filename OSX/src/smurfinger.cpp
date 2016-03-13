/*
 *  smurfinger.cpp
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

#include "smurfinger.h"

// -----------------------------------------------
//
// Constructor
//
// -----------------------------------------------
SmurFinger::SmurFinger() {
	points = new vector<ofxTuioPoint>();
}

// -----------------------------------------------
//
// Points accessor
//
// -----------------------------------------------
vector<ofxTuioPoint>* SmurFinger::getPoints() {
	return points;
}

// -----------------------------------------------
//
// Method to collect all points related to finger 
// moves between CURSOR_ADD and CURSOR_REMOVE
// events
//
// -----------------------------------------------
void SmurFinger::addPoint(ofxTuioPoint _pos) {
	if (points->size() > 0) {
		ofxTuioPoint point = *points->end();
		if (point.getX() == _pos.getX() && point.getY() == _pos.getY()) {
			return;
		}
	}
	points->push_back(_pos);
}

// -----------------------------------------------
//
// Removes points on CURSOR_REMOVE event
//
// -----------------------------------------------
void SmurFinger::clearPoints() {
	points->clear();
}

// -----------------------------------------------
//
// Add a new cursor instance and send 
// a OSC message to host/port
//
// -----------------------------------------------
void SmurFinger::onAdd(ofxOscSender* _sender) {
	ofxOscMessage *msg = new ofxOscMessage();
	
	ofxTuioCursor *obj = (ofxTuioCursor *) getTuio(); 
	if (obj != NULL) {
		msg->setAddress("/smurf/cursor/" + ofToString(obj->getFingerId()) + "/add");
		msg->addFloatArg(obj->getX());
		msg->addFloatArg(obj->getY());
	}
	_sender->sendMessage(*msg);
	
	delete msg;	
}

// -----------------------------------------------
//
// Update cursor instance and send 
// an OSC message to host/port
//
// -----------------------------------------------
void SmurFinger::onUpdate(ofxOscSender* _sender) {	
	ofxOscMessage *msg = new ofxOscMessage();
	
	ofxTuioCursor *obj = (ofxTuioCursor *) getTuio(); 
	if (obj != NULL) {
		msg->setAddress("/smurf/cursor/" + ofToString(obj->getFingerId()) + "/update");
		msg->addFloatArg(obj->getX());
		msg->addFloatArg(obj->getY());
	}
	_sender->sendMessage(*msg);
	
	delete msg;
}

// -----------------------------------------------
//
// Remove cursor instance and send 
// an OSC message to host/port
//
// -----------------------------------------------
void SmurFinger::onRemove(ofxOscSender* _sender) {
	ofxOscMessage *msg = new ofxOscMessage();
	
	ofxTuioCursor *obj = (ofxTuioCursor *) getTuio(); 
	if (obj != NULL) {
		msg->setAddress("/smurf/cursor/" + ofToString(obj->getFingerId()) + "/remove");
		msg->addFloatArg(obj->getX());
		msg->addFloatArg(obj->getY());
	}
	_sender->sendMessage(*msg);
	
	delete msg;
}
