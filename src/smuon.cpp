/*
 *  smuon.cpp
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

#include "smuon.h"
#include "ofxTuio.h"


// DTOR
Smuon::~Smuon() {

}


Smuon::Smuon(ofColor _bg, ofColor _fg) {
	Smuon();
}

Smuon::Smuon(ofColor _bg, ofColor _fg, int _radius) {
	Smuon(_bg, _fg);
	radius = _radius;
}

Smuon::Smuon(ofColor _bg, ofColor _fg, int _radius, bool _visible) {
	Smuon(_bg, _fg, _radius);
	visible = _visible;
}

Smuon::Smuon(ofColor _bg, ofColor _fg, int _radius, bool _visible, bool _enabled) {
	Smuon(_bg, _fg, _radius, _visible);
	enabled = _enabled;
}

float Smuon::getRadius() {
	return radius;
}

void Smuon::setRadius(float _radius) {
	radius = _radius;
} 

float Smuon::getProxima() {
	return proxima;
}

void Smuon::setProxima(float _proxima) {
	proxima = _proxima;
} 

void Smuon::setBG(ofColor _bg) {
	bg = _bg;
}

ofColor Smuon::getBG() {
	return bg;
}

ofxTuioContainer* Smuon::getTuio() {
	return tuio;
}

void Smuon::setFG(ofColor _fg) {
	fg = _fg;
}

ofColor Smuon::getFG() {
	return fg;
}

bool Smuon::isEnabled() {
	return enabled;
}

bool Smuon::isVisible() {
	return visible;
}

void Smuon::setEnabled(bool _enabled) {
	enabled = _enabled;
}

void Smuon::setVisible(bool _visible) {
	visible = _visible;
}

void Smuon::setTuio(ofxTuioContainer* _tuio) {
	tuio = _tuio;
}

bool Smuon::isSelected() {
	return selected;
}

void Smuon::setSelected(bool _selected) {
	selected = _selected;
}

float Smuon::getDragging() {
	return dragging;
}

void Smuon::setDragging(float sid) {
	dragging = sid;
}

void Smuon::toggleSelected() {
	selected = selected==true?false:true;
}

bool Smuon::isAlreadyDragging() {
	return dragging == -FLT_MAX;
}

bool Smuon::isProximaVisible() {
	return proximaVisible;
}
void Smuon::setProximaVisible(bool _status) {
	proximaVisible = _status;
}

bool Smuon::isLabelVisible() {
	return labelVisible;
}

void Smuon::setLabelVisible(bool _status) {
	labelVisible = _status;
}


