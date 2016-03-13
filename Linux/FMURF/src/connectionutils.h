/*
 *  connectionutils.h
 *  openFrameworks
 *
 *  Created by lucas bigeardel on 28/03/10.
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef _CONNECTION_UTILS
#define _CONNECTION_UTILS

#import "smurfconnection.h"
#import "gestures.h"

class ConnectionsUtils {
public:
	SConnectionVisual getVisualFromGesture(SmurfGestureClassification _classification);
	float getConnectionAngle();
};

#endif