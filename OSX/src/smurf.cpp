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
	onBeatMsg->addFloatArg(getPearl()->getLevel());
	
	_sender->sendMessage(*onBeatMsg);
	
	delete onBeatMsg;
}

void Smurf::onTic(ofxOscSender* _sender) {
	ofxTuioObject *obj = (ofxTuioObject*)getTuio();
	
	ofxOscMessage* onTicMsg = new ofxOscMessage();
	
	onTicMsg->setAddress("/smurf/fid/" + ofToString(obj->getFiducialId()) + "/tic");
	onTicMsg->addFloatArg(obj->getX());
	onTicMsg->addFloatArg(obj->getY());
	onTicMsg->addFloatArg(obj->getAngleDegrees()/360.0);
	
	_sender->sendMessage(*onTicMsg);
	
	delete onTicMsg;
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

void Smurf::setLabel(string _label) {
	label = _label;
}

string Smurf::getLabel() {
	return label;
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
	start();
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
					copy->addFloatArg(getPearl()->getLevel());
				}
				
				_sender->sendMessage(*copy);
				
				delete copy;
				
				updateLiveData();
			}
		}
	}
}

void Smurf::onRemove(ofxOscSender *_sender) {
	stop();
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
	Smurf::draw(NULL);
}

void Smurf::draw(ofTrueTypeFont *_font) {
	ofStyle oldStyle = ofGetStyle();
	
	ofStyle ofStyla = ofStyle();
	ofStyla.lineWidth = 3.0;
	ofStyla.circleResolution = 500;
	ofStyla.smoothing = true;
	ofStyla.blending = true;
	
	ofSetStyle(ofStyla);
		
	ofxTuioObject *blob = (ofxTuioObject*) getTuio();
	ofSetColor(255, 0, 0);
	
	
	ofPushMatrix();
	ofTranslate(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 0.0);
	
	
	ofEnableAlphaBlending();	// turn on alpha blending
	
	ofSetLineWidth(1.0);
	
	ofFill();
	ofSetColor(200, 200, 200, 125);
	
	float oldX = blob->getX() * ofGetWidth();
	float oldY = blob->getY() * ofGetHeight();

	
	//	// On Smurf Selection
	//	if (isSelected()) {
	//		ofPushStyle();
	//      ofSetColor(255, 255, 255);
	//		ofSetLineWidth(3.0);
	//		ofCircle(0, 0, getRadius()+5);
	//		ofPopStyle();
	//	}
	
	
	
	// FUNCTION
	// --------------------------------
	if (getFunction() == SMURF_FUNC_KNOB) {
		float angle = blob->getAngleDegrees();
		float ratio = angle / 360.0;
		float steps = ratio * 200.0;
		float incrRad = ofDegToRad(steps * 1.8 + 90.0);
		
		ofPushMatrix();
		ofFill();
		ofEnableSmoothing();
		ofSetLineWidth(4.0);
		ofBeginShape();
		for (float cpt=0; cpt<steps;cpt++) {
			ofVertex(
				cosf(ofDegToRad(cpt * 1.8 + 90.0)) * getRadius(), 
				sinf(ofDegToRad(cpt * 1.8 + 90.0)) * getRadius()
			);
		}
		ofVertex(0.0, 0.0);
		
		ofEndShape(false);
		
		ofSetLineWidth(5.0);
		
		ofSetColor(255, 0, 0);
		
		ofCircle(cosf(incrRad)*getRadius(), sinf(incrRad)*getRadius(), 5);
		
		ofDisableSmoothing();
		
		ofPopMatrix();
	}
	
	ofPopMatrix();	
	
	ofPushMatrix();
	
	ofTranslate(
		blob->getX() * ofGetWidth(), 
		blob->getY() * ofGetHeight(), 
		0.0
	);
	
	float angle = blob->getAngleDegrees();
	float angleDeg = step * 3.6;
	float angleDeg2 = step * 3.6 + 180.0;
	float factor = cosf(ofDegToRad(angleDeg));
	factor *= factor > 0 ? 1 : -1; 
	float factor2 = cosf(ofDegToRad(angleDeg2));
	factor2 *= factor2 > 0 ? 1 : -1; 
	float radius = getRadius();
	float innerRadius = radius - 7;
	float outerRadius = radius + 6;
	
	ofRotate(angle, 0.0, 0.0, 1.0);

	ofFill();
	ofEnableAlphaBlending();	// turn on alpha blending
	ofEnableSmoothing();
	ofColor color = getFG();
	
	ofSetColor(color.r, color.g, color.b, 150 + 100 * factor2);
	
	if (aspect == SMURF_ASPECT_TRANSPARENT) {
		// draw nothing
	} else if (aspect == SMURF_ASPECT_DISC) {
		ofCircle(0.0, 0.0, getRadius()-7);
	} else if (aspect == SMURF_ASPECT_SQUARE) {
		ofRect(-getRadius()/2-3, -getRadius()/2-3, outerRadius, outerRadius);
	} else if (aspect == SMURF_ASPECT_HEXAGON) {
		ofPushMatrix();
		ofFill();
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		ofBeginShape();		
		for (float i=0.0;i<6.0;i+=1.0) {
			float angle = ofDegToRad(i*60.0);
			ofVertex(innerRadius*cosf(angle), innerRadius*sinf(angle));
		}
		ofEndShape(true);
		ofPopMatrix();
	} else if (aspect == SMURF_ASPECT_PENTAGON) {
		ofPushMatrix();
		ofFill();
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		ofBeginShape();		
		for (float i=0.0;i<5.0;i+=1.0) {
			float angle = ofDegToRad(i*72.0);
			ofVertex(innerRadius*cosf(angle), innerRadius*sinf(angle));
		}
		ofEndShape(true);
		ofPopMatrix();
	}  else if (aspect == SMURF_ASPECT_HEIGHT_STAR) {
		ofPushMatrix();
		ofFill();
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		ofBeginShape();		
		for (int i=0;i<16;i+=1) {
			int remaining = i%2;
			float factor = (remaining==0)?1.0:0.75;
			float dist = innerRadius*factor;
			float angle = ofDegToRad(i*22.5);
			ofVertex(dist*cosf(angle), dist*sinf(angle));
		}
		ofEndShape(true);
		ofPopMatrix();
	} else {
		ofCircle(0.0, 0.0, innerRadius);
	}
	
	ofDisableAlphaBlending();	// turn off alpha blending
	
	ofPopMatrix();
	
	
	ofSetColor(200, 200, 200, 125);

	ofSetLineWidth(1.0);
	
	ofSetColor(255, 255, 255);
	
	ofNoFill();

	if (isLabelVisible()) {
		string str = ofToString((int)blob->getFiducialId());
		float angle0 = ofDegToRad(angleDeg);
		float angle1 = ofDegToRad(angleDeg+120);
		float angle2 = ofDegToRad(angleDeg+240);
		float newX0 = oldX + cosf(angle0) * innerRadius; 
		float newY0 = oldY + sinf(angle0) * innerRadius; 
		float newX1 = oldX + cosf(angle1) * innerRadius; 
		float newY1 = oldY + sinf(angle1) * innerRadius; 
		float newX2 = oldX + cosf(angle2) * innerRadius; 
		float newY2 = oldY + sinf(angle2) * innerRadius; 
		if (_font != NULL && _font->bLoadedOk) {
			ofSetColor(getFG().r, getFG().g, getFG().b, 60 + 100.0 * factor * factor);

			ofPushMatrix();
				ofTranslate(newX0, newY0,0);
				ofRotate(angleDeg-90.0, 0, 0, 1);
				ofRectangle box0 = _font->getStringBoundingBox("#"+str, 0, 0);
				_font->drawString("#"+str, -box0.width/2, box0.height);
			ofPopMatrix();
			ofPushMatrix();
				ofTranslate(newX1, newY1,0);
				ofRotate(angleDeg+30.0, 0, 0, 1);
				ofRectangle box1 = _font->getStringBoundingBox(getLabel(), 0, 0);
				_font->drawString(getLabel(), -box1.width/2, box1.height);
			ofPopMatrix();
			ofPushMatrix();
				ofTranslate(newX2, newY2,0);
				ofRotate(angleDeg+150.0, 0, 0, 1);
				string val = "[" + ofToString(angle/3.6, 0) + "]";
				ofRectangle box2 = _font->getStringBoundingBox(val, 0, 0);
				_font->drawString(val, -box2.width/2, box2.height);
			ofPopMatrix();
		} else {
			ofDrawBitmapString(str, newX0, newY0);
		}
	}
	
	if (isProximaVisible() /*&& isBeingUpdated()*/) {
		ofSetLineWidth(0.5);
		ofSetColor(220, 220, 220, 65);
		
		int angle=0;
		for (int i=0; i<36; i++ ) {	
			float radAngle = ofDegToRad(angle);
			float newX = oldX + cosf(radAngle)*getProxima(); 
			float newY = oldY + sinf(radAngle)*getProxima(); 
			ofLine(newX, newY, newX-1, newY);
			angle += 10;
		}
		ofSetColor(255, 255, 255);
	}
	
	if (dynamic_cast<SmurfAnchor*>(this) == NULL) {
		for (int i=0; i<slots.size(); i++ ) {
			Slot *slot = slots.at(i);
		
			float pos = slot->getOrderFromSlotPosition();
			float slotAngle = (pos / 16.0) * 360.0;
			float radAngle = ofDegToRad(slotAngle);
			
			float newX = blob->getX() + cosf(radAngle) * (innerRadius / ofGetWidth()); 
			float newY = blob->getY() + sinf(radAngle) * (innerRadius / ofGetHeight()); 
		
			((ofxTuioObject*)slot->getTuio())->update(newX, newY, slotAngle, 0.0, 0.0, 0.0, 0.0, 0.0);
			
			slot->draw();
		}
	}
	ofDisableSmoothing();
	//setBeingUpdated(false);
	
	
	ofPushMatrix();
	ofFill();
	ofSetColor(200, 200, 200);
	
	// Draw pearl
	float lvl = getPearl()->getLevel();
	
	float newX = blob->getX() + outerRadius*cosf(lvl*2*pi)/ofGetWidth(); 
	float newY = blob->getY() + outerRadius*sinf(lvl*2*pi)/ofGetHeight(); 

	getPearl()->getTuio()->update(newX, newY, 0.0, 0.0, 0.0);
	getPearl()->draw();
	
	ofPopMatrix();
	
	if (getNature() == "SAMPLER") {		
		ofxTuioObject *tuio = (ofxTuioObject*)getTuio();
						
		float angleRad = ofDegToRad(sampler % 360);
		float x = tuio->getPosition().getX()*ofGetWidth();
		float y = tuio->getPosition().getY()*ofGetHeight();
		
		ofPushMatrix();
			ofEnableAlphaBlending();	// turn on alpha blending
			for (int i=0; i<10; i++) {
				int alpha = i * 22;

				ofSetColor(getFG().r, getFG().g, getFG().b, alpha);
				float dX = cosf(angleRad+(0.12*i));
				float dY = sinf(angleRad+(0.12*i));
				float newX = x + dX * (getRadius() + 5.0);
				float newY = y + dY * (getRadius() + 5.0);
				ofCircle(
					newX,
					newY,
					8*(i/10.0)
				);
			}
		ofPopMatrix();
	}
	
	ofSetStyle(oldStyle);
	
	delete &ofStyla;
}

string Smurf::getNature() {
	return nature;
}

void Smurf::setNature(string _nature) {
	nature = _nature;
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

Pearl* Smurf::getPearl(){
	return pearl;
}

long Smurf::getStep() {
	return step;
}

void Smurf::setStep(long _step) {
	step = _step;
}

float Smurf::getSpeed() {
	return speed;
}

void Smurf::setSpeed(float _speed) {
	speed = _speed;
}

///////////////////
// PEARL stuff
///////////////////

void Pearl::setLevel(float _lvl) {
	level = _lvl;
}

float Pearl::getLevel() {
	return level;
}

ofxTuioContainer* Pearl::getTuio() {
	return tuioObj;
}

void Pearl::draw() {
	//ofCircle(tuioObj->getX()*ofGetWidth(), tuioObj->getY()*ofGetHeight(), 7.0);
}

void Pearl::setParent(Smurfer* _smurf) {
	parent = _smurf;
}

Smurfer* Pearl::getParent() {
	return parent;
}
