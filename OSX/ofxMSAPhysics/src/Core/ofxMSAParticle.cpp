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


#include "ofxMSAParticle.h"
#include "ofxMSAPhysics.h"
#include "binner.h"

ofxMSAParticle::ofxMSAParticle(float x, float y, float z, float m, float d) {
	init(x, y, z, m, d);
}

ofxMSAParticle::ofxMSAParticle(ofPoint &v, float m, float d) {
	init(v.x, v.y, v.z, m, d);
}

ofxMSAParticle::ofxMSAParticle(ofxMSAParticle &p) {
	init(p.x, p.y, p.z, p._mass, p._drag);
	_isFixed = p._isFixed;
	setBounce(p._bounce);
	setRadius(p._radius);
}


void ofxMSAParticle::init(float x, float y, float z, float m, float d) {
	_params = NULL;
	_physics = NULL;

	set(x, y, z);
	_oldPos.set(x, y, z);
	setMass(m);
	setDrag(d);
	setBounce();
	setRadius();
	disableCollision();
	makeFree();
	_isDead = false;
	_age = 0;
	verbose = true;
	setClassName("ofxMSAParticle");
}




ofxMSAParticle* ofxMSAParticle::setMass(float t) {
	if(t==0) t=0.00001f;
	_mass = t;
	_invMass = 1.0f/t;
	return this;
}

float ofxMSAParticle::getMass() {
	return _mass;
}

float ofxMSAParticle::getInvMass() {
	return _invMass;
}


ofxMSAParticle* ofxMSAParticle::setDrag(float t) {
	_drag = t;
	return this;
}

float ofxMSAParticle::getDrag() {
	return _drag;
}

ofxMSAParticle* ofxMSAParticle::setBounce(float t) {
	_bounce = t;
	return this;
}

float ofxMSAParticle::getBounce() {
	return _bounce;
}


ofxMSAParticle* ofxMSAParticle::setRadius(float t) {
	_radius = t;
	return this;
}

float ofxMSAParticle::getRadius() {
	return _radius;
}

ofxMSAParticle* ofxMSAParticle::enableCollision(){
	_globalCollisionEnabled = true;
	if(_physics) _physics->addToCollision(this);
	return this;
}

ofxMSAParticle* ofxMSAParticle::disableCollision() {
	_globalCollisionEnabled = false;
	if(_physics) _physics->removeFromCollision(this);
	return this;
}

bool ofxMSAParticle::hasCollision() {
	return _globalCollisionEnabled;
}




bool ofxMSAParticle::isFixed() {
	return (_isFixed == true);
}

bool ofxMSAParticle::isFree() {
	return (_isFixed == false);
}

ofxMSAParticle* ofxMSAParticle::makeFixed() {
	_isFixed = true;
	return this;
}

ofxMSAParticle* ofxMSAParticle::makeFree() {
	_oldPos.set(this->x, this->y, this->z);
	_isFixed = false;
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveTo(ofPoint &targetPos) {
	ofPoint diff = targetPos - *this;
	moveBy(diff);
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveBy(ofPoint &diffPos) {
	*this += diffPos;
	_oldPos += diffPos;
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveTo(float x, float y, float z) {
	ofPoint temp;
	temp.set(x, y, z);
	moveTo(temp);
	return this;
}

ofxMSAParticle* ofxMSAParticle::moveBy(float x, float y, float z) {
	ofPoint temp;
	temp.set(x, y, z);
	moveBy(temp);
	return this;
}

ofxMSAParticle* ofxMSAParticle::setVelocity(ofPoint &vel) {
	_oldPos = *this - vel;
//    _vel = vel;
	return this;
}

ofxMSAParticle* ofxMSAParticle::setVelocity(float x, float y, float z) {
	ofPoint temp = ofPoint(x, y, z);
	setVelocity(temp);
	return this;
}

ofxMSAParticle* ofxMSAParticle::addVelocity(ofPoint &vel) {
	_oldPos -= vel;
//    _vel += vel;
	return this;
}

ofxMSAParticle* ofxMSAParticle::addVelocity(float x, float y, float z) {
	ofPoint temp = ofPoint(x, y, z);
	addVelocity(temp);
	return this;
}

ofPoint &ofxMSAParticle::getVelocity() {
    _vel = *this - _oldPos;
	return _vel;
}

void ofxMSAParticle::kill() {
	_isDead = true;
}


bool ofxMSAParticle::isDead() {
	return _isDead;
}


void ofxMSAParticle::doVerlet() {
	if (!_isFixed) {
		if(_params->doGravity) {
			ofPoint gravityForce = _params->gravity;
			addVelocity(gravityForce);
		}

		ofPoint curPos = *this;
		getVelocity();  // updates _vel
		*this += _vel * _params->drag * _drag + _params->timeStep2;
//		*this += _vel +
		_oldPos = curPos;
	}
}

bool ofxMSAParticle::isInSameBinAs(ofxMSAParticle* p) {
	return (_xBinFlags & p->_xBinFlags) && (_yBinFlags & p->_yBinFlags) && (_zBinFlags & p->_zBinFlags);
}


void ofxMSAParticle::computeBinFlags() {
//	computeBinPosition(x, y, z, &_xBinFlags, &_yBinFlags, &_zBinFlags);
	computeBinPosition(*this, &_xBinFlags, &_yBinFlags, &_zBinFlags);
}


void ofxMSAParticle::checkWorldEdges() {
//	printf("%.3f, %.3f, %.3f\n", _params->worldMin.x, _params->worldMax.y, _params->worldMax.z);

	if(x < _params->worldMin.x + _radius) {
		moveTo(_params->worldMin.x + _radius, y, z);
        getVelocity();  // updates _vel
		setVelocity(-_vel.x * _bounce, _vel.y, _vel.z);
	} else if(x > _params->worldMax.x - _radius) {
		moveTo(_params->worldMax.x - _radius, y, z);
        getVelocity();  // updates _vel
		setVelocity(-_vel.x * _bounce, _vel.y, _vel.z);
	}

	if( y < _params->worldMin.y + _radius) {
		moveTo(x, _params->worldMin.y + _radius, z);
        getVelocity();  // updates _vel
		setVelocity(_vel.x, -_vel.y * _bounce, _vel.z);
	} else if(y > _params->worldMax.y - _radius) {
		moveTo(x, _params->worldMax.y - _radius, z);
        getVelocity();  // updates _vel
		setVelocity(_vel.x, -_vel.y * _bounce, _vel.z);
	}

	if(z < _params->worldMin.z + _radius) {
		moveTo(x, y, _params->worldMin.z + _radius);
        getVelocity();  // updates _vel
		setVelocity(_vel.x, _vel.y, -_vel.z * _bounce);
	} else if(z > _params->worldMax.z - _radius) {
		moveTo(x, y, _params->worldMax.z - _radius);
        getVelocity();  // updates _vel
		setVelocity(_vel.x, _vel.y, -_vel.z * _bounce);
	}
}


ofxMSAPhysicsParams *ofxMSAParticle::getParams() {
    return _params;
}


void ofxMSAParticle::debugDraw() {
	glPushMatrix();
	glTranslatef(x, y, z);
//#ifndef TARGET_OF_IPHONE
//	glutSolidSphere(_radius, 12, 12);
//#else
    ofCircle(0, 0, _radius);
//#endif
	glPopMatrix();
}
