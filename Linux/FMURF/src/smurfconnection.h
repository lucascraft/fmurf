/*
 *  smurfconnection.h
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

#ifndef _SMURF_CONNECTION
#define _SMURF_CONNECTION

#include "ofxTuio.h"
#include "smurfanchor.h"

enum SConnectKind {
	CONNECT_INPUT,
	CONNECT_OUTPUT,
	CONNECT_INOUT,
	CONNECT_UNKNOWN
};

enum SConnectionVisual {
	CONNECTION_SQUARE_FREQ,
	CONNECTION_TRIANGLE_FREQ,
	CONNECTION_SIN_FREQ,
	CONNECTION_CHUNKS,
	CONNECTION_DOTS,
	CONNECTION_LINE
};


class SConnection {
private: 
	SConnectKind kind;
	SConnectionVisual visual;
	SmurfAnchor *fAnchor;
	SmurfAnchor *tAnchor;
	vector<float> *liveData;
	bool enabled;
public:
	SConnection(SmurfAnchor *_from, SmurfAnchor *_to, SConnectionVisual _visual, SConnectKind _kind);
	SConnection(SmurfAnchor *_from, SmurfAnchor *_to, SConnectionVisual _visual);
	
	float fromID();
	void setFromID(float _fromID);
	
	float toID();
	void setToID(float _toID);
	
	SmurfAnchor *fromAnchor();
	void setFromAnchor(SmurfAnchor *_from);
	
	SmurfAnchor *toAnchor();
	void setToAnchor(SmurfAnchor *_to);
	
	void setConnectionKind(SConnectKind _kind);
	SConnectKind getConnectionKind();
	
	void setConnectionVisual(SConnectionVisual _kind);
	SConnectionVisual getConnectionVisual();
	
	vector<float>* getLiveData();
	void setLiveData(vector<float> *_liveData);
	
	void draw(vector<float> *_livedata);
	
	bool isEnabled();
	void setEnabled(bool _status);
	void toggleEnabled();
};

#endif