/*
 *  smurfconnection.cpp
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

#include "smurfconnection.h"
#include "connectionutils.h"
#include "smurfanchor.h"
#include <algorithm>

#define CONNECTION_MAX_HEIGHT 25

/*
 *
 *
 */
SConnection::SConnection(SmurfAnchor *_anchorFrom, SmurfAnchor *_anchorTo, SConnectionVisual _visual, SConnectKind _kind){
	fAnchor = _anchorFrom;
	tAnchor = _anchorTo;
	visual = _visual;
	kind = _kind;
	liveData = new vector<float>();
}


/*
 *
 *
 */
SConnection::SConnection(SmurfAnchor *_anchorFrom, SmurfAnchor *_anchorTo, SConnectionVisual _visual) {
	SConnection(_anchorFrom, _anchorTo, _visual, CONNECT_UNKNOWN);
}

/*
 *
 *
 */
void SConnection::setConnectionKind(SConnectKind _kind) {
	kind = _kind;
}

/*
 *
 *
 */
SConnectKind SConnection::getConnectionKind() {
	return kind;
}

/*
 *
 *
 */
void SConnection::setConnectionVisual(SConnectionVisual _visual) {
	visual = _visual;
}

/*
 *
 *
 */
SConnectionVisual SConnection::getConnectionVisual() {
	return visual;
}

/*
 *
 *
 */
float SConnection::fromSID() {
	return fAnchor != NULL ? fAnchor->getOwnerSid() : -FLT_MAX;
}

/*
 *
 *
 */
void SConnection::setFromSID(float _fromSID) {
	if (fAnchor != NULL) {
		fAnchor->setOwnerSid(_fromSID);
	}
}

/*
 *
 *
 */
float SConnection::toSID() {
	return tAnchor == NULL ? -FLT_MAX : tAnchor->getOwnerSid();
}

/*
 *
 *
 */
void SConnection::setToSID(float _toSID) {
	if (tAnchor != NULL) {
		tAnchor->setOwnerSid(_toSID);
	}
}

/*
 *
 *
 */
float SConnection::fromFID() {
	return fAnchor != NULL ? fAnchor->getOwnerFid() : -FLT_MAX;
}

/*
 *
 *
 */
void SConnection::setFromFID(float _fromFID) {
	if (fAnchor != NULL) {
		fAnchor->setOwnerFid(_fromFID);
	}
}

/*
 *
 *
 */
float SConnection::toFID() {
	return tAnchor == NULL ? -FLT_MAX : tAnchor->getOwnerFid();
}

/*
 *
 *
 */
void SConnection::setToFID(float _toFID) {
	if (tAnchor != NULL) {
		tAnchor->setOwnerFid(_toFID);
	}
}

/*
 *
 *
 */
SmurfAnchor *SConnection::fromAnchor() {
	return fAnchor;
}

/*
 *
 *
 */
void SConnection::setFromAnchor(SmurfAnchor *_from) {
	fAnchor = _from;
}

/*
 *
 *
 */
SmurfAnchor* SConnection::toAnchor() {
	return tAnchor;
}

/*
 *
 *
 */
void SConnection::setToAnchor(SmurfAnchor *_to) {
	tAnchor = _to;
}


/*
 *
 *
 */
vector<float>* SConnection::getLiveData() {
	return liveData;
}

/*
 *
 *
 */
void SConnection::setLiveData(vector<float> *_liveData) {
	liveData = _liveData;
}

/*
 *
 *
 */
bool SConnection::isEnabled() {
	return enabled;
}

/*
 *
 *
 */
void SConnection::setEnabled(bool _status) {
	enabled = _status;
}

/*
 *
 *
 */
void SConnection::toggleEnabled() {
	enabled = enabled ? false : true;
}

/*
 *
 * Basically draw a connection with a given live data feedback
 *
 */
void SConnection::draw(vector<float> *livedata) {
			
	ofxTuioPoint *fromPt = new ofxTuioPoint(fAnchor->getTuio()->getPosition().getX(), fAnchor->getTuio()->getPosition().getY());
	ofxTuioPoint *toPt = new ofxTuioPoint(tAnchor->getTuio()->getPosition().getX(), tAnchor->getTuio()->getPosition().getY());
	
	float fX = fromPt->getX() * ofGetWidth();
	float fY = fromPt->getY() * ofGetHeight();
	float tX = toPt->getX() * ofGetWidth();
	float tY = toPt->getY() * ofGetHeight();
	
	ofxTuioPoint *fnPt = new ofxTuioPoint(fX, fY);
	ofxTuioPoint *tnPt = new ofxTuioPoint(tX, tY);
	
	//ofLine(fX, fY, tX, tY);
	
	glPushMatrix();

	
	glTranslatef(fX, fY, 0.0);
		
	float dx = fX-tX;
	float dy = fY-tY;
	
	float dist = sqrtf(dx*dx+dy*dy);

	glRotatef(180.0-ofRadToDeg(fnPt->getAngle(tnPt)), 0.0, 0.0, 1.0);
	
	ofStyle oldStyle = ofGetStyle();
	
	ofStyle ofStyla = ofStyle();
	ofStyla.lineWidth = 3.0;
	ofStyla.circleResolution = 36;
	ofStyla.smoothing = true;
	ofStyla.blending = true;

	ofSetStyle(ofStyla);
	
	glColor3f(0.3, 0.3, 0.3);
	
	ofLine(0.0, 0.0, dist, 0.0);
	
	
	glColor3f(0.7, 0.7, 0.7);

	ofBeginShape();

	ofVertex(dist - 16.0, -8.0);
	ofVertex(dist -16.0, 8.0);
	ofVertex(dist - 5.0, 0.0);

	ofEndShape(true);


	// drawing live data feedback if any
	// A simple line otherwise
	ofBeginShape();

	ofVertex(0.0, 0.0);

	float incr = dist / livedata->size();
	
	rotate(livedata->rbegin(), livedata->rbegin()+1, livedata->rend());
	
	for (int idx=0; idx<livedata->size(); idx++) {
		if (idx*incr>dist) break;
		
		ofVertex(idx*incr, livedata->at(idx)*(-25));
		ofVertex(idx*incr, livedata->at(idx)*25);
			
		if (idx*incr+incr>dist) break;		
	}
		
	ofVertex(dist, 0.0);
	
	ofEndShape(false);
	
	glPopMatrix();
		
	delete fnPt;
	delete tnPt;
	delete fromPt;
	delete toPt;
	
	ofSetStyle(oldStyle);

	delete &ofStyla;
}

/*
 *
 *
 */
void SConnection::onAdd(ofxOscSender* _oscSender) {
	ofxOscMessage* onAddMsg = new ofxOscMessage();
	
	onAddMsg->setAddress("/smurf/connection/add");
	onAddMsg->addIntArg((int)fromFID());
	onAddMsg->addIntArg((int)toFID());
	onAddMsg->addIntArg(isEnabled()?1:0);
	_oscSender->sendMessage(*onAddMsg);
	
	delete onAddMsg;	
}

/*
 *
 *
 */
void SConnection::onUpdate(ofxOscSender* _oscSender) {
	ofxOscMessage* onUpdateMsg = new ofxOscMessage();
	
	onUpdateMsg->setAddress("/smurf/connection/update");
	onUpdateMsg->addIntArg((int)fromFID());
	onUpdateMsg->addIntArg((int)toFID());
	onUpdateMsg->addIntArg(isEnabled()?1:0);
	
	_oscSender->sendMessage(*onUpdateMsg);
	
	delete onUpdateMsg;
}

/*
 *
 *
 */
void SConnection::onRemove(ofxOscSender* _oscSender) {
	ofxOscMessage* onRemoveMsg = new ofxOscMessage();
	
	onRemoveMsg->setAddress("/smurf/connection/remove");
	onRemoveMsg->addIntArg((int)fromFID());
	onRemoveMsg->addIntArg((int)toFID());
	onRemoveMsg->addIntArg(isEnabled()?1:0);
	
	_oscSender->sendMessage(*onRemoveMsg);
	
	delete onRemoveMsg;
}
