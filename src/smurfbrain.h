/*
 *  smurfbrain.h
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

#ifndef _SMURF_BRAIN
#define _SMURF_BRAIN

#include "ofxOsc.h"

#include "ofEvents.h"

#include "swave.h"
#include "smurfconnection.h"
#include "smurfanchor.h"
#include "smurfbeat.h"
#include "smurfcfg.h"
#include "smurfinger.h"
#include "smurf.h"
#include "gestures.h"
#include "smurfutils.h"


class SmurfBrain {
	
private:
	//
	vector<Smurf*> *smurfs;
	vector<SmurFinger*> *fingers;
	vector<SConnection*> *connections;
	
	// OSC
	ofxOscSender* sender;
	ofxOscReceiver* receiver;
	
	SmurfCfg *config;
	
#ifdef TARGET_OS_MAC
	bool gesture;
	SmurfGestures *gesturesEngine;
#endif
	
	bool connectionsAllowed;
	
	vector<Smuon*> *selection;
	
	SmurfUtils *utils;
	//ConnectionUtils *connectionUtils;
	
	
public:
	
	// Execution threads
	SmurfBeat beat;

	SmurfBrain(int _bpm);
	
	void setSmurfs(vector<Smurf*> *_smurfs);
	void setFingers(vector<SmurFinger*> *_fingers);
	void setConnections(vector<SConnection*> *_connections);
	
	//
	vector<Smurf*> * getSmurfs();
	vector<SmurFinger*> * getFingers();
	vector<SConnection*> * getConnections();
	
	void deleteSmurf(float sid);
	
	void handleOscReceive();
	
	//
	void initBeat(int bpm);
	void handleBeat(int waveId, vector<SWave*> *waves);

	//
	void handleCursorAdd(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor);
	void handleCursorUpdate(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor);
	void handleCursorRemove(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor);
	
	//
	void handleSmurfAdd(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject);
	void handleSmurfUpdate(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject);
	void handleSmurfRemove(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject);
	
	//
	void objectAdded(ofxTuioObject & tuioObject);
	void objectRemoved(ofxTuioObject & tuioObject);
	void objectUpdated(ofxTuioObject & tuioObject);
	
	// TUIO
	void tuioAdded(ofxTuioCursor & tuioCursor);
	void tuioRemoved(ofxTuioCursor & tuioCursor);
	void tuioUpdated(ofxTuioCursor & tuioCursor);
	
	// BPM
	void setBPM(int bpm);
	int getBPM();
	
	// OSC sender
	void setOscSender(ofxOscSender *_sender);
	ofxOscSender* getOscSender();
	
	// OSC receiver
	void setOscReceiver(ofxOscReceiver *_receiver);
	ofxOscReceiver* getOscReceiver();
	
	// Cfg
	void setSmurfCfg(SmurfCfg *_cfg);
	SmurfCfg *getSmurfCfg();

#ifdef TARGET_OS_MAC
	// Gestures
	void setGestures(SmurfGestures *_gesturesEngine);
	SmurfGestures * getGestures();
	//void handleGesture(Smuon* smuon, SmurfGestureClassification _gestureClassification);
	void loadGestures(); // gesture.models file
	bool isGesture();
	void toggleGesture();
	//void saveGestures();
#endif
	
	// Connections
	bool isConnectionModeOn();
	void toggleConnectionMode();
	
	// SVG
	void loadSVG();
	
	// Smurf Utils
	SmurfUtils *getSmurfUtils();
	
	// Selection
	void handleSimpleSelection(Smurf* _smurf);
	void handleMultipleSelection(vector<Smurf*> _smurfs);
		
	// Link handling
	void handleCreateLinkInitial(Smuon* smuon, Smurf* _smurf, SConnectionVisual kind);
	void removeNoMoreValidConnections(Smurf *_smurf);
	
	// Smurf creation handling
	void handleCreateNonTangibleSmurf(Smuon* smuon, SmurfKind kind);

	//
	void handleSelection(SmurFinger *_finger);
	void markSelection(SmurFinger* finger, vector<Smurf*> *smurfs);
	
	//
	bool isCursorAlive(SmurFinger *_finger);
	bool isCursorAlive(float sessionId);
	SmurFinger *findCursor(float sessionId);
	Smurf *findSmurf(float sessionId);
	Smurf *findSmurfGettingDraggedIfAny(float _sessionId);
	Smurf *evalIfTargetIsDropCompatible(Smurf* _dragged);
	
	void evalConnectivityToOtherSmurfsOnRangeIfAny(Smurf *smurf);
	
	void doConnectToTargetIfAnyValidConnection(Smurf *_dragged, Smurf *_target);
	SConnection* createConnection(Smuon* smuon, float fromID, float toID, SConnectionVisual kind);
	bool areAlreadyConnected(Smurf *from, Smurf *to);
};

#endif
