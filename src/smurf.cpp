/*
 *  smurf.cpp
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

#include "smurf.h"
#include "smurfanchor.h"
#include "slot.h"
#include "ofxOsc.h"

/*
Smurf::Smurf(ofxTuioObject *tuioObj, SmurfKind kind) {
	Smurf(tuioObj, kind, SMURF_FUNC_NONE);
}
*/
Smurf::Smurf(ofxTuioObject *tuioObj, SmurfKind kind/*, SmurfFunction function*/) {
	//Smuon();
	slots = vector<Slot*>();
	oscMsgMap = map<SmurfEvt, vector<ofxOscMessage*>*>();

	setTuio(tuioObj);
	setKind(kind);
	setFunction(SMURF_FUNC_NONE);
	setLastWaveUid(-1);

	ofxOscMessage* onEvtMsg = new ofxOscMessage();
	onEvtMsg->setAddress("/smurf/fid/");
	
	addOscMsgOnEvent(EVT_ADD, onEvtMsg);
	addOscMsgOnEvent(EVT_UPDATE, onEvtMsg);
	addOscMsgOnEvent(EVT_REMOVE, onEvtMsg);
	
	liveData = new vector<float>(67, 0);
	
	//
	//-------------------------------------------------
	
//	ofxOscMessage* slotAofOScMsg = new ofxOscMessage();
//	slotAofOScMsg->setAddress("/smurf/fid/slotAction");
//	slotAofOScMsg->addIntArg(tuioObj->getFiducialId());
//	slotAofOScMsg->addIntArg(0);
//	
//	setSlot(_A, PUSH, BOX, slotAofOScMsg);
//	
//	ofxOscMessage* slotBofOScMsg = new ofxOscMessage();
//	slotBofOScMsg->setAddress("/smurf/fid/slotAction");
//	slotBofOScMsg->addIntArg(tuioObj->getFiducialId());
//	slotBofOScMsg->addIntArg(1);
//	
//	setSlot(_B, PUSH, BOX, slotBofOScMsg);
//
//	ofxOscMessage* slotCofOScMsg = new ofxOscMessage();
//	slotCofOScMsg->setAddress("/smurf/fid/slotAction");
//	slotCofOScMsg->addIntArg(tuioObj->getFiducialId());
//	slotCofOScMsg->addIntArg(2);
//	
//	setSlot(_C, PUSH, BOX, slotCofOScMsg);
//	
//	ofxOscMessage* slotDofOScMsg = new ofxOscMessage();
//	slotDofOScMsg->setAddress("/smurf/fid/slotAction");
//	slotDofOScMsg->addIntArg(tuioObj->getFiducialId());
//	slotDofOScMsg->addIntArg(3);
//	
//	setSlot(_D, PUSH, BOX, slotAofOScMsg);
	
	
	animation = PULSE;
	aspect = SMURF_ASPECT_DISC;
}

Smurf::~Smurf(){
	slots.clear();
	oscMsgMap.clear();
}

void Smurf::setAspect(SmurfAspect _aspect) {
	aspect = _aspect;
}

SmurfAspect Smurf::getAspect() {
	return aspect;
}

vector<Slot*> Smurf::getSlots() {
	return slots;
}

void Smurf::addOscMsgOnEvent(SmurfEvt evt, ofxOscMessage* msg) {
	if (oscMsgMap[evt] == NULL) {
		oscMsgMap[evt] = new vector<ofxOscMessage*>();
	}
	oscMsgMap[evt]->push_back(msg);	
}

void Smurf::removeOscMsgOnEvent(SmurfEvt evt, ofxOscMessage* msg) {
	//oscMsgMap[evt]->erase(msg);	
}


void Smurf::setLastWaveUid(int _uid) {
	lastWaveUid = _uid;
}


int Smurf::getLastWaveUid() {
	return lastWaveUid;
}

void Smurf::updateLiveData() {
	//liveData.clear();
	//liveData.push(float(((ofxTuioObject*)getTuio())->getAngleDegrees()/360.0));
	draw();
}

void Smurf::onBeat(ofxOscSender* _sender, SWave *wave) {
	ofxTuioObject *obj = (ofxTuioObject*)getTuio();
	
	ofxOscMessage* onBeatMsg = new ofxOscMessage();
	
	onBeatMsg->setAddress("/smurf/fid/" + ofToString(obj->getFiducialId()) + "/bang");
	onBeatMsg->addFloatArg(obj->getX());
	onBeatMsg->addFloatArg(obj->getY());
	onBeatMsg->addFloatArg(obj->getAngleDegrees()/360.0);
	
	_sender->sendMessage(*onBeatMsg);
				
	delete onBeatMsg;
}

SmurfKind Smurf::getKind() {
	return kind;
}

void Smurf::setKind(SmurfKind _kind) {
	kind = _kind;
}

SmurfFunction Smurf::getFunction(){
	return function;
}

void Smurf::setFunction(SmurfFunction _function) {
	function = _function;
}

vector<float>* Smurf::getLiveData() {
	return liveData;
}

void Smurf::setLiveData(vector<float> *_livedata) {
	liveData = _livedata;
}

void Smurf::pushLiveData(float _idx, float _data) {
	if (liveData != NULL) {
		if (liveData->size()>_idx) {
			(*liveData)[_idx] = _data;
		}
	}
}

void Smurf::onAdd(ofxOscSender *_sender) {
	std::map<SmurfEvt, vector<ofxOscMessage*>*>::const_iterator
    mit (oscMsgMap.begin()),
    mend(oscMsgMap.end());
	for(;mit!=mend;++mit) {
		if (mit->first == EVT_ADD) {
			vector<ofxOscMessage*> *v = (vector<ofxOscMessage*>*) mit->second;
			for (int i=0; i<v->size(); i++ ) {
				ofxOscMessage *msg = (ofxOscMessage *) v->at(i);
				
				ofxOscMessage *copy = new ofxOscMessage();
				copy->copy(*msg);
				copy->clear();
				
				ofxTuioObject *obj = (ofxTuioObject *) getTuio(); 
				if (obj != NULL) {
					copy->setAddress(msg->getAddress()+ofToString(obj->getFiducialId())+"/add");
					copy->addFloatArg(obj->getX());
					copy->addFloatArg(obj->getY());
					copy->addFloatArg(obj->getAngleDegrees()/360.0);
				}
				
				_sender->sendMessage(*copy);
				
				delete copy;
				
				updateLiveData();
			}
			
		}
	}
}

void Smurf::onUpdate(ofxOscSender *_sender) {
	//setBeingUpdated(true);
	std::map<SmurfEvt, vector<ofxOscMessage*>*>::const_iterator
    mit (oscMsgMap.begin()),
    mend(oscMsgMap.end());
	for(;mit!=mend;++mit) {
		if (mit->first == EVT_UPDATE) {
			vector<ofxOscMessage*> *v = (vector<ofxOscMessage*>*) mit->second;
			for (int i=0; i<v->size(); i++ ) {
				ofxOscMessage *msg = (ofxOscMessage *) v->at(i);
				
				ofxOscMessage *copy = new ofxOscMessage();
				copy->copy(*msg);
				copy->clear();
				
				ofxTuioObject *obj = (ofxTuioObject *) getTuio(); 
				if (obj != NULL) {
					copy->setAddress(msg->getAddress()+ofToString(obj->getFiducialId())+"/update");
					copy->addFloatArg(obj->getX());
					copy->addFloatArg(obj->getY());
					copy->addFloatArg(obj->getAngleDegrees()/360.0);
				}
				
				_sender->sendMessage(*copy);
				
				delete copy;
				
				updateLiveData();
			}
		}
	}
}

void Smurf::onRemove(ofxOscSender *_sender) {
	std::map<SmurfEvt, vector<ofxOscMessage*>*>::const_iterator
    mit (oscMsgMap.begin()),
    mend(oscMsgMap.end());
	for(;mit!=mend;++mit) {
		if (mit->first == EVT_REMOVE) {
			vector<ofxOscMessage*> *v = (vector<ofxOscMessage*>*) mit->second;
			for (int i=0; i<v->size(); i++ ) {
				ofxOscMessage *msg = (ofxOscMessage *) v->at(i);
				
				ofxOscMessage *copy = new ofxOscMessage();
				copy->copy(*msg);
				copy->clear();
				
				ofxTuioObject *obj = (ofxTuioObject *) getTuio(); 
				if (obj != NULL) {
					copy->setAddress(msg->getAddress()+ofToString(obj->getFiducialId())+"/remove");
					copy->addFloatArg(obj->getX());
					copy->addFloatArg(obj->getY());
					copy->addFloatArg(obj->getAngleDegrees()/360.0);
				}
				
				_sender->sendMessage(*copy);
				
				delete copy;
				
				updateLiveData();
			}
		}
	}
}

std::map<SmurfEvt, vector<ofxOscMessage*>*> Smurf::getOscMsgMap() {
	return oscMsgMap;
}


void Smurf::setSlot(SlotPosition position, SlotKind kind, SlotVisual visual, ofxOscMessage* oscMsg) {
	Slot *slot = new Slot(position, kind, visual);
	slot->getOscMessages()->push_back(oscMsg);
	slots.push_back(slot);
}

void Smurf::setSlot(SlotPosition position, SlotKind kind, SlotVisual visual, vector<ofxOscMessage*>* oscMsgVector) {
	Slot *slot = new Slot(position, kind, visual);
	for (int i=0; i<oscMsgVector->size(); i++ ) {
		ofxOscMessage* msg = oscMsgVector->at(i);
		slot->getOscMessages()->push_back(msg);
	}
	slots.push_back(slot);
}

void Smurf::draw() {
	ofSetCircleResolution(100);
	ofxTuioObject *blob = (ofxTuioObject*) getTuio();
	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glTranslatef(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 0.0);
	
	float angle = blob->getAngleDegrees();
	
	glRotatef(angle, 0.0, 0.0, 1.0);

	ofFill();
	ofEnableAlphaBlending();	// turn on alpha blending
	ofColor color = getFG();
	ofSetColor(color.r, color.g, color.b, 255);
	
	if (aspect == SMURF_ASPECT_TRANSPARENT) {
		// draw nothing
	} else if (aspect == SMURF_ASPECT_DISC) {
		ofCircle(0.0, 0.0, getRadius()-7);
	} else if (aspect == SMURF_ASPECT_SQUARE) {
		ofRect(-getRadius()/2-3, -getRadius()/2-3, getRadius()+6, getRadius()+6);
	} else if (aspect == SMURF_ASPECT_STAR) {
		ofCircle(0.0, 0.0, getRadius()-7);
	} else if (aspect == SMURF_ASPECT_TRIANGLE) {
//		ofRect(-getRadius()/2-3, -getRadius()/2-3, getRadius()+6, getRadius()+6);
		ofCircle(0.0, 0.0, getRadius()-5);
//		ofLine(cosf(120.0)*20, sinf(120.0)*20, 20, 0.0);
//		ofLine(20, 0.0, cosf(240.0)*20, sinf(240.0)*20);
//		ofLine(cosf(240.0)*20, sinf(240.0)*20, cosf(120.0)*20, sinf(120.0)*20);
	} else {
		ofCircle(0.0, 0.0, getRadius()-7);
	}
	
	ofDisableAlphaBlending();	// turn off alpha blending
	
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 0.0);
	
	
	ofEnableAlphaBlending();	// turn on alpha blending

	ofSetLineWidth(1.0);
	ofSetColor(200, 200, 200, 60);
	
	ofFill();
	ofSetColor(200, 200, 200, 125);
	
		
	// FUNCTION
	// --------------------------------
	if (getFunction() == SMURF_FUNC_KNOB) {
		float ratio = (angle/360.0);
		float steps = ratio*200.0;
		
		for (float cpt=0; cpt<steps;cpt++) {
			
			ofCircle(cosf(ofDegToRad(cpt*1.8+90.0))*getRadius(), sinf(ofDegToRad(cpt*1.8+90.0))*getRadius(), 2);
		}
		
		ofNoFill();
		
		glColor3f(0.9,0.9,0.9);

		ofCircle(cosf(ofDegToRad(steps*1.8+90.0))*getRadius(), sinf(ofDegToRad(steps*1.8+90.0))*getRadius(), 4);
		glColor3f(0.7,0.6,1.0);

		ofCircle(cosf(ofDegToRad(steps*1.8+90.0))*getRadius(), sinf(ofDegToRad(steps*1.8+90.0))*getRadius(), 4);
	
		glColor3f(0.4,0.3,1.0);
		ofCircle(cosf(ofDegToRad(steps*1.8+90.0))*getRadius(), sinf(ofDegToRad(steps*1.8+90.0))*getRadius(), 5);
	}
	
//	// On Smurf Selection
//	if (isSelected()) {
//		ofPushStyle();
//		glColor3f(1.0,0.0,0.0);
//		ofSetLineWidth(3.0);
//		ofCircle(0, 0, getRadius()+5);
//		ofPopStyle();
//	}
	
	glPopMatrix();
	
	ofSetColor(200, 200, 200, 125);

	ofSetLineWidth(1.0);
	
	glColor3f(1.0,1.0,1.0);
	
	
	ofNoFill();

	if (isLabelVisible()) {
		string str = ofToString((int)(blob->getFiducialId()));
		ofDrawBitmapString(str, blob->getX()*ofGetWidth()-10.0, blob->getY()*ofGetHeight()+25.0);
	}
	
	if (isProximaVisible() /*&& isBeingUpdated()*/) {
		ofSetLineWidth(0.5);
		ofSetColor(220, 220, 220, 65);
		
		int angle=0;
		for (int i=0; i<36; i++ ) {			
			float newX = blob->getX()*ofGetWidth() + cosf(ofDegToRad(angle))*getProxima(); 
			float newY = blob->getY()*ofGetHeight() + sinf(ofDegToRad(angle))*getProxima(); 
			ofLine(newX, newY, newX-1, newY);
			angle += 10;
		}
		glColor3f(1.0,1.0,1.0);
	}
	
	if (dynamic_cast<SmurfAnchor*>(this) == NULL) {
	

		for (int i=0; i<slots.size(); i++ ) {
			Slot *slot = slots.at(i);
		
			float newX = blob->getX() + cosf(ofDegToRad(slot->getPosition()))*57.0/ofGetWidth(); 
			float newY = blob->getY() + sinf(ofDegToRad(slot->getPosition()))*57.0/ofGetHeight(); 
		
			slot->getTuio()->update(newX, newY, 0.0, 0.0, 0.0);
		
			slot->draw();
		}
	}

	//setBeingUpdated(false);
	
}

bool Smurf::isBeingUpdated(){
	return beingUpdated;
}

void Smurf::setBeingUpdated(bool _status){
	beingUpdated = _status;
}

void Smurf::toggleBeingUpdated(){
	beingUpdated = beingUpdated ? false : true;
}
