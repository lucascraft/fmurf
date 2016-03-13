/*
 *  wiistuff.h
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
 *
 */

#ifndef _WII_STUFF
#define _WII_STUFF

#include "ofMain.h"

class WiimoteEvent {
	string id;
	float x, y, z;
	int b1, b2;
};


class WiiStuff {
//	Poco::EventType<const WiimoteEvent> wiimoteEventDispatcher;
};

#endif