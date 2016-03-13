/*
 *  smurfcfg.h
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


#ifndef _SMURF_CFG
#define _SMURF_CFG

#include "ofxMSAUtils.h"
#include "ofxXmlSettings.h"
#include "smurf.h"

//-----------------------------------------------------------
//
// Configuration file for Puredata <-> TUIO fiducial mapping.
//
//-----------------------------------------------------------
class SmurfDetails {
public:
	float uid;
	float sessionId;
	msaColor bg;
	msaColor fg;
	SmurfAspect aspect;
	float radius;
	float proxima;
	float range;
	SmurfFunction function;
	string kind;
	bool proximaVisible;
	SmurfDetails(
				 float _uid, 
				 float _sessionId, 
				 msaColor _bg, 
				 msaColor _fg, 
				 SmurfAspect _aspect, 
				 float _radius, 
				 float _proxima, 
				 float _range, 
				 SmurfFunction function, 
				 string kindID, 
				 bool proximaVisible
	);
};

class SmurfCfg {
private:
	ofxXmlSettings  XML;
	
	int tuioPort;

	string oscSendAddress;
	int oscSendPort;
	int oscReceivePort;
	
protected:
	map<string, msaColor> colors;
	map<float, SmurfDetails*> details;
	
public:
	SmurfCfg();
	
	//void initTheFloor(Smurfloor *_floor);
	void initSettings();
	void initColors();
	
	// Smurf attributes 
	msaColor getColor(int _idx);
	msaColor getColor(string _name);
	SmurfAspect getStyle(string _style);
	SmurfFunction getFunction(string _function);

	void setTuioPort(int _port);
	int getTuioPort();
	
	void setOscSendAddress(string _address);
	string getOscSendAddress();
	
	void setOscSendPort(int _port);
	int getOscSendPort();
	
	void setOscReceivePort(int _port);
	int getOscReceivePort();
	
	SmurfDetails* getSmurfDetails(float _uid);
};


#endif