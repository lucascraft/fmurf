/*
 *  testApp.h 
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

#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofEvents.h"

#include "ofxVectorGraphics.h"

#include "smuon.h"
#include "smurf.h"
#include "smurfloor.h"
#include "smurfcfg.h"

#include "fmfutils.h"

#include "ofxTuio.h"

#include "ofxMSAFluid.h"
#include "ParticleSystem.h"

#include "ofxSimpleGuiToo.h"


#define tuioCursorSpeedMult				1	// the iphone screen is so small, easy to rack up huge velocities! need to scale down 
#define tuioStationaryForce				1.0f	// force exerted when cursor is stationary

#define GESTURES_ENABLED


class fmfApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		// SMURF it up !
	
		Smurfloor *smurfFloor;
		SmurfCfg *smurfCfg;
		
		FMFUtils *synthUtils;
	
		void drawWaves();
		void drawConnections();
		void drawSmurfs();
		void drawWindows();
		void drawFingers();
		void smurfCollisionComputation(SWave *wave);
		void handleAnchorsUpdate(SConnection *_connection);
	
		// ofxTUIO
	
		myTuioClient tuio;
	
	
	// MSA Fluid !
	
	void addToFluid(float x, float y, float dx, float dy, bool addColor = true, bool addForce = true);
	
	int					fluidCellsX;
	bool				resizeFluid;
	bool				drawFluid;
	bool				drawParticles;
	bool				renderUsingVA;
	
	ofxMSAFluidSolver	fluidSolver;
	ofxMSAFluidDrawer	fluidDrawer;	
	
	ParticleSystem		particleSystem;
	
	int					pmouseX, pmouseY;
	
	// cache these for slightly better performance
	struct {
		int				width;
		int				height;
		float			invWidth;
		float			invHeight;
		float			aspectRatio;
		float			aspectRatio2;
	} window;
	
	ofxOscSender *sender;
	ofxOscReceiver *receiver;

	ofxSimpleGuiToo	gui;

	ofTrueTypeFont *font;	

};

extern fmfApp *myApp;

#endif

