/*
 *  smurfbrain.cpp
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

#include "smurfbrain.h"
#include "fmftypes.h"

#include <fstream>

#define MIN_GESTURE_POINTS_THRESHOLD 15

SmurfBrain::SmurfBrain(int _bpm) {
	utils = new SmurfUtils();
	//connectionUtils = new ConnectionsUtils();
	selection = new vector<Smuon*>();
#ifdef TARGET_OS_MAC
	gesture = true;
#endif
	connectionsAllowed = false;

	initBeat(_bpm);
}

void SmurfBrain::initBeat(int bpm) {	
	cout << "init the beat thread @ tempo " << beat.bpm << "\n";
	setFingers(new vector<SmurFinger*>());
	setSmurfs(new vector<Smurf*>());
#ifdef TARGET_OS_MAC
	setGestures(new SmurfGestures());
#endif
	setConnections(new vector<SConnection*>());
	beat.setBPM(bpm);
	beat.start();
}


void SmurfBrain::handleBeat(int waveId, vector<SWave*> *waves) {
	int ret = beat.bang();
	if(ret != -1) {
		(*waves).push_back(new SWave(-1, waveId, ofGetWidth()/2, ofGetHeight()/2, 1000));	
		
		ofxOscMessage* onBeatMsg = new ofxOscMessage();
		onBeatMsg->setAddress("/smurf/beat");
		onBeatMsg->addIntArg(getBPM());
		
		getOscSender()->sendMessage(*onBeatMsg);
		
		delete onBeatMsg;
	}
}

void SmurfBrain::handleOscReceive() {
	while( getOscReceiver()->hasWaitingMessages() )
	{
		ofxOscMessage m;
		getOscReceiver()->getNextMessage( &m );
		
		if ( m.getAddress() == std::string("/smurf/wiimote") )
		{
			float fid = m.getArgAsFloat(0);
			float x = m.getArgAsFloat(1);
			float y = m.getArgAsFloat(2);
			float z = m.getArgAsFloat(3);
			int padX = m.getArgAsInt32(4);
			int padY = m.getArgAsInt32(5);
			int button1 = m.getArgAsInt32(4);
			int button2 = m.getArgAsInt32(5);
			
			
			if (!isCursorAlive(-111)) {
				//
				// To be replaced by some ofEvent/ofListener based stuff here
				//
				ofxTuioCursor *tuioCursor = new ofxTuioCursor(-111, fid, x, y);
				SmurFinger *finger = new SmurFinger();
				finger->setTuio(tuioCursor);
				finger->addPoint(tuioCursor->getPosition());			
				getFingers()->push_back(finger);	
			} else {
				SmurFinger *finger = findCursor(-111);
				delete finger->getTuio();
				finger->setTuio(new ofxTuioCursor(-111, fid, x, y));
			}

		} else if (m.getAddress().find(std::string("/smurf/fid"))!=string::npos) {
			int npos = m.getAddress().find(std::string("/smurf/fid"));
			std::string fidAndCommand = m.getAddress().substr(11);
			std::string fid = fidAndCommand.substr(0,1);
			
			if (m.getAddress().find(std::string("/live")) != string::npos) {
				int nbArgs = m.getNumArgs();				
								
				Smurf *s = findSmurf(strtof(fid.c_str(), NULL));
				if (s != NULL) {
					for (int i=0;i<nbArgs;i++) {
						s->pushLiveData(i, m.getArgAsFloat(i));
					}
					s->draw();
				}
			}
		}
	}
}

// ACCESSORS
//--------------------------------------

void SmurfBrain::setSmurfs(vector<Smurf*> *_smurfs) {
	smurfs = _smurfs;
}

void SmurfBrain::setFingers(vector<SmurFinger*> *_fingers) {
	fingers = _fingers;
}

void SmurfBrain::setConnections(vector<SConnection*> *_connections) {
	connections = _connections;
}

vector<Smurf*> * SmurfBrain::getSmurfs() {
	return smurfs;
}

vector<SmurFinger*> * SmurfBrain::getFingers() {
	return fingers;
}

vector<SConnection*> * SmurfBrain::getConnections() {
	return connections;
}

void SmurfBrain::setBPM(int _bpm) {
	beat.setBPM(_bpm);
}

int SmurfBrain::getBPM() {
	beat.getBPM();
}

// OSC sender handling
//---------------------------------------

void SmurfBrain::setOscSender(ofxOscSender *_sender) {
	sender = _sender;
}

ofxOscSender* SmurfBrain::getOscSender() {
	return sender;
}

// OSC receiver handling
//---------------------------------------

void SmurfBrain::setOscReceiver(ofxOscReceiver *_receiver) {
	receiver = _receiver;
}

ofxOscReceiver* SmurfBrain::getOscReceiver() {
	return receiver;
}

// Configuration
// ---------------------------------------

void SmurfBrain::setSmurfCfg(SmurfCfg *_cfg) {
	config = _cfg;
}

SmurfCfg* SmurfBrain::getSmurfCfg() {
	return config;
}

#ifdef TARGET_OS_MAC

// Gestures
// ---------------------------

bool SmurfBrain::isGesture() {
	return gesture;
}

void SmurfBrain::toggleGesture() {
	gesture=(gesture==true?false:true);
}

void SmurfBrain::setGestures(SmurfGestures *_gesturesEngine) {
	gesturesEngine = _gesturesEngine;
}

SmurfGestures * SmurfBrain::getGestures() {
	return gesturesEngine;
}

#endif

// Connections
// ----------------------------
bool SmurfBrain::isConnectionModeOn() {
	return connectionsAllowed;
}

void SmurfBrain::toggleConnectionMode() {
	connectionsAllowed=(connectionsAllowed==true?false:true);
}

//void SmurfBrain::handleGesture(Smuon* smuon, SmurfGestureClassification _gestureClassification) {
//	if (!isGesture()) return;
//	if (smuon == NULL) return;
//	
//	Smurf *closer = utils->getCloserSmurfWithinGivenRadius(getSmurfs(), getFingers(), smuon->getTuio(), 0.08f);
//	
//	if (_gestureClassification == GESTURE_SELECTION) {
//		handleSimpleSelection(closer);
//	} else if (_gestureClassification == GESTURE_MULTIPLE_SELECTION) {
//		// Not supported yet
//	} else if (_gestureClassification == GESTURE_CREATE_VIRTUAL_SMURF) {
//		// Not supported yet
//		// Will add DAC support later on 
//		//handleCreateNonTangibleSmurf(smuon, SMURF_KIND_VIRTUAL);
//	} else if (_gestureClassification == GESTURE_CREATE_SIN_FREQ_LINK) {
//		handleCreateLinkInitial(smuon, closer, CONNECTION_SIN_FREQ);
//	} else if ( _gestureClassification == GESTURE_CREATE_SQUARE_FREQ_LINK) {
//		handleCreateLinkInitial(smuon, closer, CONNECTION_SQUARE_FREQ);
//	} else if ( _gestureClassification == GESTURE_CREATE_TRIANGLE_FREQ_LINK) {
//		handleCreateLinkInitial(smuon, closer, CONNECTION_TRIANGLE_FREQ);
//	}
//}

void SmurfBrain::handleSimpleSelection(Smurf* _smurf) {
	if (_smurf != NULL) {
		bool status = _smurf->isSelected()?false:true;
		_smurf->setSelected(status);
	}
}

void SmurfBrain::handleMultipleSelection(vector<Smurf*> _smuon) {
	// Not implemented yet !!!
}

SConnection* SmurfBrain::createConnection(Smuon* smuon, float fromID, float toID, SConnectionVisual kind) {
	SmurfAnchor *from = utils->createSmurfAnchor(findSmurf(fromID), fromID, ANCHOR_KIND_OUTPUT);
	from->setKind(SMURF_KIND_ANCHOR);
	
	SmurfAnchor *to = utils->createSmurfAnchor(findSmurf(toID), toID, ANCHOR_KIND_INPUT);
	to->setKind(SMURF_KIND_ANCHOR);

	smurfs->push_back(from);
	smurfs->push_back(to);
	
	SConnection *connection = new SConnection(from, to, kind);
	connection->setFromAnchor(from);
	connection->setToAnchor(to);
	connection->setConnectionVisual(kind);
	connection->setConnectionKind(CONNECT_UNKNOWN);
	
	return connection;
}

void SmurfBrain::handleCreateLinkInitial(Smuon* smuon, Smurf* _smurf, SConnectionVisual kind) {
	if (_smurf == NULL) return; // NO from Smurf matched
	if (_smurf->getKind() == SMURF_KIND_HANDLE) return;
	if (_smurf->getKind() == SMURF_KIND_ANCHOR) return;
	
	Smurf *connectionHandle = utils->createAtypicalSmurf(smuon, SMURF_KIND_HANDLE);
	if (connectionHandle != NULL) {
		smurfs->push_back(connectionHandle);
	} else {
		return;
	}
	
	if (_smurf->getTuio() != NULL && connectionHandle->getTuio() != NULL) {
		SConnection *connection = createConnection(smuon, _smurf->getTuio()->getSessionId(), connectionHandle->getTuio()->getSessionId(), kind);

		if (connection != NULL) {
			connections->push_back(connection);
		}
	}
}

void SmurfBrain::handleCreateNonTangibleSmurf(Smuon* smuon, SmurfKind kind) {
	Smurf *atypicalSmurf = utils->createAtypicalSmurf(smuon, kind);
	if (atypicalSmurf != NULL) {
		smurfs->push_back(atypicalSmurf);
	}
}

// Selection && DND
//-----------------


// SmurfUtils
//---------------------
SmurfUtils* SmurfBrain::getSmurfUtils() {
	return utils;
}


// SVG
//----
void SmurfBrain::loadSVG() {
}

void SmurfBrain::loadGestures() { // gesture.models file
	
	int path_size = 1024;
	char* path = new char[path_size];   
	path = getcwd(path, path_size);
	
#ifdef TARGET_OS_MAC
	const char* gesturesFilePath = strcat(path, "/../../../data/gesture.models");
#elif TARGET_OS_UNIX
	const char* gesturesFilePath = strcat(path, "/data/gesture.models");
#elif TARGET_OS_WIN32
	const char* gesturesFilePath = strcat(path, "/data/gesture.models");
#endif
	
#ifdef TARGET_OS_MAC
	
	std::ifstream in(gesturesFilePath, std::ios::binary);
	
	if(in.is_open()) {
		getGestures()->classification->load(in);	
	}
	
	in.close();
#endif
}


// TUIO messages Handling
//---------------------------------------

void SmurfBrain::markSelection(SmurFinger* finger, vector<Smurf*> *smurfs) {
	for (int i=0; i<smurfs->size(); i++) {
		Smurf *smurf = smurfs->at(i);
		ofxTuioObject *tuio = (ofxTuioObject*) smurf->getTuio();
		for (int j=0;j<smurf->getSlots().size(); j++) {
			Slot* slot = smurf->getSlots().at(j);
			float dist = finger->getTuio()->getDistance(slot->getTuio())/50;
			if (dist < 0.0002) {
				if (slot->getKind() == TOGGLE) {
					slot->setSelected(slot->isSelected()==false?true:false);
				} else if (slot->getKind() == PUSH) {
					// Special fx ?
				}
				for (int i=0; i<slot->getOscMessages()->size(); i++) {
					ofxOscMessage *msg = slot->getOscMessages()->at(i);
					
					ofxOscMessage *copy = new ofxOscMessage();
					copy->copy(*msg);
					copy->clear();
					copy->setAddress(msg->getAddress());
					copy->addIntArg(tuio->getFiducialId());
					copy->addIntArg(slot->getOrderFromSlotPosition());
					copy->addFloatArg(tuio->getX());
					copy->addFloatArg(tuio->getY());
					copy->addFloatArg(tuio->getAngleDegrees());
					
					getOscSender()->sendMessage(*copy);
					
					delete copy;
				}
			}
		}
	}
}

bool SmurfBrain::isCursorAlive(SmurFinger *_finger) {
	return findCursor(_finger->getTuio()->getSessionId()) != NULL;
}

SmurFinger* SmurfBrain::findCursor(float sessionId) {
	for (int i=0; i<fingers->size(); i++) {
		if (fingers->at(i)->getTuio()->getSessionId() == sessionId) {
			return fingers->at(i);
		}
	}
	return NULL;
}

Smurf* SmurfBrain::findSmurf(float sessionId) {
	Smurf *smurf = NULL;
	for (int i=0; i<smurfs->size(); i++) {
		smurf = smurfs->at(i);
		if (smurf->getTuio()->getSessionId() == sessionId) {
			return smurf;
		}
	}
	return smurf;
}


bool SmurfBrain::isCursorAlive(float _sessionId) {
	return findCursor(_sessionId) != NULL;
}

Smurf* SmurfBrain::findSmurfGettingDraggedIfAny(float _sessionId) {
	for (int i=0; i<smurfs->size(); i++) {
		if (smurfs->at(i)->getDragging() == _sessionId) {
			return smurfs->at(i);
		}
	}
	return NULL;
}
				
// Cursor Add
void SmurfBrain::handleCursorAdd(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor) {
	bool absent = true;
	SmurFinger *finger;
	for (int i=0; i<fingers->size(); i++) {
		finger = fingers->at(i);
		if (finger != NULL && finger->getTuio() != NULL) {
			if (finger->getTuio()->getSessionId() == tuioCursor.getSessionId()) {
				absent = false;
				break;
			}
		}
	}
	if (!isCursorAlive(tuioCursor.getSessionId())) {
		finger = new SmurFinger();
		finger->setTuio(&tuioCursor);
		fingers->push_back(finger);		
		finger->addPoint(tuioCursor.getPosition());
	}
	finger->onAdd(getOscSender());
	
	handleSelection(finger);
}

void SmurfBrain::removeNoMoreValidConnections(Smurf *_smurf) {	
	if (_smurf == NULL) return;
	
	vector<SConnection*>::iterator it;
	for (it = connections->begin(); it != connections->end(); it++) {
		SConnection* connection = *it;
		if (connection != NULL) {
			if (connection->fromAnchor() == NULL || connection->toAnchor() == NULL) {
				delete(connection);
				it = connections->erase(it);
				connection = NULL;			
			} else if (connection->fromID() == _smurf->getTuio()->getSessionId() || connection->toID() == _smurf->getTuio()->getSessionId()) {
				if (connection->fromAnchor() != NULL) {
					if (connection->fromAnchor()->getTuio() != NULL) {
						deleteSmurf(connection->fromAnchor()->getTuio()->getSessionId());
					}
				}
				if (connection->toAnchor() != NULL) {
					if (connection->toAnchor()->getTuio() != NULL) {
						deleteSmurf(connection->toAnchor()->getTuio()->getSessionId());
					}
				}
				delete connection;
				it = connections->erase(it);
				if (it == connections->end()) {
					return;
				}
				connection = NULL;
			}
		}
	}
}

void SmurfBrain::deleteSmurf(float sid) {
	vector<Smurf*>::iterator it;
	for (it = smurfs->begin(); it != smurfs->end(); it++) {
		Smurf *smurf = *it;
		if (smurf != NULL) {
			ofxTuioObject *tuio = (ofxTuioObject*) smurf->getTuio();
			if (tuio != NULL && sid == tuio->getSessionId()) {
				smurf->onRemove(getOscSender());

				delete smurf;
				smurfs->erase(it);
				smurf = NULL;
				break;
			}
		}
	}
}

void SmurfBrain::handleSelection(SmurFinger *_finger) {
	if (_finger == NULL) return;

	for (int i=0; i<smurfs->size(); i++) {
		Smurf *smurf = smurfs->at(i);
		ofxTuioContainer *target = smurf->getTuio();
		if (target != NULL && target->getDistance(_finger->getTuio()) < 0.03 && !smurf->isAlreadyDragging()) {
			smurf->setDragging(_finger->getTuio()->getSessionId());
			smurf->toggleSelected();
		}
	}	
}

Smurf* SmurfBrain::evalIfTargetIsDropCompatible(Smurf* dragged) {
	vector<Smurf*>::iterator it;
	if (dragged->getKind() == SMURF_KIND_HANDLE) {
		for (it = smurfs->begin(); it != smurfs->end(); it++) {
			Smurf *smurf = *it;
			if (smurf != NULL) {
				ofxTuioContainer *target = smurf->getTuio();
				if (target != NULL) {
					if (dragged->getTuio() != NULL) {
						if (target->getDistance(dragged->getTuio()) < 0.03) {
							if (smurf->getKind() != SMURF_KIND_HANDLE) {
								return smurf;
							}
						}
					}
				}
			}
		}
	}
	return NULL; 
}

void SmurfBrain::doConnectToTargetIfAnyValidConnection(Smurf *dragged, Smurf *target) {
	for (int i=0; i<connections->size(); i++) {
		SConnection* connection = connections->at(i);
		if (connection != NULL) {
			float toID = connection->toID();
			if (dragged->getTuio() != NULL) {
				if (toID == dragged->getTuio()->getSessionId()) {
					if (target != NULL) {
						connection->setToID(target->getTuio()->getSessionId());
						deleteSmurf(dragged->getTuio()->getSessionId());
					}
				}
			}
		}
	}
}

bool SmurfBrain::areAlreadyConnected(Smurf *from, Smurf *to) {
	if (from != NULL && to != NULL) { 
		for (int i=0; i<connections->size(); i++) {
			SConnection* connection = connections->at(i);
			if (from->getTuio() != NULL && to->getTuio() != NULL) {
				if (to->getTuio()->getSessionId() == from->getTuio()->getSessionId()) {
					return true;
				} else if (
					connection->toID() == to->getTuio()->getSessionId() && 
					connection->fromID() == from->getTuio()->getSessionId()
				) {
					return true;
				} else if (
					connection->toID() == from->getTuio()->getSessionId() && 
					connection->fromID() == to->getTuio()->getSessionId()
				) {
					return true;
				} 
			}
		}
	}
	return false;
}


void SmurfBrain::evalConnectivityToOtherSmurfsOnRangeIfAny(Smurf *from) {
	if (from == NULL || from->getTuio() == NULL) return;
	if (dynamic_cast<SmurfAnchor*> (from)!= NULL) return;
	
	if (from->getKind() == SMURF_KIND_TANGIBLE) {
		for (int i=0; i<smurfs->size(); i++) {
			Smurf *to = smurfs->at(i);
			if (!(dynamic_cast<SmurfAnchor*> (to)!= NULL) && to->getKind() == SMURF_KIND_TANGIBLE) {
				ofxTuioContainer *target = to->getTuio();
		
				if (target != NULL) {
					ofxTuioPoint *fromPt = new ofxTuioPoint(from->getTuio()->getPosition().getX(), from->getTuio()->getPosition().getY());
					ofxTuioPoint *toPt = new ofxTuioPoint(to->getTuio()->getPosition().getX(), to->getTuio()->getPosition().getY());
		
					float fX = fromPt->getX() * ofGetWidth();
					float fY = fromPt->getY() * ofGetHeight();
					float tX = toPt->getX() * ofGetWidth();
					float tY = toPt->getY() * ofGetHeight();
		
					ofxTuioPoint *fnPt = new ofxTuioPoint(fX, fY);
					ofxTuioPoint *tnPt = new ofxTuioPoint(tX, tY);
		
					float dx = fX-tX;
					float dy = fY-tY;
		
					float dist = sqrtf(dx*dx+dy*dy);
		
					if (isConnectionModeOn()) {
						if (from->getProxima() > dist) {
							// To refine
							if (!areAlreadyConnected(from, to)) {
								SConnection *connection = createConnection(
															   from, 
															   from->getTuio()->getSessionId(),
															   to->getTuio()->getSessionId(), 
															   CONNECTION_LINE
															   );
								connections->push_back(connection);
							}
						} else {
							if (areAlreadyConnected(from, to)) {
								removeNoMoreValidConnections(from);
								removeNoMoreValidConnections(to);
							}
						}
					}
					delete fromPt;
					delete toPt;
					delete fnPt;
					delete tnPt;
				}
			}
		}
	}
}


// Cursor Update
void SmurfBrain::handleCursorUpdate(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor) {
	vector<SmurFinger*>::iterator it;
	for (it = fingers->begin(); it != fingers->end(); it++) {
		SmurFinger *finger = *it;
		if (finger != NULL && finger->getTuio() != NULL) {
			if (finger->getTuio()->getSessionId() == tuioCursor.getSessionId()) {
				Smurf* smurf = findSmurfGettingDraggedIfAny(finger->getTuio()->getSessionId());
				if (smurf != NULL) {
					finger->clearPoints();
				
					if (smurf->getTuio() != NULL) {
						((ofxTuioObject*)smurf->getTuio())->update(
															   tuioCursor.getPosition().getX(), 
															   tuioCursor.getPosition().getY(),
															   ((ofxTuioObject*)smurf->getTuio())->getAngle(), 
															   tuioCursor.getXSpeed(), 
															   tuioCursor.getXSpeed(), 
															   0.0f, 
															   tuioCursor.getMotionSpeed(), 
															   tuioCursor.getMotionAccel()
															   );
					}
				} else {
					finger->addPoint(tuioCursor.getPosition());
				}

				finger->setTuio(&tuioCursor);
				finger->onUpdate(getOscSender());

				break;
			}
		}
	}
}

// Cursor Remove
void SmurfBrain::handleCursorRemove(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor) {
	vector<SmurFinger*>::iterator it;
	for (it = fingers->begin(); it != fingers->end(); it++) {
		SmurFinger *finger = *it;
		if (finger != NULL && finger->getTuio() != NULL) {
			if (finger->getTuio()->getSessionId() == tuioCursor.getSessionId()) {
				markSelection(finger, smurfs);
			
				if (finger->getPoints() != NULL && finger->getPoints()->size()>MIN_GESTURE_POINTS_THRESHOLD) {
					//handleGesture(finger, gesturesEngine->isMatching(finger->getPoints()));
				}
			
				Smurf* dragged = findSmurfGettingDraggedIfAny(finger->getTuio()->getSessionId());
				if (dragged != NULL) {
					Smurf *target = evalIfTargetIsDropCompatible(dragged);
					if (target != NULL) {
						doConnectToTargetIfAnyValidConnection(dragged, target);
					} else {
						dragged->setDragging(-FLT_MAX);
					}
				}
				
				finger->onRemove(getOscSender());

				delete finger;
				fingers->erase(it);
				finger = NULL;
				
				break;
			}
		}
	}
}




// Smurf Add
void SmurfBrain::handleSmurfAdd(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject) {
	bool absent = true;
	Smurf *smurf;
	vector<Smurf*>::iterator it;
	for (it = smurfs->begin(); it != smurfs->end(); it++) {
		smurf = *it;
		if (smurf != NULL) {
			ofxTuioObject *tuio = (ofxTuioObject*) smurf->getTuio();
			if (tuio != NULL) {
				if (tuio->getSessionId() == tuioObject.getSessionId()) {
					smurf->onAdd(getOscSender());
					absent = false;
					break;
				}
			}
		}
	}
	if (absent) {
		
		SmurfDetails *detail = getSmurfCfg()->getSmurfDetails((&tuioObject)->getFiducialId());

		if (detail->kind == "OSCILLATOR") {
			smurf = new FMFOscillator(&tuioObject, SMURF_KIND_TANGIBLE);
		} else if (detail->kind == "PHAZOR") {
			smurf = new FMFOscillator(&tuioObject, SMURF_KIND_TANGIBLE);
		} else {
			smurf = new Smurf(&tuioObject, SMURF_KIND_TANGIBLE);
		}

		smurf->onAdd(getOscSender());

		smurf->setFG(detail->fg);
		smurf->setBG(detail->bg);
		smurf->setAspect(detail->aspect);
		smurf->setRadius(detail->radius);
		smurf->setProxima(detail->proxima);
		smurf->setProximaVisible(detail->proximaVisible);
		smurf->setRange((int)detail->range);
		smurf->setFunction(detail->function);
		
		smurfs->push_back(smurf);
	}
}

// Smurf Update
void SmurfBrain::handleSmurfUpdate(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject) {
	vector<Smurf*>::iterator it;
	for (it = smurfs->begin(); it != smurfs->end(); it++) {
		Smurf *smurf = *it;
		if (smurf != NULL) {
			ofxTuioObject *tuio = (ofxTuioObject*) smurf->getTuio();
			if (tuio != NULL) {
				if (tuio->getSessionId() == tuioObject.getSessionId()) {
					smurf->setTuio(&tuioObject);
			
					evalConnectivityToOtherSmurfsOnRangeIfAny(smurf);

					smurf->onUpdate(getOscSender());
					break;
				}
			}
		}
	}
}

// Smurf Remove
void SmurfBrain::handleSmurfRemove(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject) {
	vector<Smurf*>::iterator it;
	for (it = smurfs->begin(); it != smurfs->end(); it++) {
		Smurf *smurf = *it;
		ofxTuioObject *tuio = (ofxTuioObject*) smurf->getTuio();
		if (tuio != NULL) {
			if (tuio->getSessionId() == tuioObject.getSessionId()) {
				removeNoMoreValidConnections(smurf);
				smurf->getOscMsgMap().clear();
				smurf->onRemove(getOscSender());
			
				delete smurf;
				smurfs->erase(it);
				smurf = NULL;
				
				break;
			}
		}
	}
}

// TUIO object added
void SmurfBrain::objectAdded(ofxTuioObject & tuioObject){
	handleSmurfAdd(getSmurfs(), tuioObject);
}

// TUIO object removed
void SmurfBrain::objectRemoved(ofxTuioObject & tuioObject){
	handleSmurfRemove(getSmurfs(), tuioObject);
}

// TUIO object updated
void SmurfBrain::objectUpdated(ofxTuioObject & tuioObject){
	handleSmurfUpdate(getSmurfs(), tuioObject);
}

// TUIO cursor added
void SmurfBrain::tuioAdded(ofxTuioCursor & tuioCursor){
	handleCursorAdd(getFingers(), tuioCursor);
}

// TUIO cursor removed
void SmurfBrain::tuioRemoved(ofxTuioCursor & tuioCursor){
	handleCursorRemove(getFingers(), tuioCursor);
}

// TUIO cursor updated
void SmurfBrain::tuioUpdated(ofxTuioCursor & tuioCursor){
	handleCursorUpdate(getFingers(), tuioCursor);
}

