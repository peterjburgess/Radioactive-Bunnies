//
//  bunnyworld.h
//  Rabbits
//
//  Created by Peter Burgess on 2015-05-28.
//  Copyright (c) 2015 Peter Burgess. All rights reserved.
//

#ifndef Rabbits_bunnyworld_h
#define Rabbits_bunnyworld_h

#include "bunny.h"

class BunnyWorld
{
public:
    BunnyWorld();
    ~BunnyWorld();
    
    //Getters
    int getPopulation() const;
    
    void takeTurn();
    void printBunnies();
    
    Bunny* const m_first;
    
private:
    //private member variables
    int m_population;
    int m_radioactivePopulation;
    
    //perform mass actions on bunnies
    void increaseAge() const;
    void killOldBunnies();
    void infectBunnies();
    void cullBunnies();
    void giveBirth();
    
    //perform action on individual bunny
    void printBunny(Bunny *bunny) const;
    void killBunny(Bunny *deadBunny);

    //boolean checks
    bool isEligibleMale() const;
    bool shouldInfect() const;
    
    int getRandomColor();


    
};

#endif
