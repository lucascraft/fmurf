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
	connectionsAllowed = true;

	initBeat(_bpm);
	
	windowsManager = new UIManager();
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

void SmurfBrain::handleTics() {
	if (smurfs != NULL) {
		for (int i=0; i<smurfs->size(); i++) {
			Smurf *smurf = smurfs->at(i);
			ofxTuioObject *tuio = (ofxTuioObject*) smurf->getTuio();
			if(smurf->tic() == 1) {
				smurf->onTic(getOscSender());
			}
		}
	}
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

void SmurfBrain::handleGesture(Smuon* smuon, SmurfGestureClassification _gestureClassification) {
	if (!isGesture()) return;
	if (smuon == NULL) return;
	
	Smurf *closer = utils->getCloserSmurfWithinGivenRadius(getSmurfs(), getFingers(), smuon->getTuio(), 0.08f);
	
	if (_gestureClassification == GESTURE_SELECTION) {
		handleSimpleSelection(closer);
	} else if (_gestureClassification == GESTURE_MULTIPLE_SELECTION) {
		// Not supported yet
	} else if (_gestureClassification == GESTURE_CREATE_VIRTUAL_SMURF) {
		// Not supported yet
		// Will add DAC support later on 
		//handleCreateNonTangibleSmurf(smuon, SMURF_KIND_VIRTUAL);
	} else if (_gestureClassification == GESTURE_CREATE_SIN_FREQ_LINK) {
		Smurf *newSmurf = getSmurfUtils()->createAtypicalSmurf(smuon, SMURF_KIND_VIRTUAL);
		if (newSmurf != NULL) {
			smurfs->push_back(newSmurf);
		}
		handleCreateLinkInitial(smuon, closer, CONNECTION_SIN_FREQ);
		
		//getUIManager()->getWindows()->push_back(new SWindow(newSmurf));
	} else if ( _gestureClassification == GESTURE_CREATE_SQUARE_FREQ_LINK) {
		Smurf *newSmurf = getSmurfUtils()->createAtypicalSmurf(smuon, SMURF_KIND_VIRTUAL);
		if (newSmurf != NULL) {
			smurfs->push_back(newSmurf);
		}
		handleCreateLinkInitial(smuon, closer, CONNECTION_SQUARE_FREQ);
		
		//getUIManager()->getWindows()->push_back(new SWindow(newSmurf));
	} else if ( _gestureClassification == GESTURE_CREATE_TRIANGLE_FREQ_LINK) {
		Smurf *newSmurf = getSmurfUtils()->createAtypicalSmurf(smuon, SMURF_KIND_VIRTUAL);
		if (newSmurf != NULL) {
			smurfs->push_back(newSmurf);
		}
		handleCreateLinkInitial(smuon, closer, CONNECTION_TRIANGLE_FREQ);

		//getUIManager()->getWindows()->push_back(new SWindow(newSmurf));
	}
}

void SmurfBrain::handleSimpleSelection(Smurf* _smurf) {
	if (_smurf != NULL) {
		bool status = _smurf->isSelected()?false:true;
		_smurf->setSelected(status);
	}
}

void SmurfBrain::handleMultipleSelection(vector<Smurf*> _smuon) {
	// Not implemented yet !!!
}

bool SmurfBrain::isAnAnchor(float _fid) {
	Smurf* smurf = findSmurf(_fid);
 	return dynamic_cast<SmurfAnchor*> (smurf) != NULL;
}

SConnection* SmurfBrain::createConnection(float fromID, float toID, SConnectionVisual kind) {
	
	if (isAnAnchor(fromID) || isAnAnchor(toID)) return NULL;
	
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
	
	handleConnectionAdd(connection);
	
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
		SConnection *connection = createConnection(_smurf->getTuio()->getSessionId(), connectionHandle->getTuio()->getSessionId(), kind);

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

#ifdef TARGET_OS_MAC
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
#endif


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

Pearl* SmurfBrain::findPearlGettingDraggedIfAny(float _sessionId) {
	return (Pearl*) findSmurfGettingDraggedIfAny(_sessionId, true);
}

Smurf* SmurfBrain::findSmurfGettingDraggedIfAny(float _sessionId) {
	return (Smurf*) findSmurfGettingDraggedIfAny(_sessionId, false);
}

Smurfer* SmurfBrain::findSmurfGettingDraggedIfAny(float _sessionId, bool pearlFocused) {
	for (int i=0; i<smurfs->size(); i++) {
		if (pearlFocused) {
			if (smurfs->at(i)->getPearl()->getDragging() == _sessionId) {
				return smurfs->at(i)->getPearl();
			}
		} else {
			if (smurfs->at(i)->getDragging() == _sessionId) {
				return smurfs->at(i);
			}
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



void SmurfBrain::removeNoMoreValidConnections(Smurf* _from, Smurf* _to) {	
	if (_from == NULL) return;
	if (_to == NULL) return;
	
	vector<SConnection*> *connectionsToDelete = new vector<SConnection*>();
	
	vector<SConnection*>::iterator it;
	for (it = connections->begin(); it != connections->end(); it++) {
		SConnection* connection = *it;
		if (connection != NULL) {
			if (connection->fromAnchor() == NULL) {
				connectionsToDelete->push_back(connection);
			} else if (connection->toAnchor() == NULL) {
				connectionsToDelete->push_back(connection);
			} else if (connection->fromSID() == _from->getTuio()->getSessionId() && connection->toSID() == _to->getTuio()->getSessionId()) {
				connectionsToDelete->push_back(connection);
			}
		}
	}
	vector<SConnection*>::iterator toDeleteIt;
	for (toDeleteIt = connectionsToDelete->begin(); toDeleteIt != connectionsToDelete->end(); toDeleteIt++) {
		deleteConnection(*toDeleteIt);
	}
	delete connectionsToDelete;
}

void SmurfBrain::removeNoMoreValidConnections(Smurf* _smurf) {	
	if (_smurf == NULL) return;
	if (_smurf->getTuio() == NULL) return;
	
	vector<SConnection*> *connectionsToDelete = new vector<SConnection*>();
	
	vector<SConnection*>::iterator it;
	for (it = connections->begin(); it != connections->end(); it++) {
		SConnection* connection = *it;
		if (connection != NULL) {
			if (connection->fromSID() == _smurf->getTuio()->getSessionId()) {
				connectionsToDelete->push_back(connection);
			} else if (connection->toSID() == _smurf->getTuio()->getSessionId()) {
				connectionsToDelete->push_back(connection);
			}
		}
	}
	vector<SConnection*>::iterator toDeleteIt;
	for (toDeleteIt = connectionsToDelete->begin(); toDeleteIt != connectionsToDelete->end(); toDeleteIt++) {
		deleteConnection(*toDeleteIt);
	}
	delete connectionsToDelete;
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
				return;
			}
		}
	}
}

void SmurfBrain::deleteSmurf(Smurf* s) {
	if (s == NULL) return;
	vector<Smurf*>::iterator it;
	for (it = smurfs->begin(); it != smurfs->end(); it++) {
		Smurf *smurf = *it;
		if (smurf != NULL && s == smurf) {
			smurf->onRemove(getOscSender());
			smurfs->erase(it);
			delete smurf;
			smurf = NULL;
			return;
		}
	}
}

void SmurfBrain::deleteConnection(SConnection *connection) {
	vector<SConnection*>::iterator it;
	for (it = connections->begin(); it != connections->end(); it++) {
		SConnection *conn = *it;
		if (conn == connection) {
			handleConnectionRemove(conn);
			if (conn->fromAnchor() != NULL) {
				deleteSmurf(conn->fromAnchor());
			}
			if (conn->toAnchor() != NULL) {
				deleteSmurf(conn->toAnchor());
			}
			connections->erase(it);
			delete conn;
			conn = NULL;
			return;
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
		float dist = _finger->getTuio()->getDistance(smurf->getPearl()->getTuio());
		if (dist < 0.03 && !smurf->getPearl()->isAlreadyDragging()) {
			smurf->getPearl()->setDragging(_finger->getTuio()->getSessionId());
			smurf->getPearl()->toggleSelected();
		}		
		
	}	
}

Smurf* SmurfBrain::evalIfTargetIsDropCompatible(Smurf* dragged) {
//	vector<Smurf*>::iterator it;
//	if (dragged->getKind() == SMURF_KIND_HANDLE) {
//		for (it = smurfs->begin(); it != smurfs->end(); it++) {
//			Smurf *smurf = *it;
//			if (smurf != NULL) {
//				ofxTuioContainer *target = smurf->getTuio();
//				if (target != NULL) {
//					if (dragged->getTuio() != NULL) {
//						if (target->getDistance(dragged->getTuio()) < 0.03) {
//							if (smurf->getKind() != SMURF_KIND_HANDLE) {
//								return smurf;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
	return NULL; 
}

void SmurfBrain::doConnectToTargetIfAnyValidConnection(Smurf *dragged, Smurf *target) {
//	for (int i=0; i<connections->size(); i++) {
//		SConnection* connection = connections->at(i);
//		if (connection != NULL) {
//			float toID = connection->toID();
//			if (dragged->getTuio() != NULL) {
//				if (toID == dragged->getTuio()->getSessionId()) {
//					if (target != NULL) {
//						connection->setToID(target->getTuio()->getSessionId());
//						deleteSmurf(dragged->getTuio()->getSessionId());
//					}
//				}
//			}
//		}
//	}
}

bool SmurfBrain::areAlreadyConnected(Smurf *from, Smurf *to) {
	if (from != NULL && to != NULL) { 
		if (from->getTuio() != NULL && to->getTuio() != NULL) {
			if (to->getTuio()->getSessionId() == from->getTuio()->getSessionId()) {
				return true;
			} 
			//bool DAC = false;
			for (int i=0; i<connections->size(); i++) {
				SConnection* connection = connections->at(i);
				/*
				if (connection->toSID() == -440.0) {
					DAC = true;
				}
				if (DAC) { //ONLY ONE Connection to DAC at TIME !!!
					if (to->getTuio()->getSessionId() == -440.0 || from->getTuio()->getSessionId() == -440.0) {
						return true;
					}
				}*/
				if (
					connection->toSID() == to->getTuio()->getSessionId() && 
					connection->fromSID() == from->getTuio()->getSessionId()
				) {
					return true;
				} else if (
					connection->toSID() == from->getTuio()->getSessionId() && 
					connection->fromSID() == to->getTuio()->getSessionId()
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
	if (from->getKind() == SMURF_KIND_ANCHOR) return;
	if (dynamic_cast<SmurfAnchor*> (from) != NULL) return;
	
	if (from->getKind() == SMURF_KIND_TANGIBLE) {
		for (int i=0; i<smurfs->size(); i++) {
			Smurf *to = smurfs->at(i);
			if (dynamic_cast<SmurfAnchor*> (to) == NULL && to->getKind() != SMURF_KIND_ANCHOR /*&& to->getKind() == SMURF_KIND_TANGIBLE*/) {
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
							if (to->getTuio()->getSessionId() == -440.0 || from->getTuio()->getSessionId() == -440.0) {
								bool dummy = true;
							}
							
							if (!areAlreadyConnected(from, to)) {
								SConnection *connection = createConnection(
															   from->getTuio()->getSessionId(),
															   to->getTuio()->getSessionId(), 
															   CONNECTION_LINE
															);
								if (connection != NULL) {
									connections->push_back(connection);
								}
							}
						} else {
							if (areAlreadyConnected(from, to)) {
								removeNoMoreValidConnections(from, to);
								removeNoMoreValidConnections(to, from);
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



///////////////////////////
// UI Manager
///////////////////////////

UIManager* SmurfBrain::getUIManager() {
	return windowsManager;
}


///////////////////////////
// Cursor Update
///////////////////////////
void SmurfBrain::handleCursorUpdate(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor) {
	vector<SmurFinger*>::iterator it;
	for (it = fingers->begin(); it != fingers->end(); it++) {
		SmurFinger *finger = *it;
		if (finger != NULL && finger->getTuio() != NULL) {
			if (finger->getTuio()->getSessionId() == tuioCursor.getSessionId()) {
				
				Pearl* pearl = findPearlGettingDraggedIfAny(finger->getTuio()->getSessionId());
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
				} if(pearl != NULL) {
					if (pearl->getTuio() != NULL) {
						float pX = pearl->getTuio()->getX();
						float pY = pearl->getTuio()->getY();
						float fX = finger->getTuio()->getX();
						float fY = finger->getTuio()->getY();
						
						float dX = fX - pX;
						//float dY = fY - pY;

						float val = dX/ofGetWidth();
						val = pearl->getLevel()+100*val;
						if (val<0) { val = 0; }
						if (val>1) { val = 1; }
						pearl->setLevel(val);
						((Smurf*)pearl->getParent())->onUpdate(sender);
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

//
// Cursor Remove
//
void SmurfBrain::handleCursorRemove(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor) {
	vector<SmurFinger*>::iterator it;
	for (it = fingers->begin(); it != fingers->end(); it++) {
		SmurFinger *finger = *it;
		if (finger != NULL && finger->getTuio() != NULL) {
			if (finger->getTuio()->getSessionId() == tuioCursor.getSessionId()) {
				markSelection(finger, smurfs);
			
				//
				// To plug gestures back later on
				//
				if (finger->getPoints() != NULL && finger->getPoints()->size()>MIN_GESTURE_POINTS_THRESHOLD) {
					handleGesture(finger, gesturesEngine->isMatching(finger->getPoints()));
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




//
// Smurf Add
//
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
		if (detail == NULL) return;

			if (detail->kind == "OSCILLATOR") {
				smurf = new FMFOscillator(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "SIN_OSC") {
				smurf = new FMFSinOsc(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "SQR_OSC") {
				smurf = new FMFSqrOsc(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "TRIANGLE_OSC") {
				smurf = new FMFTriangleOsc(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "SAWTOOTH_OSC") {
				smurf = new FMFSawtoothOsc(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "PULSE_OSC") {
				smurf = new FMFPulseOsc(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "PHASOR") {
				smurf = new FMFPhasor(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "TEMPO") {
				smurf = new FMFTempo(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "MULT") {
				smurf = new FMFMultiply(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "ADD") {
				smurf = new FMFAdd(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "SAMPLER") {
				smurf = new FMFSampler(&tuioObject, SMURF_KIND_TANGIBLE);
			} else if (detail->kind == "SEQUENCER") {
				smurf = new FMFSequencer(&tuioObject, SMURF_KIND_TANGIBLE);
			} else {
				smurf = new Smurf(&tuioObject, SMURF_KIND_TANGIBLE);
			}
			smurf->setFG(detail->fg);
			smurf->setBG(detail->bg);
			smurf->setAspect(detail->aspect);
			smurf->setRadius(detail->radius);
			smurf->setProxima(detail->proxima);
			smurf->setProximaVisible(detail->proximaVisible);
#ifdef TARGET_OS_MAC		
			smurf->setRange((int)detail->range);
#endif			
			smurf->setKind(SMURF_KIND_TANGIBLE);
			smurf->setFunction(detail->function);
			smurf->setLabelVisible(detail->labelVisible);
			smurf->setLabel(detail->label);
		
			smurf->onAdd(getOscSender());

			smurfs->push_back(smurf);
	}
}

//
// Smurf Update
//
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

//
// Smurf Remove
//
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

//
//
//
void SmurfBrain::handleConnectionAdd(SConnection* connection) {
	if (connection != NULL) {
		connection->onAdd(getOscSender());
	}
}

//
//
//
void SmurfBrain::handleConnectionUpdate(SConnection* connection) {
	if (connection != NULL) {
		connection->onUpdate(getOscSender());
	}
}

//
//
//
void SmurfBrain::handleConnectionRemove(SConnection* connection) {
	if (connection != NULL) {
		connection->onRemove(getOscSender());
	}
}


//
// TUIO object added
//
void SmurfBrain::objectAdded(ofxTuioObject & tuioObject){
	handleSmurfAdd(getSmurfs(), tuioObject);
}

//
// TUIO object removed
//
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

//
// TUIO cursor removed
//
void SmurfBrain::tuioRemoved(ofxTuioCursor & tuioCursor){
	handleCursorRemove(getFingers(), tuioCursor);
}

//
// TUIO cursor updated
//
void SmurfBrain::tuioUpdated(ofxTuioCursor & tuioCursor){
	handleCursorUpdate(getFingers(), tuioCursor);
}

