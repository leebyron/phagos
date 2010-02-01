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


#define INITIAL_GAME_STATE 0x4 // 0x1


// determines how rapid animations of the controller are
#define CONTROLLER_ANIMATOR 0.15

// resolution of points along polygon to approximate a ring
#define RING_RESOLUTION 48
#define RING_RADIUS 85.5

// determines how quickly a creature can turn based on it's speed
#define CREATURE_TURNING_SCALAR 0.003
#define CREATURE_TURNING_MIN 0.002

// determines how much velocity can be added based on it's speed
#define CREATURE_VELOCITY_SCALAR 0.0024
#define CREATURE_VELOCITY_MIN 0.008

// determines how big a creature can get
#define CREATURE_SIZE_SCALAR 2.5
#define CREATURE_SIZE_MIN 2

// determines the mass of a creature which effects how things move
#define CREATURE_WEIGHT_SCALAR 0.1
#define CREATURE_WEIGHT_MIN 1

// used in collisions to determine how much force to push back
#define CREATURE_SQUISHINESS 0.08

#define OOZE_USE_RATE 0.003
#define OOZE_RECOVERY_RATE 0.001

#define EDGE_FIELD_STRENGTH 0.0004


#ifndef WRAP_ANGLE
  #define WRAP_ANGLE(val) while(val<-PI){val+=TWO_PI;}while(val>PI){val-=TWO_PI;}
#endif

float sqAni(float x);

