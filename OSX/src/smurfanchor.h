/*
 *  smurfanchor.h
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

#ifndef _SMURF_ANCHOR
#define _SMURF_ANCHOR

#include "smurf.h"
#include "ofxTuio.h"


enum AnchorKind {
	ANCHOR_KIND_INPUT,
	ANCHOR_KIND_OUTPUT
};


class SmurfAnchor : public Smurf {
private:
	float ownerFid;
	float ownerSid;
	AnchorKind anchorKind;
public:
	SmurfAnchor(float _sid, ofxTuioObject *_tuioObj, float _fid, SmurfKind _kind, AnchorKind _anchorStyle) : Smurf(_tuioObj, kind) {
		setOwnerFid(_fid);
		setOwnerSid(_sid);
		setAnchorKind(_anchorStyle);
		setRadius(2);
		setProxima(2);
	}
	
	float getOwnerFid();
	void setOwnerFid(float _fid);
	
	float getOwnerSid();
	void setOwnerSid(float _sid);
	
	AnchorKind getAcnhorKind();
	void setAnchorKind(AnchorKind _kind);
	
	void draw();
};

#endif