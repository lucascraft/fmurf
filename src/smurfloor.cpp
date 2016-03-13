/*
 *  smurfloor.cpp
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


#include "swave.h"
#include "smurfloor.h"


Smurfloor::Smurfloor(int _bpm, int _speed) {
	waves = new vector<SWave*>();
	brain = new SmurfBrain(_bpm);
	bpm = _bpm;	
	waveSpeed = _speed;
	lastWaveUid = 0;
	verbose = false;
}

void Smurfloor::think() {
	brain->handleBeat(getNextWaveUid(), waves);
	brain->handleOscReceive();
}

void Smurfloor::setWaveSpeed(int _speed) {
	waveSpeed = _speed;
}

int Smurfloor::getWaveSpeed() {
	return waveSpeed;
}

void Smurfloor::setBPM(int _bpm) {
	bpm = _bpm;
	brain->setBPM(bpm);
}

int Smurfloor::getBPM() {
	return bpm;
}

void Smurfloor::setOscSender(ofxOscSender *_sender) {
	brain->setOscSender(_sender);
}

void Smurfloor::setOscReceiver(ofxOscReceiver *_receiver) {
	brain->setOscReceiver(_receiver);
}

void Smurfloor::setSmurfCfg(SmurfCfg *_cfg) {
	brain->setSmurfCfg(_cfg);
}

int Smurfloor::getNextWaveUid() {
	return lastWaveUid++;
}

void Smurfloor::setVerbose(bool _verbose) {
	verbose = _verbose;
}

bool Smurfloor::isVerbose() {
	return verbose;
}

#ifdef TARGET_OS_MAC
void Smurfloor::toggleGesture() {
	brain->toggleGesture();
}

bool Smurfloor::isGesture() {
	return brain->isGesture();
}
#endif

bool Smurfloor::isConnectionModeOn() {
	return brain->isConnectionModeOn();
}

void Smurfloor::toggleConnectionMode() {
	brain->toggleConnectionMode();
}



