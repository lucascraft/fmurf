/*
 *  smurf.h
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

#ifndef _SMURF
#define _SMURF

#include "ofMain.h"
#include "ofxOsc.h"
#include "swave.h"
#include "slot.h"
#include "smurfer.h"

enum SmurfEvt {
	EVT_SELECTION,
	EVT_ADD,
	EVT_REMOVE,
	EVT_UPDATE,
	EVT_BEAT
};

enum SmurfKind {
	SMURF_KIND_TANGIBLE,
	SMURF_KIND_VIRTUAL,
	SMURF_KIND_DUAL,
	SMURF_KIND_INTRINSEC,
	SMURF_KIND_ANCHOR,
	SMURF_KIND_HANDLE
};

enum SmurfAspect {
	SMURF_ASPECT_DISC,
	SMURF_ASPECT_SQUARE,
	SMURF_ASPECT_TRIANGLE,
	SMURF_ASPECT_STAR/*,
	SMURF_ASPECT_HEXAGON,
	SMURF_ASPECT_OCTOGON,
	SMURF_ASPECT_SIX_STAR,
	SMURF_ASPECT_HEIGHT_STAR,
	SMURF_ASPECT_CUSTOM*/
};

enum SmurfFunction {
	SMURF_FUNC_NONE,
	SMURF_FUNC_KNOB
};

class Smurf : public Smurfer {
protected:
	SmurfAspect aspect;
	SmurfKind kind;
	SmurfFunction function;
	vector<Slot*> slots;
	int lastWaveUid;
	map<SmurfEvt, vector<ofxOscMessage*>*> oscMsgMap;
	vector<float> *liveData;
	bool beingUpdated;
public:
	Smurf(ofxTuioObject *tuioObj, SmurfKind kind);
	//Smurf(ofxTuioObject *tuioObj, SmurfKind kind, SmurfFunction function);
	~Smurf();
	void addOscMsgOnEvent(SmurfEvt evt, ofxOscMessage* msg);
	void removeOscMsgOnEvent(SmurfEvt evt, ofxOscMessage* msg);
	
	void setLastWaveUid(int _uid);
	int getLastWaveUid();
	
	vector<Slot*> getSlots();
	
	map<SmurfEvt, vector<ofxOscMessage*>*> getOscMsgMap();	
	
	void onBeat(ofxOscSender *_sender, SWave *wave);
	void onAdd(ofxOscSender *_sender);
	void onUpdate(ofxOscSender *_sender);
	void onRemove(ofxOscSender *_sender);
		
	void setSlot(SlotPosition position, SlotKind kind, SlotVisual visual, ofxOscMessage*);
	void setSlot(SlotPosition position, SlotKind kind, SlotVisual visual, vector<ofxOscMessage*>*);
	
	SmurfKind getKind();
	void setKind(SmurfKind _kind);
	
	SmurfFunction getFunction();
	void setFunction(SmurfFunction _function);
	
	vector<float>* getLiveData();
	void setLiveData(vector<float> *_livedata);
	void pushLiveData(float _idx, float _data);
	void updateLiveData();
	
	virtual void draw();
	
	void setAspect(SmurfAspect _aspect);
	SmurfAspect getAspect();
	
	bool isBeingUpdated();
	void setBeingUpdated(bool _status);
	void toggleBeingUpdated();	
};



#endif