//
//  bunnyworld.cpp
//  Rabbits
//
//  Created by Peter Burgess on 2015-05-28.
//  Copyright (c) 2015 Peter Burgess. All rights reserved.
//

#include "bunny.h"
#include "bunnyworld.h"
#include <fstream>
#include <iostream>

//Constructor
BunnyWorld::BunnyWorld():
m_population(0),
m_radioactivePopulation(0),
m_first(new Bunny)
{
    //clears output.txt when world created.
    std::ofstream outputFile("output.txt");
    outputFile.close();
    std::ofstream populationFile("population.txt");
    populationFile.close();
    //Set up an empty first bunny to start the program
    m_first->m_next = nullptr;
    Bunny* tracker = m_first;

    //create first 5 bunnies
    for (int i = 0; i < 5; i++)
    {
        int color = getRandomColor();
        Bunny* newBunny = new Bunny(color);
        newBunny->m_next = nullptr;
        tracker->m_next = newBunny;
        tracker = newBunny;
        m_population++;
        if (newBunny->getRadioactive()){
            m_radioactivePopulation++;
        }
    }
    printBunnies();

}

//Destructor
BunnyWorld::~BunnyWorld()
{
    Bunny* tracker = m_first;
    while (tracker != nullptr){
        Bunny* old = tracker;
        tracker = tracker->m_next;
        delete old;
    }
}

/*---------------Getters---------------------------------------------------*/
int BunnyWorld::getPopulation() const
{
    return m_population;
}

/*------------------------Perform actions public---------------------------*/

//Perform all actions required on the Bunny world
void BunnyWorld::takeTurn()
{
    //if the population is greater than 1000, kill half of the population at random
    if (m_population >= 1000){
        cullBunnies();
    }
    //kill bunnies over the age of 10 and radioactive bunnies over the age of 50
    killOldBunnies();
    //increase age of every bunny
    increaseAge();
    if(m_radioactivePopulation != m_population){
        //infect x new bunnies at random, where x is the number of current radioactive bunnies
        infectBunnies();
        /*
         if there is at least one male age 2 or over and not radioactive, give birth to one bunny
         for every female age 2 or over
         */
        if(isEligibleMale()){
            giveBirth();
        }
    }
    //print all of the information about every bunny
    printBunnies();
}

//Go through each bunny in list and print the information to console and file
void BunnyWorld::printBunnies()
{
    //point to first bunny
    Bunny* tracker = m_first->m_next;
    //go through list until nullptr pointer reached and print information about each bunny
    while (tracker!=nullptr){
        printBunny(tracker);
        tracker = tracker->m_next;
    }
    std::ofstream outputfile ("population.txt" , std::ios::app);
    //print info to console
    std::cout << "Population: " << m_population << " Radioactive population: " << m_radioactivePopulation << '\n';
    //print info to file
    outputfile << "Population: " << m_population << " Radioactive population: " << m_radioactivePopulation << '\n';
    outputfile.close();
}

/*-----------------Perform mass actions on Bunnies---------------------*/

//go through each bunny and increase age by 1
void BunnyWorld::increaseAge() const
{
    Bunny* tracker = m_first->m_next;
    while (tracker != nullptr)
    {
        tracker->increaseAge();
        tracker = tracker->m_next;
    }
}

//goes through list of bunnies and kills those over 10 and not radioactive or over 50 if radioactive
void BunnyWorld::killOldBunnies()
{
    //point tracker to first 'dummy' bunny
    Bunny* tracker = m_first;
    //point next bunny to first 'real' bunny
    Bunny* nextBunny = tracker->m_next;
    /*
     The program keeps bunnies in age order so only goes through the bunnies that are aged
     10 or over to decide whether to kill it or not
    */
    while (nextBunny->getAge() >= 10)
    {
        //if bunny is 50, always dies. If not radioactive, is 10 by the while condition so kill
        if (nextBunny->getAge() == 50 || !nextBunny->getRadioactive()){
            tracker->m_next = nextBunny->m_next;
            killBunny(nextBunny);
        }
        else
            tracker = tracker->m_next;
        
        nextBunny = tracker->m_next;
        
        /*
         if we've reached the end of the list (no bunnies under 10) break out of while loop.
         It's implemented like this because the while loop requires a getAge call which doesn't
         work for the nullptr pointer.
         */
        if (nextBunny==nullptr){
            break;
        }
    }
}

/*
 Converts x new bunnies to be radioactive mutant vampire bunnies at randomwhere x is the current number of
 radioactive mutant vampire bunnies.
*/
void BunnyWorld::infectBunnies()
{
    //sets the number of bunnies to infect
    int numberToInfect = m_radioactivePopulation;
    Bunny* tracker = m_first->m_next;
    //if every bunny is radioactive, break out of the while loop
    while (numberToInfect > 0 && m_radioactivePopulation != m_population){
        //if you've reached the end of the list, go back to the start
        if(tracker == nullptr){
            tracker = m_first->m_next;
        }
        /*if the bunny isn't already radioactive, decide whether it should be infected
        at random with a probability equal to radioactivepopulation/totalpopulation
        */
        if (!tracker->getRadioactive() && shouldInfect()){
            tracker->setRadioactive(true);
            m_radioactivePopulation++;
            numberToInfect --;
        }
        tracker = tracker->m_next;
    }
    
}

//If population is over a certain number, kill half the population at random
void BunnyWorld::cullBunnies()
{
    //the new population should be half the old population
    int newPopulation = m_population/2;
    int shouldKill;
    Bunny* tracker = m_first;
    //while there are still more than half the bunnies alive
    while (m_population > newPopulation)
    {
        //decide whether bunny should be killed with probability of 50%
        shouldKill = rand()%2;
        //if end of list reached, go back to the start
        if (tracker == nullptr) {
            tracker = m_first;
        }
        if (shouldKill == 1 && tracker->m_next != nullptr){
            Bunny* deadBunny = tracker->m_next;
            tracker->m_next = deadBunny->m_next;
            killBunny(deadBunny);
        }
        tracker = tracker->m_next;
    }
}

/*
 For every female aged 2 or older and not radioactive, give birth to a new bunny of the same color
 and place it at the end of the list
 */
void BunnyWorld::giveBirth()
{
    Bunny* tracker = m_first->m_next;
    //find last bunny in list.
    Bunny* findEnd = tracker;
    while (findEnd->m_next != nullptr){
        findEnd = findEnd->m_next;
    }
    //go through whole list
    while (tracker != nullptr){
        if (tracker->getSex() == bny::female && tracker->getAge() >=2 && !tracker->getRadioactive()){
            int color = tracker->getColor();
            Bunny* newBunny = new Bunny(color);
            //put new bunny at end of list
            newBunny->m_next = nullptr;
            findEnd->m_next = newBunny;
            findEnd = newBunny;
            m_population++;
            if (newBunny->getRadioactive()){
                m_radioactivePopulation++;
            }
        }
        tracker = tracker->m_next;
    }
}


/*----------Perform actions on individual Bunny--------------------*/

//kills a bunny
void BunnyWorld::killBunny(Bunny *deadBunny)
{
    if (deadBunny->getRadioactive()){
        m_radioactivePopulation--;
    }
    delete deadBunny;
    m_population --;
}

//prints out information about bunny to a file and console
void BunnyWorld::printBunny(Bunny* bunny) const
{
    std::ofstream outputFile;
    outputFile.open("output.txt", std::ios::app);
    std::string bunnyString = bunny->toString();
    std::cout << bunnyString << '\n';
    outputFile << bunnyString << '\n';
    outputFile.close();
}


//Check to see if there is a Bunny with age >=2 and not radioactive in the population
bool BunnyWorld::isEligibleMale() const
{
    Bunny* tracker = m_first->m_next;
    while(tracker!=nullptr){
        if (tracker->getAge() >= 2 && tracker->getSex() == bny::male && !tracker->getRadioactive()){
            return true;
        }
        tracker = tracker->m_next;
    }
    return false;
}

//Make non-radioactive bunny radioactive with a probability of number of radioactive Bunnies / population
bool BunnyWorld::shouldInfect() const
{
    int randomNumber = rand() % m_population;
    if (randomNumber <= m_radioactivePopulation){
        return true;
    }
    else{
        return false;
    }
}

//Assign Bunny a random color.
int BunnyWorld::getRandomColor()
{
    return rand()%4;
}

