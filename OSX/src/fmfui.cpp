/*
 *  fmfui.cpp
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

#include "fmfui.h"

/////////////////////
// SWidget
/////////////////////
void SRotable::onSelection() {

}

void SRotable::onDispose() {

}

void SRotable::onInit() {

}

void SRotable::onPaint() {
	
}

void SRotable::setBorder(float _b) {
	border = _b;
}

float SRotable::getBorder() {
	return border;
}

void SRotable::setAngle(float _a) {
	angle = _a;
}

float SRotable::getAngle() {
	return angle;
}

ofxTuioPoint* SRotable::toWidget(ofxTuioPoint* _pt) {
	return NULL;
}

ofxTuioPoint* SRotable::toUI(ofxTuioPoint* _pt) {
	return NULL;
}

ofxTuioPoint* SRotable::getSize() {
	return size;
}

void SRotable::setSize(ofxTuioPoint* _pt) {
	if ( _pt == NULL) {
		size = new ofxTuioPoint(0.0, 0.0);
	} else {
		if (size != NULL) {
			delete size;
		}
		size = new ofxTuioPoint(_pt->getX(), _pt->getY());
	}
}

/////////////////////
// SControl
/////////////////////

float SControl::getValue() {
	return value;
}

void SControl::getValue(float _value) {
	value = _value;
}

/////////////////////
// SRangeControl
/////////////////////

float SRangeControl::getMin() {
	return min;
}

float SRangeControl::getMax() {
	return max;
}

float SRangeControl::getStep() {
	return step;
}

void SRangeControl::setMin(float _min) {
	min = _min;
}

void SRangeControl::setMax(float _max) {
	max = _max;
}

void SRangeControl::setStep(float _step) {
	step = _step;
}


/////////////////////
// SWidget
/////////////////////

void SWidget::draw() {
	ofRectangle(0.0, 0.0, getSize()->getX(), getSize()->getY());
}

SLayoutData* SWidget::getLayoutData() {
	return layoutData;
}

void SWidget::getLayoutData(SLayoutData* _layoutData) {
	layoutData = _layoutData;
}

void SWidget::setStyle(FmfUiCst _style) {
	style = _style;
}

FmfUiCst SWidget::getStyle() {
	return style;
}

/////////////////////
// SComposite
/////////////////////

vector<SWidget*>* SComposite::getChildren() {
	return children;
}

void SComposite::layout() {
	

}

void SComposite::setLayout(SLayout* _layout) {
	slayout = _layout;
}

SLayout* SComposite::getLayout() {
	return slayout;
}

void SComposite::draw(){
	if (getChildren() != NULL) {	
		// Don't forget to draw yourself !!!
		vector<SWidget*> *swiIt=getChildren();
		if (swiIt != NULL) {
			for (int i=0; i<swiIt->size(); i++) {
				swiIt->at(i)->draw();
			}
		}
	}
}


/////////////////////
// SWindow
/////////////////////

void SWindow::setZOrder(int _zo) {
	zorder = _zo;
}

int SWindow::getZOrder() {
	return zorder;
}

SComposite* SWindow::getContent() {
	return content;
}

/////////////////////
// UIManager
/////////////////////

vector<SWindow*>* UIManager::getWindows() {
	return windows;
}

vector<SmurFinger*>* UIManager::getCursors() {
	return cursors;
}

