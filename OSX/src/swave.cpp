/*
 *  swave.cpp
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

#include "swave.h"

SWave::SWave(int _fidId, int _uid, int _x, int _y, int _range) {
	fidId = _fidId;
	x = _x;
	y = _y;
	uid = _uid;
	radius = 0;
	range = _range;
}

int SWave::getUid() {
	return uid;
}

void SWave::setRadius(int _radius) {
	radius = _radius;
}

int SWave::getRadius() {
	return radius;
}

int SWave::getX() {
	return x;
}

int SWave::getY() {
	return y;
}

int SWave::getRange() {
	return range;
}

int SWave::getFid() {
	return fidId;
}

void SWave::draw() {
	ofSetLineWidth(1);
    ofCircle(getX(), getY(), getRadius());
}

