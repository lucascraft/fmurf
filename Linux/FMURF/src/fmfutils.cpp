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
		case FMF_TYPE_PHAZOR:
			return createPHAZOR(_fid);
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
	dac->setKind(SMURF_KIND_TANGIBLE);
	dac->setBG(msaColor(0xA8, 0xA8, 0xA8));
	dac->setFG(msaColor(0xA8, 0xA8, 0xA8));
	dac->setLabelVisible(false);
	dac->setRadius(18);
	return dac;
}

FMFOscillator* FMFUtils::createOSC(float _fid) {
	FMFOscillator* osc = new FMFOscillator(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	osc->setKind(SMURF_KIND_TANGIBLE);
	return osc;
}

FMFPhasor* FMFUtils::createPHAZOR(float _fid) {
	FMFPhasor* phazor = new FMFPhasor(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	phazor->setKind(SMURF_KIND_TANGIBLE);
	return phazor;
}

FMFMultiply* FMFUtils::createMULT(float _fid) {
	FMFMultiply* mult = new FMFMultiply(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	mult->setKind(SMURF_KIND_TANGIBLE);
	return mult;
}

FMFAdd* FMFUtils::createADD(float _fid) {
	FMFAdd *add = new FMFAdd(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	add->setKind(SMURF_KIND_TANGIBLE);
	return add;
}

FMFSequencer* FMFUtils::createSEQUENCER(float _fid) {
	FMFSequencer *sequencer = new FMFSequencer(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	sequencer->setKind(SMURF_KIND_TANGIBLE);
	return sequencer;
}

FMFSampler* FMFUtils::createSAMPLER(float _fid) {
	FMFSampler *sampler = new FMFSampler(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	sampler->setKind(SMURF_KIND_TANGIBLE);
	return sampler;
}

FMFTempo* FMFUtils::createTEMPO(float _fid) {
	FMFTempo *tempo = new FMFTempo(new ofxTuioObject(_fid, _fid, 0.5, 0.5, 0.0), SMURF_KIND_TANGIBLE);
	tempo->setKind(SMURF_KIND_TANGIBLE);
	return tempo;
}

