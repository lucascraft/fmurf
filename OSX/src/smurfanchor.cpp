/*
 *  smurfanchor.cpp
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

#include "smurfanchor.h"
#include "smurf.h"




float SmurfAnchor::getOwnerSid() {
	return ownerSid;
}

void SmurfAnchor::setOwnerSid(float _sid) {
	ownerSid = _sid;
}

float SmurfAnchor::getOwnerFid() {
	return ownerFid;
}

void SmurfAnchor::setOwnerFid(float _fid) {
	ownerFid = _fid;
}

AnchorKind SmurfAnchor::getAcnhorKind() {
	return anchorKind;
}

void SmurfAnchor::setAnchorKind(AnchorKind _kind) {
	anchorKind = _kind;
}

void SmurfAnchor::draw() {
	ofStyle oldStyle = ofGetStyle();
	
	ofStyle ofStyla = ofStyle();
	ofStyla.lineWidth = 2.0;
	ofStyla.circleResolution = 360;
	ofStyla.smoothing = true;
	ofStyla.blending = true;
	
	ofSetStyle(ofStyla);
	ofPushMatrix();
	
	ofFill();
	
	ofCircle(getTuio()->getX()*ofGetWidth(), getTuio()->getY()*ofGetHeight(), 3);
	
	ofPopMatrix();

	ofSetStyle(oldStyle);
	
	delete &ofStyla;
}

//void SmurfAnchor::draw(ofxTuioPoint _ptOwner, ofxTuioPoint _ptTarget, int ownerRadius) {
//	
//	
//}