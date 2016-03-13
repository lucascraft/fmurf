/*
 *  smurfloor.h
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

#ifndef _SMURF_LOOR
#define _SMURF_LOOR


#include "swave.h"
#include "smurfer.h"
#include "smurfinger.h"
#include "smurf.h"
#include "smurfcfg.h"
#include "smurfbrain.h"
#include "ofxOsc.h"


class Smurfloor : public Smurfer {
		
protected:
	int lastWaveUid;
	bool verbose;
public:
	vector<SWave*> *waves;
	
	SmurfBrain *brain;

	int barTickness;

	Smurfloor(int _bpm, int _speed);
	
	long bpm;
	int waveSpeed;
	
	// main loop for OSC IN/OUT + Beat
	void think();
	
	// BPM : beat
	void setBPM(int _bpm);
	int getBPM();
	
	// Last Uid
	int getNextWaveUid();
	
	// OSC Setup
	void setOscSender(ofxOscSender *_sender);
	void setOscReceiver(ofxOscReceiver *_receiver);
	
	// Verbosity
	bool isVerbose();
	void setVerbose(bool _verbose);
	
	// Gesture
	bool isGesture();
	void toggleGesture();
	
	// Connections
	bool isConnectionModeOn();
	void toggleConnectionMode();
	
	void setWaveSpeed(int _speed);
	int getWaveSpeed();
	
	// Config
	void setSmurfCfg(SmurfCfg *_cfg);
};

#endif
