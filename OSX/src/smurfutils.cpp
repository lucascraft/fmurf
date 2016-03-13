/*
 *  smurfutils.cpp
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

#include "smurfutils.h"
#include "ofxMSAUtils.h"

SmurfUtils::SmurfUtils() {
	virtualID = 100;
}

float SmurfUtils::getNextVirtualID() {
	return virtualID++;
}


//
// Stupid Geometry utilities
//
Smuon* SmurfUtils::getCloserSmuonWithinGivenRadiusAndKind(
			vector<Smurf*> *smurfs, 
			vector<SmurFinger*> *fingers, 
			ofxTuioContainer *tuioObj, 
			float radius, 
			CloserEnum _discriminationKind 
) {
	float dist = FLT_MAX;
	Smuon *smuon = NULL;
	
	if (_discriminationKind == CLOSER_SMUON || _discriminationKind == CLOSER_CURSOR) {	
		for (vector<SmurFinger*>::iterator it=fingers->begin(); it != fingers->end(); it++) {
			SmurFinger *finger = *it;
			float dv = finger->getTuio()->getDistance(tuioObj);
			if (dv < dist && radius > dv) {
				dist = dv;
				smuon = finger;
			}
		}
	}
	
	if (_discriminationKind == CLOSER_SMUON || _discriminationKind == CLOSER_SMURF) {	
		for (vector<Smurf*>::iterator it=smurfs->begin(); it != smurfs->end(); it++) {
			Smurf *smurf = *it;
			float dv = smurf->getTuio()->getDistance(tuioObj);
			if (dv < dist && radius > dv) {
				dist = dv;
				smuon = smurf;
			}
		}
	}
	
	return smuon;
	
}

vector<Smuon*> SmurfUtils::getSmuonsWithinGivenRadiusAndKind(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius, CloserEnum _discriminationKind) {
	vector<Smuon*> smuons = vector<Smuon*>();
	
	if (_discriminationKind == CLOSER_SMUON || _discriminationKind == CLOSER_CURSOR) {		
		for (vector<SmurFinger*>::iterator it=fingers->begin(); it != fingers->end(); it++) {
			SmurFinger *finger = *it;
			float dv = finger->getTuio()->getDistance(tuioObj);
			if (radius > dv) {
				smuons.push_back(finger);
			}
		}
	}
	
	if (_discriminationKind == CLOSER_SMUON || _discriminationKind == CLOSER_SMURF) {		
		for (vector<Smurf*>::iterator it=smurfs->begin(); it != smurfs->end(); it++) {
			Smurf *smurf = *it;
			float dv = smurf->getTuio()->getDistance(tuioObj);
			if (radius > dv) {
				smuons.push_back(smurf);
			}
		}
	}
	
	return smuons;
}


Smuon* SmurfUtils::getCloserSmuonWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius) {
	return getCloserSmuonWithinGivenRadiusAndKind(smurfs, fingers, tuioObj, radius, CLOSER_SMUON);
}

vector<Smuon*> SmurfUtils::getSmuonsWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius) {
	return getSmuonsWithinGivenRadiusAndKind(smurfs, fingers, tuioObj, radius, CLOSER_SMUON);
}


Smurf* SmurfUtils::getCloserSmurfWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius) {
	return (Smurf*) getCloserSmuonWithinGivenRadiusAndKind(smurfs, fingers, tuioObj, radius, CLOSER_SMURF);
}


vector<Smuon*> SmurfUtils::getSmurfsWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius) {
	return getSmuonsWithinGivenRadiusAndKind(smurfs, fingers, tuioObj, radius, CLOSER_SMURF);
}


SmurFinger* SmurfUtils::getCloserCursorWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius) {
	return (SmurFinger*) getCloserSmuonWithinGivenRadiusAndKind(smurfs, fingers, tuioObj, radius, CLOSER_CURSOR);
}

vector<Smuon*> SmurfUtils::getCursorsWithinGivenRadius(vector<Smurf*> *smurfs, vector<SmurFinger*> *fingers, ofxTuioContainer *tuioObj, float radius) {
	return getSmuonsWithinGivenRadiusAndKind(smurfs, fingers, tuioObj, radius, CLOSER_CURSOR);
}


// Atypical smurfs creation utilities
//-----------------------------------

Smurf* SmurfUtils::createAtypicalSmurf(Smuon* smuon, SmurfKind kind) {
	if ( smuon == NULL ) return NULL;
	
	SmurFinger *finger = (SmurFinger*) smuon;
	
	if ( finger->getPoints()->size() == 0 ) return NULL;
	
	ofxTuioPoint pt = finger->getPoints()->at(0);
	
	float vID = getNextVirtualID();
	
	ofxTuioObject *tuioObj = new ofxTuioObject(vID, vID, float(pt.getX()), float(pt.getY()), 0.0);
	
	Smurf *smurf = new Smurf(tuioObj, kind);
	smurf->setRadius(50);
	smurf->setProxima(50);
	smurf->setFG(msaColor( 0xAD, 0xEA, 0xEA));
	smurf->setBG(msaColor( 0xAD, 0xEA, 0xEA));
	smurf->setLabelVisible(true);
	
	return smurf;
}

SmurfAnchor* SmurfUtils::createSmurfAnchor(Smuon* smuon, float _ownerId, AnchorKind _anchorKind) {
	ofxTuioPoint pt = ofxTuioPoint(0.5, 0.5);
	
	if ( smuon == NULL ) return NULL;
	
	if (dynamic_cast<SmurFinger*> (smuon)) {	
		SmurFinger *finger = (SmurFinger*) smuon;
	
		if ( finger->getPoints()->size() == 0 ) return NULL;
	
		pt = finger->getPoints()->at(0);
	} else if (dynamic_cast<Smurf*> (smuon)) {
		pt = smuon->getTuio()->getPosition();
	}
	
	float vID = getNextVirtualID();
	
	ofxTuioObject *tuioObj = new ofxTuioObject(vID, vID, float(pt.getX()), float(pt.getY()), 0.0);
	
	SmurfAnchor *smurfAnchor = new SmurfAnchor(_ownerId, tuioObj, ((ofxTuioObject*)smuon->getTuio())->getFiducialId(), SMURF_KIND_ANCHOR, _anchorKind);
	smurfAnchor->setKind(SMURF_KIND_ANCHOR);
	smurfAnchor->setRadius(12);
	smurfAnchor->setProxima(12);
	smurfAnchor->setFG(msaColor( 0xAD, 0xEA, 0xEA));
	smurfAnchor->setBG(msaColor( 0xAD, 0xEA, 0xEA));
	smurfAnchor->setLabelVisible(false);
	
	return smurfAnchor;
}


