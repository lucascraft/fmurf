/*
 *  fmfutils.cpp
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

#include "fmfutils.h"
#include "ofxTuio.h"
#include "ofxMSAUtils.h"

FMFUtils::FMFUtils() {

}

Smurf* FMFUtils::createFMFElement(FMFType _type, float _fid){

	switch (_type) {
		case FMF_TYPE_ADD:
			return createADD(_fid);
		case FMF_TYPE_DAC:
			return createDAC(_fid);
		case FMF_TYPE_OSC:
			return createOSC(_fid);
		case FMF_TYPE_SIN_OSC:
			return createSinOSC(_fid);
		case FMF_TYPE_SQR_OSC:
			return createSqrOSC(_fid);
		case FMF_TYPE_SAWTOOTH_OSC:
			return createSawtoothOSC(_fid);
		case FMF_TYPE_TRIANGLE_OSC:
			return createTriangleOSC(_fid);
		case FMF_TYPE_PULSE_OSC:
			return createPulseOsc(_fid);
		case FMF_TYPE_PHASOR:
			return createPHASOR(_fid);
		case FMF_TYPE_MULT:
			return createMULT(_fid);
		case FMF_TYPE_SAMPLER:
			return createSAMPLER(_fid);
		case FMF_TYPE_SEQUENCER:
			return createSEQUENCER(_fid);
		case FMF_TYPE_TEMPO:
			return createTEMPO(_fid);
		default:
			break;
	}
	return NULL;
}


FMFDac* FMFUtils::createDAC(float _fid) {
	FMFDac* dac = new FMFDac(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	dac->setBG(msaColor(0xA8, 0xA8, 0xA8));
	dac->setFG(msaColor(0xA8, 0xA8, 0xA8));
	dac->setLabelVisible(false);
	dac->setRadius(18);
	return dac;
}

FMFSqrOsc* FMFUtils::createSqrOSC(float _fid) {
	FMFSqrOsc* osc = new FMFSqrOsc(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return osc;
}

FMFSinOsc* FMFUtils::createSinOSC(float _fid) {
	FMFSinOsc* osc = new FMFSinOsc(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return osc;
}

FMFTriangleOsc* FMFUtils::createTriangleOSC(float _fid) {
	FMFTriangleOsc* osc = new FMFTriangleOsc(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return osc;
}

FMFSawtoothOsc* FMFUtils::createSawtoothOSC(float _fid) {
	FMFSawtoothOsc* osc = new FMFSawtoothOsc(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return osc;
}

FMFPulseOsc* FMFUtils::createPulseOsc(float _fid) {
	FMFPulseOsc* osc = new FMFPulseOsc(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return osc;
}

FMFOscillator* FMFUtils::createOSC(float _fid) {
	FMFOscillator* osc = new FMFOscillator(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return osc;
}

FMFPhasor* FMFUtils::createPHASOR(float _fid) {
	FMFPhasor* phasor = new FMFPhasor(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return phasor;
}

FMFMultiply* FMFUtils::createMULT(float _fid) {
	FMFMultiply* mult = new FMFMultiply(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return mult;
}

FMFAdd* FMFUtils::createADD(float _fid) {
	FMFAdd *add = new FMFAdd(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return add;
}

FMFSequencer* FMFUtils::createSEQUENCER(float _fid) {
	FMFSequencer *sequencer = new FMFSequencer(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return sequencer;
}

FMFSampler* FMFUtils::createSAMPLER(float _fid) {
	FMFSampler *sampler = new FMFSampler(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return sampler;
}

FMFTempo* FMFUtils::createTEMPO(float _fid) {
	FMFTempo *tempo = new FMFTempo(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	return tempo;
}

