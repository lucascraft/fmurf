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

#include "ofxMSAUtils.h"
#include "ofMain.h"
#include "ofxOsc.h"
#include "swave.h"
#include "slot.h"
#include "smurfer.h"
#include "ofxThread.h"
#include "ofTrueTypeFont.h"


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
	SMURF_ASPECT_TRANSPARENT,
	SMURF_ASPECT_DISC,
	SMURF_ASPECT_SQUARE,
	//SMURF_ASPECT_TRIANGLE,
	//SMURF_ASPECT_STAR,
	SMURF_ASPECT_PENTAGON,
	SMURF_ASPECT_HEXAGON,
	//SMURF_ASPECT_OCTOGON,
	//SMURF_ASPECT_SIX_STAR,
	SMURF_ASPECT_HEIGHT_STAR
	//SMURF_ASPECT_CUSTOM
};

enum SmurfFunction {
	SMURF_FUNC_NONE,
	SMURF_FUNC_KNOB
};

class Pearl : public Smurfer {
	ofxTuioContainer* tuioObj;
	float level;
	float speed;
	Smurfer* parent;
public:
	float getLevel();
	void setLevel(float _lvl);
	ofxTuioContainer* getTuio();
	Pearl() : Smurfer() {
		tuioObj = new ofxTuioContainer(0.0, 0.0, 0.0);
		level = 0.5; // range : [0.0 .. 1.0]
	}
	void setParent(Smurfer* _smurf);
	Smurfer* getParent();
	void draw();
	void draw(ofTrueTypeFont _font);
};


class Smurf : public Smurfer, ofxThread {
protected:
	SmurfAspect aspect;
	SmurfKind kind;
	SmurfFunction function;
	vector<Slot*> slots;
	Pearl* pearl;
	int lastWaveUid;
	long step;
	int sampler;
	string nature;
	map<SmurfEvt, vector<ofxOscMessage*>*> oscMsgMap;
	vector<float> *liveData;
	bool beingUpdated;
	string label;
	float factor;
public:
	Smurf(ofxTuioObject *tuioObj, SmurfKind kind) : Smurfer() {
		slots = vector<Slot*>();
		oscMsgMap = map<SmurfEvt, vector<ofxOscMessage*>*>();
		
		setNature("SMURF");
		
		pearl = new Pearl();
		pearl->setParent(this);
		
		setTuio(tuioObj);
		setKind(kind);
		setFunction(SMURF_FUNC_NONE);
		setLastWaveUid(-1);
		
		ofxOscMessage* onEvtMsg = new ofxOscMessage();
		onEvtMsg->setAddress("/smurf/fid/");
		
		addOscMsgOnEvent(EVT_ADD, onEvtMsg);
		addOscMsgOnEvent(EVT_UPDATE, onEvtMsg);
		addOscMsgOnEvent(EVT_REMOVE, onEvtMsg);
		
		liveData = new vector<float>(16, 0);
		
		animation = PULSE;
		aspect = SMURF_ASPECT_DISC;
		
	}
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
	virtual void draw(ofTrueTypeFont *_font);
	
	void setAspect(SmurfAspect _aspect);
	SmurfAspect getAspect();
	
	bool isBeingUpdated();
	void setBeingUpdated(bool _status);
	void toggleBeingUpdated();	
	
	string getNature();
	void setNature(string _nature);
	Pearl* getPearl();
	
	void setLabel(string _label);
	string getLabel();

	///////////////////
	// Threading
	///////////////////
	
	void start(){
		if (kind != SMURF_KIND_ANCHOR && kind != SMURF_KIND_HANDLE) {
			startThread(true, false);   // blocking, verbose
		}
	}
	
	void stop(){
		if (kind != SMURF_KIND_ANCHOR && kind != SMURF_KIND_HANDLE) {
			stopThread();
		}
	}
	
	//--------------------------
	void threadedFunction(){
		while( isThreadRunning() != 0 ){
			if( lock() ){
				if(sampler + 13 >= INT_MAX) {
					sampler = 0;
				}
				sampler += 13;
				
				// STEP
				step++;
				if(step >= LONG_MAX || step >= 100) step = 0;
				
				unlock();
				ofSleepMillis(50);
			}
		}
	}
	//--------------------------
	int tic(){
		if( lock() ){
			if(step >= 93) {;
				unlock();
				return 1;
			} 
			unlock();
		} else {
			cout << "can't lock!\neither an error\nor the thread has stopped";
		}
		return -1;
	}
	
	void onTic(ofxOscSender *_sender);
	
	float getSpeed();
	
	void setSpeed(float speed);
	
	long getStep();
	
	void setStep(long step);
};

#endif