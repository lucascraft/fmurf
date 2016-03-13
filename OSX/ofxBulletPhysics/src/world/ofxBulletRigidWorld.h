/*
 *  ofxBulletRigidWorld.h
 *  ofxBulletPhysics demo
 *
 *  Created by Mehmet Akten on 21/06/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

// container for rigid body objects only

#pragma once

#include "ofxBulletWorldBase.h"

class ofxBulletRigidWorld : public ofxBulletWorldBase {
public:

	
protected:
	btDynamicsWorld* createBulletWorld() {
		return new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	}
};