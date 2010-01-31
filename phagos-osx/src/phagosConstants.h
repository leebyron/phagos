/*
 *  phagosConstants.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once

// how many seconds should we wait after someone taps in for another
// player to tap in as well
#define WAITING_COUNTDOWN_TIME_1   5.0
#define WAITING_COUNTDOWN_TIME     3.0
#define WAITING_COUNTDOWN_TIME_MAX 1.5

// how many players can tap in before we close the doors to others
#define MAX_PLAYERS 4


// determines how rapid animations of the controller are
#define CONTROLLER_ANIMATOR 0.15

// resolution of points along polygon to approximate a ring
#define RING_RESOLUTION 48
#define RING_RADIUS 85.5

// determines how quickly a creature can turn based on it's speed
#define CREATURE_TURNING_SCALAR 0.025

// determines how much velocity can be added based on it's speed
#define CREATURE_VELOCITY_SCALAR 0.01

#define OOZE_USE_RATE 0.003
#define OOZE_RECOVERY_RATE 0.001

float sqAni(float x);

