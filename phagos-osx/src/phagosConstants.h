/*
 *  phagosConstants.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#pragma once



// how many players can tap in before we close the doors to others
#define MAX_PLAYERS 4

// how many seconds should we wait after someone taps in for another
// player to tap in as well
#define WAITING_COUNTDOWN_TIME_1   5.0
#define WAITING_COUNTDOWN_TIME     3.0
#define WAITING_COUNTDOWN_TIME_MAX 1.5

// initial game state, use for debugging to skip to steps
#define INITIAL_GAME_STATE 0x2 // 0x1



// determines how rapid animations of the controller are
#define CONTROLLER_ANIMATOR 0.15

// the strength of the edges of the screen to keep things in bounds
#define EDGE_FIELD_STRENGTH 0.0004



// resolution of points along polygon to approximate a ring
#define RING_RESOLUTION 40
#define RING_RADIUS 85.5

// out of a total of 1 (=100%) per frame usage and recovery of ooze
#define OOZE_USE_RATE 0.0015
#define OOZE_RECOVERY_RATE 0.00085

// the mag power of your creator
#define CREATOR_MAGNIFICATION 0.4

// how many points are added to a creature per frame * OOZE_USE_RATE while button is pressed
// OOZE_USE_RATE(0.003) * POINTS_TO_OOZE(500) * FPS(60) = POINTS_PER_SECOND(54)
// size, hunger and speed and measured in Points
#define POINTS_TO_OOZE 500



// the cost % of ooze to create a new creature
#define NEW_CREATURE_COST 0.03

// used in collisions to determine how much force to push back
#define CREATURE_SQUISHINESS 0.08

// used to convert points to dimensions
#define CREATURE_TAIL_LENGTH 0.1
#define CREATURE_MOUTH_SIZE 0.1



// determines how quickly a creature can turn based on it's speed
#define CREATURE_TURNING_SCALAR 0.0015
#define CREATURE_TURNING_MIN 0.001

// determines how much velocity can be added based on it's speed
#define CREATURE_VELOCITY_SCALAR 0.002
#define CREATURE_VELOCITY_MIN 0.008

// determines how big a creature can get
#define CREATURE_SIZE_SCALAR 2.5
#define CREATURE_SIZE_MIN 0

// determines the mass of a creature which effects how things move
#define CREATURE_WEIGHT_SCALAR 0.1
#define CREATURE_WEIGHT_MIN 1

// determines how many size points are eaten per frame
// eatingSizePointsPerFrame = hunger * CREATURE_EATING_SPEED + CREATURE_EATING_MIN
// if you want to destroy a 100 size cell with a 100 hunger in 5 seconds:
// 100size = 60fps * 5sec * 100hunger * 0.003eatingspeed
#define CREATURE_EATING_SPEED 0.003
#define CREATURE_EATING_MIN 0.007

// determines the maximum angle we can still eat something at
#define CREATURE_EATING_ANGLE 0.003
#define CREATURE_EATING_ANGLE_MIN 0.04

// determines how many of the points eaten are regained
#define POINTS_EATEN_EFFICIENCY 0.6

// the distance you can be from your target and still eat
#define NOM_DISTANCE 6

// the amount of size to eat every frame just due to being alive
#define PER_FRAME_METABOLISM 0.005



//------------------------------------------------------------------------
// have some utils functions here too, why not!

#ifndef WRAP_ANGLE
  #define WRAP_ANGLE(val) while(val<-PI){val+=TWO_PI;}while(val>PI){val-=TWO_PI;}
#endif

#ifndef SQ
  #define SQ(val) (val*val)
#endif

float sqAni(float x);
