/***********************************************************************

 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

#pragma once

#include "ofMain.h"
#include "ofxObjCPointer.h"

#include "ofxMSAPhysicsParams.h"

class ofxMSAParticle : public ofPoint, public ofxObjCPointer {
public:
	friend class ofxMSAPhysics;

	ofxMSAParticle(float x = 0, float y = 0, float z = 0, float mass = 1.0f, float drag = 1.0f);
	ofxMSAParticle(ofPoint &v, float m = 1.0f, float d = 1.0f);
	ofxMSAParticle(ofxMSAParticle &p);

	virtual void	init(float x, float y, float z, float m = 1.0f, float d = 1.0f);

	ofxMSAParticle* setMass(float t = 1);
	float			getMass();
	float			getInvMass();

	ofxMSAParticle* setDrag(float t = 1);
	float			getDrag();

	ofxMSAParticle* setBounce(float t = 1);
	float			getBounce();

	ofxMSAParticle* setRadius(float t = 15);
	float			getRadius();

	// even with collision disabled you can still create your own collision constraint between two particles
	ofxMSAParticle* enableCollision();
	ofxMSAParticle* disableCollision();
	bool			hasCollision();

	bool			isFixed();
	bool			isFree();
	ofxMSAParticle* makeFixed();
	ofxMSAParticle* makeFree();

	ofxMSAParticle* moveTo(ofPoint &targetPos);
    ofxMSAParticle* moveBy(ofPoint &diffPos);
    ofxMSAParticle* moveTo(float x, float y, float z);
    ofxMSAParticle* moveBy(float x, float y, float z);

    ofxMSAParticle* setVelocity(ofPoint &vel);
    ofxMSAParticle* setVelocity(float x, float y, float z);
    ofxMSAParticle* addVelocity(ofPoint &vel);
    ofxMSAParticle* addVelocity(float x, float y, float z);
	ofPoint&		getVelocity();

	// override these functions if you create your own particle type with custom behaviour and/or drawing
	virtual void	update() {}
	virtual void	draw() {}

	void			kill();
	bool			isDead();

	bool			isInSameBinAs(ofxMSAParticle* p);

	ofxMSAPhysicsParams *getParams();

protected:
	ofxMSAPhysicsParams *_params;
	ofxMSAPhysics		*_physics;


	ofPoint			_oldPos;
	ofPoint         _vel;
	float			_mass, _invMass;
	float			_drag;
	float			_bounce;
	float			_radius;
	float			_age;
	bool			_isDead;
	bool			_isFixed;
	bool			_globalCollisionEnabled;
	unsigned int	_xBinFlags, _yBinFlags, _zBinFlags;

	void			computeBinFlags();
	void			doVerlet();
	void			checkWorldEdges();

	virtual void debugDraw();
};

