/*
 *  PlayerManager.h
 *  Phagos
 *
 *  Created by Lee Byron on 1/30/10.
 *  Copyright 2010 Experimental Design Lab. All rights reserved.
 *
 */

#import "Player.h"

class PlayerManager {
public:
  
  static PlayerManager* getManager();
  PlayerManager();
  ~PlayerManager();
  
  int       numPlayers;
  Player*   players[8];
  Player*   playersByJoy[8];

  void      clearPlayers();
  Player*   addPlayer(int joyNum);
  Player*   getPlayer(int playerNum);
  bool      hasPlayerForJoystick(int joyNum);
  Player*   getPlayerForJoystick(int joyNum);

};
