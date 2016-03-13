/*
 *  fmftypes.h
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

#ifndef _FMF_TYPES
#define _FMF_TYPES

#include "smurf.h"

class FMFOscillator : public Smurf {
public:
	FMFOscillator(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}
};

class FMFPhasor : public Smurf {
public:
	FMFPhasor(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

class FMFAdd : public Smurf {
public:
	FMFAdd(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

class FMFMultiply : public Smurf {
public:
	FMFMultiply(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

class FMFDac : public Smurf {
public:
	FMFDac(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

class FMFSequencer : public Smurf {
public:
	FMFSequencer(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

class FMFTempo : public Smurf {
public:
	FMFTempo(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

class FMFSampler : public Smurf {
public:
	FMFSampler(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		
	}	
};

#endif