//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_GAME_H
#define FIVECROWNS_GAME_H


#include "Player.h"
#include <map>
class Game {
public:
    void start();
private:
    int numRounds = 13;
    // vector<Player*> players;
    map<string, Player*> players;
    void onStart();
    void createPlayers();
};


#endif //FIVECROWNS_GAME_H
