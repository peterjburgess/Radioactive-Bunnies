//
//  main.cpp
//  Rabbits
//
//  Created by Peter Burgess on 2015-05-05.
//  Copyright (c) 2015 Peter Burgess. All rights reserved.
//

#include <cstdlib>
#include <time.h>
#include "bunnyworld.h"

using namespace std;



int main(){
    srand(time(NULL));
    BunnyWorld world;
    int numTurns = 0;
    while (world.getPopulation() > 0)
    {
        world.takeTurn();
        numTurns ++;
    }
    
    return 0;
}
