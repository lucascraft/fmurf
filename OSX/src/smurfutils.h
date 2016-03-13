/*
 *  smurfutils.h
 *
 *  openFrameworks
 *
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

#ifndef _SMURF_UTILS
#define _SMURF_UTILS

#include "ofxTuio.h"
#include "smurf.h"
#include "smurfinger.h"
#include "smurfanchor.h"

/**
 * Enum literals to be used to precisely determine which UI element to consider
 * reagrding range detection utilities.
 */
enum CloserEnum {
	CLOSER_SMUON,
	CLOSER_SMURF,
	CLOSER_CURSOR
};

/**
 * This utility class offers routines to retieve UI elements given a range and a kind.
 * It basically compare distances between an origin and UI elements of a given kind inside a determined radius.
 */
class SmurfUtils {
private:
	float virtualID;
	float getNextVirtualID();

public:
	SmurfUtils();
	
	
	Smuon* getCloserSmuonWithinGivenRadiusAndKind(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius, CloserEnum discriminantKind);
	
	vector<Smuon*> getSmuonsWithinGivenRadiusAndKind(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius, CloserEnum discriminantKind);
	
	Smuon* getCloserSmuonWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius);
	
	vector<Smuon*> getSmuonsWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius);
	
	Smurf* getCloserSmurfWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius);
	
	vector<Smuon*> getSmurfsWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius);
	
	SmurFinger* getCloserCursorWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius);
	
	vector<Smuon*> getCursorsWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius);

	// Atypical smurfs creation utilities
	//-----------------------------------
	Smurf* createAtypicalSmurf(Smuon* smuon, SmurfKind kind);
	
	SmurfAnchor* createSmurfAnchor(Smuon* smuon, float _ownerId, AnchorKind _anchorKind);

};

#endif

