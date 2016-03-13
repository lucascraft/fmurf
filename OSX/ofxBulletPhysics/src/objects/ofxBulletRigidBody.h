/*
 *  ofxBulletObject.h
 *  ofxBulletPhysics demo
 *
 *  Created by Mehmet Akten on 21/06/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

/* TODO
 add ownership for collision shape, so it can delete or not
 */

#include "ofTypes.h"
#include "btBulletDynamicsCommon.h"

class ofxBulletRigidBody {
public:
	ofxBulletRigidBody();
	virtual	~ofxBulletRigidBody();

	// initialize the rigidbody with the given collisionShape and startPosition
	// ownsCollisionShape is for advanced (and internal use) only
	void					setup(ofPoint &startPosition, btCollisionShape *collisionShape, bool ownsCollisionShape, float mass = 1);
	btCollisionShape		*getCollisionShape();	
	btRigidBody				*getBulletBody();
	
//	void					setMass(float m = 1);
//	float					getMass();	
	
	bool					isFixed();
	bool					isFree();
	void					makeFixed();
	void					makeFree();	
	
protected:
//	float					mass;
	bool					ownsCollisionShape;		// whether the object owns (and can delete) the collision shape
	btRigidBody				*bulletBody;
	btCollisionShape		*collisionShape;
};


inline btCollisionShape		*ofxBulletRigidBody::getCollisionShape() {
	return collisionShape;
}

inline btRigidBody			*ofxBulletRigidBody::getBulletBody() {
	return bulletBody;
}
//
//inline void					ofxBulletRigidBody::setMass(float m) {
//	mass = m;
//}
//
//inline float				ofxBulletRigidBody::getMass() {
//	return mass;
//}
//

inline bool					ofxBulletRigidBody::isFixed() {
//	return (mass == 0);
}

inline bool					ofxBulletRigidBody::isFree() {
}

inline void					ofxBulletRigidBody::makeFixed() {
}

inline void					ofxBulletRigidBody::makeFree() {
}