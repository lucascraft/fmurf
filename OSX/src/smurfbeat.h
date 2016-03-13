/*
 *  smurfbeat.h
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

#ifndef _SMURF_BEAT
#define _SMURF_BEAT

#include "ofMain.h"

#include "ofxThread.h"

// this is not a very exciting example yet
// but ofThread provides the basis for ofNetwork and other
// operations that require threading.
//
// please be careful - threading problems are notoriously hard
// to debug and working with threads can be quite difficult


class SmurfBeat : public ofxThread {
		
public:
	long lastCount;
	long count;  // threaded fucntions that share data need to use lock (mutex)
	// and unlock in order to write to that data
	// otherwise it's possible to get crashes.
	//
	// also no opengl specific stuff will work in a thread...
	// threads can't create textures, or draw stuff on the screen
	// since opengl is single thread safe
	
	int bpm;
		
	//--------------------------
	SmurfBeat(){
		lastCount = 1;
		count = 0;
		bpm = 60;
	}
	
	void start(){
		startThread(true, false);   // blocking, verbose
	}
	
	void stop(){
		stopThread();
	}
	
	//--------------------------
	void threadedFunction(){
		while( isThreadRunning() != 0 ){
			if( lock() ){
				count++;
				if(count >= LONG_MAX) count = 0;
				unlock();
				ofSleepMillis(60000 / bpm);
			}
		}
	}
	
	//--------------------------
	int bang(){
		if( lock() ){
			if (lastCount != count) {
				lastCount = count;
				unlock();
				return lastCount;
			} 
			unlock();
		} else {
			cout << "can't lock!\neither an error\nor the thread has stopped";
		}
		return -1;
	}
	
	void setBPM(int _bpm) {
		bpm = _bpm;
	}
	
	int getBPM() {
		return bpm;
	}
	
};

#endif
