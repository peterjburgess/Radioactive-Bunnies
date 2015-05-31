//
//  bunny.cpp
//  Rabbits
//
//  Created by Peter Burgess on 2015-05-24.
//  Copyright (c) 2015 Peter Burgess. All rights reserved.
//


#include "bunny.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>

//default constructor only used to create empty bunny at start of list
Bunny::Bunny()
{
    
}

//constructor
Bunny::Bunny(int bunnyColor)
:m_next(nullptr),
m_sex(),
m_name(),
m_color(bunnyColor),
m_radioactive(),
m_age(0)
{
    //assign random values
    m_sex= setSex();
    m_name = setName();
    m_radioactive = setRadioactive();
    
    //print out birth information to console and file
    std::string bunnyRadio;
    if (m_radioactive){
        bunnyRadio = "Radioactive Vampire ";
    }
    std::ofstream outputFile;
    outputFile.open("output.txt", std::ios::app);
    std::cout << bunnyRadio << "Bunny " << m_name << " was born\n";
    outputFile << bunnyRadio << "Bunny " << m_name << " was born\n";
    outputFile.close();
}

//destructor
Bunny::~Bunny()
{
    //print out death information to console and file
    std::string bunnyRadio;
    if (m_radioactive){
        bunnyRadio = "Radioactive Vampire ";
    }
    std::ofstream outputFile;
    outputFile.open("output.txt", std::ios::app);
    if (m_name != ""){
        std::cout << bunnyRadio << "Bunny " << m_name << " has died \n";
        outputFile << bunnyRadio << "Bunny " << m_name << " has died \n";
    }
    outputFile.close();
}

/*----------------------------Setters-------------------------------*/
//Assigns sex male or female to bunny with 50% probability for each.
int Bunny::setSex()
{
    return rand() % 2;
}

//Checks to see whether Bunny is male or female. Opens appropriate file of names. Randomly picks a name from
//that file and assigns it to Bunny name
std::string Bunny::setName()
{
    std::ifstream myfile;
    int lineExtractNumber;
    std::string line;
    if (m_sex==bny::male){
        myfile.open("male-names");
        lineExtractNumber = rand() % numMaleNames; //num male names determined by getNumberLines
    }
    else{
        myfile.open("female-names");
        lineExtractNumber = rand() % numFemaleNames; //num female names determined by getNumberLines
    }
    for (int i = 0; i < lineExtractNumber; i++)
        std::getline(myfile, line);
    myfile.close();
    line[0] = std::toupper(line[0]);
    return line;
}

//Sets radioactive bunny status to true with probability of 2%
bool Bunny::setRadioactive()
{
    int  randomNumber = rand() % 50;
    if (randomNumber == 0){
        return true;
    }
    else{
        return false;
    }
}

void Bunny::setRadioactive(bool radioactiveStatus)
{
    m_radioactive = radioactiveStatus;
}

/*----------------------------Getters-------------------------------*/

int Bunny::getColor() const
{
    return m_color;
}


int Bunny::getSex() const
{
    return m_sex;
}

bool Bunny::getRadioactive() const
{
    return m_radioactive;
}

//returns age of Bunny
int Bunny::getAge() const
{
    return m_age;
}

std::string Bunny::getName() const
{
    return m_name;
}


/*----------------------------Other-------------------------------*/

//increases age of Bunny by one year when called
void Bunny::increaseAge()
{
    m_age++;
}


//takes file name and goes through file line by line until reaching the end of the file Increments a
//counter for each line retrived and thus returns the total number of lines in the file.
int Bunny::getNumberLines(std::string myfile)
{
    std::string line;
    int numLines = 0;
    std::ifstream file(myfile);
    while (getline(file, line)){
        numLines++;
    }
    file.close();
    return numLines - 1;
}

std::string Bunny::toString()
{
    std::string output;
    std::string bunnyColor;
    switch (m_color){
        case bny::white:
            bunnyColor = "White";
            break;
        case bny::brown:
            bunnyColor = "Brown";
            break;
        case bny::black:
            bunnyColor = "Black";
            break;
        case bny::spotted:
            bunnyColor = "Spotted";
            break;
    }
    std::string bunnySex = "Male";
    std::string bunnyRadio = "No";
    if(m_sex == bny::female){
        bunnySex = "Female";
    }
    if (m_radioactive){
        bunnyRadio = "Yes";
    }
    output = "Name: " + m_name + " - Age: " + std::to_string(m_age) + " - Color: " + bunnyColor
    + " - Sex: " + bunnySex + " - Radioactive: " + bunnyRadio;
    return output;
}









