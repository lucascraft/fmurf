/*
 *  fmfui.h
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

#ifndef _FMFUI
#define _FMFUI

#include "smuon.h"
#include "smurfinger.h"

/////////////////
// SLayout
/////////////////

class SLayout  {
public:
//	virtual void layout(SComposite* _composite);
//	virtual void layout(SComposite* _composite, bool _force);
//	virtual ofPoint computeSize(SComposite* _composite, float _hHint, float _vHint);
	SLayout() {
	}
};

class SLayoutData  {	
};

class SGridLayout : public SLayout {
	int nCol;
	bool equalWidth;
	
	SGridLayout(int _col, bool _equals) : SLayout() {
		nCol = _col;
		equalWidth = _equals;
	}
	
//	for (int n=0; n<nCol; n++) {
//	}
};

enum GRID_DATA {
	GRID_DATA_VERTICAL_ALIGN_BEGIN,
	GRID_DATA_VERTICAL_ALIGN_END,
	GRID_DATA_VERTICAL_ALIGN_CENTER,
	GRID_DATA_VERTICAL_ALIGN_FILL,
	GRID_DATA_HORIZONTAL_ALIGN_BEGIN,
	GRID_DATA_HORIZONTAL_ALIGN_END,
	GRID_DATA_HORIZONTAL_ALIGN_CENTER,
	GRID_DATA_HORIZONTAL_ALIGN_FILL
	// To be continued ...
};

class SGridData : public SLayoutData {
private:
	GRID_DATA hAlign, vAlign;
	bool grabHExcess, grabVExcess;
public:
	SGridData(GRID_DATA _hAlign, GRID_DATA _vAlign, bool _grabHExcess, bool _grabVExcess) {
		hAlign = _hAlign;
		vAlign = _vAlign;
		grabHExcess = _grabHExcess;
		grabVExcess = _grabVExcess;
	}
//	GRID_DATA getGridData(SControl[][] _controls, int _row, int _col, int _rowCount, int _colCount);
};

/////////////////
// SRotable
/////////////////

class SRotable : public Smuon {
private:
	ofxTuioPoint* size;
	float angle;
	float border;
public:
	void onInit();
	void onDispose();
	void onSelection();
	void onPaint();
	
	void setBorder(float _b);
	float getBorder();
	
	void setAngle(float _a);
	float getAngle();
	
	ofxTuioPoint* toWidget(ofxTuioPoint* _pt);
	ofxTuioPoint* toUI(ofxTuioPoint* _pt);
	
	ofxTuioPoint* getSize();
	void setSize(ofxTuioPoint* _pt);
	
	SRotable(float _w, float _h, float _angle) : Smuon() {
		size = new ofxTuioPoint(_w, _h); // pixels
		angle = _angle; // degrees
		border = 10.0;
	}
	
	SRotable() {
		SRotable(50.0, 50.0, 0.0); // pixels & degrees
	}
};

enum FmfUiCst {
	FMF_CONTROL_HORIZONTAL,
	FMF_CONTROL_VERTICAL,
	FMF_BUTTON_PUSH,
	FMF_BUTTON_TOGGLE,
	FMF_NONE
};


/////////////////
// SWidget
/////////////////

class SWidget : public SRotable {
private:
	SLayoutData* layoutData;
	FmfUiCst style;
public:
	virtual void draw();
	SLayoutData* getLayoutData();
	void getLayoutData(SLayoutData* layoutData);
	void setStyle(FmfUiCst _style);
	FmfUiCst getStyle();
	SWidget(FmfUiCst _style, float _w, float _h, float _angle) : SRotable(_w, _h, _angle) {
		style = _style;
	}
	SWidget() {
		SWidget(FMF_NONE, 50.0, 50.0, 45.0);
	}
};


/////////////////
// SComposite
/////////////////

class SComposite : public SWidget {
private:
	vector<SWidget*>* children;
	SLayout* slayout;
public:
	vector<SWidget*>* getChildren();
	void layout();
	void setLayout(SLayout* _layout);
	SLayout* getLayout();
	void draw();
	SComposite(FmfUiCst _style, float _w, float _h, float _angle) : SWidget(_style, _w, _h, _angle) {
		children = new vector<SWidget*>();
	}
	SComposite() {
		SComposite(FMF_NONE, 50.0, 50.0, 33.0);
	}
};

/////////////////
// SWindow
/////////////////

class SWindow : public SRotable {
private:
	int zorder;
	SComposite* content;
public:
	void setZOrder(int _zo);
	int getZOrder();
	SComposite* getContent();
	SWindow(Smuon *smuon) : SRotable() {
		content = new SComposite(FMF_NONE, 140.0, 80.0, 45.0);
		setSize(content->getSize());
		float x = smuon->getTuio()->getPosition().getX();
		float y = smuon->getTuio()->getPosition().getY();
		setTuio(new ofxTuioContainer(-333, x, y));
		setBorder(10.0);
	}
	void layout() {
		content->layout();
	}
	void draw() {
		SWindow::draw(NULL);
	}
	void draw(ofTrueTypeFont *_font) {
		ofPushMatrix();
			if (getTuio() != NULL) {
				ofxTuioPoint center = getTuio()->getPosition();
				float x = center.getX() * ofGetWidth();
				float y = center.getY() * ofGetHeight();
				ofTranslate(x, y, 0.0);
				ofRotate(ofDegToRad(getAngle()), 0.0, 0.0, 1.0);
				ofxTuioPoint *size = getSize();
				ofFill();
				ofSetColor(getBG().r, getBG().g, getBG().b);
				float borderPlusWidth = size->getX() + getBorder()*2;
				float borderPlusHeight = size->getY() + getBorder()*2;
				ofRect(-borderPlusWidth/2, -borderPlusHeight/2, borderPlusWidth, borderPlusHeight);
				ofSetColor(getFG().r, getFG().g, getFG().b);
				ofRect(-size->getX()/2, -size->getY()/2, size->getX(), size->getY());
			}
			layout();
			if (content != NULL) {
				content->draw();
			}
		ofPopMatrix();
	}
};

/////////////////
// Controls
/////////////////

class SControl : public SWidget {
private:
	float value;
public:
	float getValue();
	void getValue(float _value);
	SControl() : SWidget() {}
};

class SButton : public SControl {
private:

public:
	SButton() : SControl() {}
};

class SRangeControl : public SControl {
private:
	float min;
	float max;
	float step;
	float position;
public:
	virtual float getMin();
	virtual float getMax();
	virtual float getStep();
	virtual void setMin(float _min);
	virtual void setMax(float _max);
	virtual void setStep(float _step);
	SRangeControl(float _min, float _max, float _step, float _position) : SControl() {
		min = _min;
		max = _max;
		step = _step;
		position = _position;
	}
};

class SSlider : public SRangeControl {
private:
	float hCursor;
	float vCursor;
public:	
	FmfUiCst orientation;
	
	SSlider(float _min, float _max, float _step, float _position, float _hCursor, float _vCursor, FmfUiCst _orientation) : SRangeControl(_min, _max, _step, _position) {
		hCursor = _hCursor;
		vCursor = _vCursor;
		orientation = _orientation;
	}
};

class SKnob : public SRangeControl {
	SKnob(float _min, float _max, float _step, float _position) : SRangeControl(_min, _max, _step, _position) {}
};

class SLabel : public SControl {
	SLabel() : SControl() {}
};

class SImage : public SControl {
	SImage() : SControl() {}
};

class SVideo : public SControl {
	SVideo() : SControl() {}
};

//class SMultiChannel : public SControl {
//private:
//	vector<float> values;
//public:
//	
//}

class SRadar : public SControl {
private:
	float hMin;
	float hMax;
	float hStep;
	float vMin;
	float vMax;
	float vStep;
	ofPoint position;
	float cursorRadius;
public:
	float getHMin();
	float getHMax();
	float getHStep();
	float getVMin();
	float getVMax();
	float getVStep();
	float getPosition();
	void setHMin(float _hMin);
	void setHMax(float _hMax);
	void setHStep(float _hStep);
	void setVMin(float _vMin);
	void setVMax(float _vMax);
	void setVStep(float _vStep);
	void setPosition(ofPoint pt);
	
	SRadar(float _hMin, float _hMax, float _hStep, float _vMin, float _vMax, float _vStep, ofPoint _pos, float _cursorRadius) : SControl() {
		hMin = _hMin;
		hMax = _hMax;
		hStep = _hStep;
		vMin = _vMin;
		vMax = _vMax;
		vStep = _vStep;
		position = _pos;
		cursorRadius = _cursorRadius;
	}
};

class SList : public SControl {
	
	SList() : SControl() {
		
	}
};

class SCombo : public SControl {
	
	SCombo() : SControl() {
		
	}
};

class SCanvas : public SControl {
	
	SCanvas() : SControl() {
		
	}
};

// Later on ... Need a stack layout prior doing that properly ?
class STabContainer : public SComposite {
	
	STabContainer() : SComposite() {
		
	}
};

class STabItem : public SComposite {
	
	STabItem() : SComposite() {
		
	}
};

/////////////////
// UI Manager
/////////////////

class UIManager {
private:
	vector<SWindow*> *windows;
	vector<SmurFinger*> *cursors;
public:
	UIManager() {
		windows = new vector<SWindow*>();
		cursors = new vector<SmurFinger*>();
	}	
	vector<SWindow*>* getWindows();
	vector<SmurFinger*>* getCursors();
	void draw() {
		for (vector<SWindow*>::iterator winIt=getWindows()->begin(); winIt != getWindows()->end(); winIt++) {
			SWindow* window = *winIt;
			ofPushMatrix();
			ofTranslate(
				window->getTuio()->getPosition().getX()*ofGetWidth(), 
				window->getTuio()->getPosition().getY()*ofGetHeight(), 
				0.0
			);
			ofRotate(
				window->getAngle(), 
				0.0, 
				0.0, 
				1.0
			);
			ofFill();
			window->draw();
			ofPopMatrix();
		}
	}
};

#endif