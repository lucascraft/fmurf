/*
 *  smuon.h
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


#ifndef _SMUON
#define _SMUON

#include "ofxVectorGraphics.h"
#include "ofxTuio.h"

class Smuon {
	
protected:
	ofColor bg, fg;
	
	float radius;
	float proxima;
    bool visible;
	bool enabled;
	bool selected;
	float dragging;
	bool proximaVisible;
	bool labelVisible;

	ofxTuioContainer* tuio;
	
public:
	ofColor SMUON_DEFAULT_BG, SMUON_DEFAULT_FG;
	
	Smuon() {
		SMUON_DEFAULT_BG = ofColor();
		SMUON_DEFAULT_BG.r = 255;
		SMUON_DEFAULT_BG.g = 123;
		SMUON_DEFAULT_BG.b = 122;
		
		SMUON_DEFAULT_FG = ofColor();
		SMUON_DEFAULT_FG.r = 123;
		SMUON_DEFAULT_FG.g = 255;
		SMUON_DEFAULT_FG.b = 122;

		bg = SMUON_DEFAULT_BG;
		fg = SMUON_DEFAULT_FG;
		
		radius = 20;
		proxima = 75;
		visible = true;
		enabled = true;	
		dragging = false;
		proximaVisible = false;
		labelVisible = true;
	}
	
	Smuon(ofColor _bg, ofColor _fg);
	Smuon(ofColor _bg, ofColor _fg, int _radius);
	Smuon(ofColor _bg, ofColor _fg, int _radius, bool _visible);
	Smuon(ofColor _bg, ofColor _fg, int _radius, bool _visible, bool _enabled);
	
	virtual ~Smuon();
	
	//
	void setFG(ofColor _fg);
	void setBG(ofColor _bg);
	void setVisible(bool _visible);
	void setEnabled(bool _enabled);
	void setRadius(float _radius);	
	void setProxima(float _proxima);	
	void setTuio(ofxTuioContainer* _tuio);
	void setDragging(float _dragging);
	void setSelected(bool _selected);
	void setProximaVisible(bool _status);
	void setLabelVisible(bool _status);

	//
	ofColor getFG();
	ofColor getBG();
	bool isEnabled();
	bool isVisible();
	float getDragging();
	float getRadius();
	float getProxima();
	bool isSelected();
	ofxTuioContainer* getTuio();
	bool isAlreadyDragging();
	void toggleSelected();
	bool isProximaVisible();
	bool isLabelVisible();
	
};
#endif