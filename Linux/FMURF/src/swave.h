/*
 *  swave.h
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

#ifndef _SMURF_WAVE
#define _SMURF_WAVE

#include "smuon.h"
#include "smurfer.h"

#include "ofxTuio.h"

class SWave {
private:
	int fidId;
	int x;
	int y;
	int radius;
	int uid;
	int range;
public:
	SWave(int _fid, int _uid, int _x, int _y, int _range);
	int getUid();
	void setRadius(int _radius);
	int getRadius();
	int getX();
	int getY();
	void draw();
	int getRange();
	int getFid();
};


#endif