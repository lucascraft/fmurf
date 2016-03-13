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
		setNature("OSCILLATOR");
	}
	
	void draw() {
		Smurf::draw();
	}
};

class FMFSqrOsc : public FMFOscillator {
public:
	FMFSqrOsc(ofxTuioObject *_tuioObj, SmurfKind _kind) : FMFOscillator(_tuioObj, kind) {
		setNature("SQR_OSC");
	}
	
	void draw() {
		FMFOscillator::draw();
	}
};

class FMFSinOsc : public FMFOscillator {
public:
	FMFSinOsc(ofxTuioObject *_tuioObj, SmurfKind _kind) : FMFOscillator(_tuioObj, kind) {
		setNature("SIN_OSC");
	}
	
	void draw() {
		FMFOscillator::draw();
	}
};

class FMFTriangleOsc : public FMFOscillator {
public:
	FMFTriangleOsc(ofxTuioObject *_tuioObj, SmurfKind _kind) : FMFOscillator(_tuioObj, kind) {
		setNature("TRIANGLE_OSC");
	}
	
	void draw() {
		FMFOscillator::draw();
	}
};

class FMFSawtoothOsc : public FMFOscillator {
public:
	FMFSawtoothOsc(ofxTuioObject *_tuioObj, SmurfKind _kind) : FMFOscillator(_tuioObj, kind) {
		setNature("SAWTOOTH_OSC");
	}
	
	void draw() {
		FMFOscillator::draw();
	}
};

class FMFPulseOsc : public FMFOscillator {
public:
	FMFPulseOsc(ofxTuioObject *_tuioObj, SmurfKind _kind) : FMFOscillator(_tuioObj, kind) {
		setNature("PULSE_OSC");
	}
	
	void draw() {
		FMFOscillator::draw();
	}
};


class FMFPhasor : public Smurf {
public:
	FMFPhasor(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		setNature("PHASOR");
	}	

	void draw() {
		Smurf::draw();
	}
};

class FMFAdd : public Smurf {
public:
	FMFAdd(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		setNature("ADD");
	}	
	
	void draw() {
		Smurf::draw();
	}
};

class FMFMultiply : public Smurf {
public:
	FMFMultiply(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		setNature("MULTIPLY");
	}	
	
	void draw() {
		Smurf::draw();
	}
};

class FMFDac : public Smurf {
public:
	FMFDac(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		setNature("DAC");
	}	
	
	void draw() {
		Smurf::draw();
	}
};

class FMFSequencer : public Smurf {
public:
	FMFSequencer(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		ofxOscMessage *msg = new ofxOscMessage();
		
		setSlot(_A, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_B, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_C, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_D, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_E, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_F, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_G, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_H, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_I, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_J, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_K, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_L, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_M, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_N, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_O, TOGGLE, SLOT_VISUAL_BOX, msg);
		setSlot(_P, TOGGLE, SLOT_VISUAL_BOX, msg);
		
		setNature("SEQUENCER");
	}	
	
	void draw() {
		Smurf::draw();
	}
};

class FMFTempo : public Smurf {
public:
	FMFTempo(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		setNature("TEMPO");
	}	
	
	void draw() {
		Smurf::draw();
	}
};

class FMFSampler : public Smurf {
public:
	FMFSampler(ofxTuioObject *_tuioObj, SmurfKind _kind) : Smurf(_tuioObj, kind) {
		setNature("SAMPLER");
	}	
	
	void draw() {
		Smurf::draw();
	}
};

#endif