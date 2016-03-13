/*
 *  fmfutils.h
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

#ifndef _FMF_UTILS
#define _FMF_UTILS

#include "smurf.h"
#include "fmftypes.h"


enum FMFType {
	FMF_TYPE_OSC,
	FMF_TYPE_PHAZOR,
	FMF_TYPE_MULT,
	FMF_TYPE_SEQUENCER,
	FMF_TYPE_SAMPLER,
	FMF_TYPE_ADD,
	FMF_TYPE_TEMPO,
	FMF_TYPE_DAC
};

class FMFUtils  {
private:
	Smurf* createFMFElement(FMFType _type, float _fid);
public:
	FMFUtils();
	~FMFUtils();
	FMFDac* createDAC(float _fid);
	FMFOscillator* createOSC(float _fid);
	FMFPhazor* createPHAZOR(float _fid);
	FMFMultiply* createMULT(float _fid);
	FMFAdd* createADD(float _fid);
	FMFSequencer* createSEQUENCER(float _fid);
	FMFSampler* createSAMPLER(float _fid);
	FMFTempo* createTEMPO(float _fid);
};

#endif