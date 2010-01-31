/*
 *  CreatureWorld.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#import "Creature.h"

class CreatureWorld {
public:
  
  CreatureWorld();
  ~CreatureWorld();

  ofxMSAPhysics*  physics;
  vector<Creature*> creatures;
  
  void initWorld();
  void resetWorld();
  void updateWorld();
  Creature* spawnCreature(Player* player,
                          float size,
                          float mouthSize,
                          float speed);

};
