/*
 *  ofxBulletRigidWorld.h
 *  ofxBulletPhysics demo
 *
 *  Created by Mehmet Akten on 21/06/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

// container for soft body and rigid body objects

#pragma once

#include "ofxBulletWorldBase.h"

class ofxBulletSoftWorld : public ofxBulletWorldBase {
public:
	
	
protected:
	btDynamicsWorld* createBulletWorld() {
		//return new btSoftRigidDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	}
};