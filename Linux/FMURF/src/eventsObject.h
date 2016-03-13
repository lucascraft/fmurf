/*
 *  eventObjet.h
 *  openFrameworks
 *
 *  Created by lucas bigeardel on 15/02/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef _OFXEVENTSOBECT
#define _OFXEVENTSOBECT

#include "ofMain.h"
#include "ofEvents.h"

class eventsObject {
public:
	eventsObject(){
	}
	
	void enable(){
	    ofAddListener(ofEvents.update, this, &eventsObject::update);
	}
	
	void disable(){
	    ofRemoveListener(ofEvents.update, this, &eventsObject::update);
	}
	
	void update(ofEventArgs & args){
		counter+=0.3;
		long intCounter=(long)counter;
		ofNotifyEvent(bangBeatEvt,intCounter,this);
	}
	
	ofEvent<long> bangBeatEvt;
	
private:
	float counter;
	
};
#endif /* _OFXEVENTSOBECT */
