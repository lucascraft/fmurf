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
#include "fmfui.h"

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
	
	UIManager* windowsManager;
	
public:
	
	// Beat execution thread
	SmurfBeat beat;

	SmurfBrain(int _bpm);
	
	void setSmurfs(vector<Smurf*> *_smurfs);
	void setFingers(vector<SmurFinger*> *_fingers);
	void setConnections(vector<SConnection*> *_connections);
	
	//
	vector<Smurf*> * getSmurfs();
	vector<SmurFinger*> * getFingers();
	vector<SConnection*> * getConnections();
	
	void deleteSmurf(Smurf* smurf);
	void deleteSmurf(float sid);
	void deleteConnection(SConnection *connection);
	
	void handleOscReceive();
	
	// Smurf beat lifecycle
	void initBeat(int bpm);
	void handleBeat(int waveId, vector<SWave*> *waves);
	void handleTics();

	// Smurf cursors lifecycle
	void handleCursorAdd(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor);
	void handleCursorUpdate(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor);
	void handleCursorRemove(vector<SmurFinger*> *fingers, ofxTuioCursor & tuioCursor);
	
	// Smurf fiducials lifecycle
	void handleSmurfAdd(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject);
	void handleSmurfUpdate(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject);
	void handleSmurfRemove(vector<Smurf*> *smurfs, ofxTuioObject & tuioObject);
	
	// Smurf connections lifecycle
	void handleConnectionAdd(SConnection* connection);
	void handleConnectionUpdate(SConnection* connection);
	void handleConnectionRemove(SConnection* connection);
	
	// TUIO objects lifecycle
	void objectAdded(ofxTuioObject & tuioObject);
	void objectRemoved(ofxTuioObject & tuioObject);
	void objectUpdated(ofxTuioObject & tuioObject);
	
	// TUIO cursors lifecycle
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
	void handleGesture(Smuon* smuon, SmurfGestureClassification _gestureClassification);
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
	void removeNoMoreValidConnections(Smurf *_smurf, Smurf *_to);
	void removeNoMoreValidConnections(Smurf *_smurf);
	
	// Smurf creation handling
	void handleCreateNonTangibleSmurf(Smuon* smuon, SmurfKind kind);

	//
	void handleSelection(SmurFinger *_finger);
	void markSelection(SmurFinger* finger, vector<Smurf*> *smurfs);
	
	// Cusor utilities
	bool isCursorAlive(SmurFinger *_finger);
	bool isCursorAlive(float sessionId);
	
	// find utilities
	SmurFinger *findCursor(float sessionId);
	Smurf *findSmurf(float sessionId);
	Smurfer *findSmurfGettingDraggedIfAny(float _sessionId, bool pearlFocused);
	Smurf *findSmurfGettingDraggedIfAny(float _sessionId);
	Pearl* findPearlGettingDraggedIfAny(float _sessionId);
	Smurf *evalIfTargetIsDropCompatible(Smurf* _dragged);
	bool isAnAnchor(float _fid);
	
	void evalConnectivityToOtherSmurfsOnRangeIfAny(Smurf *smurf);
	
	void doConnectToTargetIfAnyValidConnection(Smurf *_dragged, Smurf *_target);
	SConnection* createConnection(float fromID, float toID, SConnectionVisual kind);
	bool areAlreadyConnected(Smurf *from, Smurf *to);
	
	UIManager* getUIManager();
};

#endif
