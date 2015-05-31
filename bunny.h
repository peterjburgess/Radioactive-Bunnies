//
//  bunny.h
//  Rabbits
//
//  Created by Peter Burgess on 2015-05-24.
//  Copyright (c) 2015 Peter Burgess. All rights reserved.
//

#ifndef Rabbits_bunny_h
#define Rabbits_bunny_h

#include <string>


namespace bny{
    enum sex{male, female};
    enum color{white, brown, black, spotted};
}

class Bunny
{
public:
    //Constructors and destructor
    Bunny();
    Bunny(int color);
    ~Bunny();
    //Setters
    int setSex();
    std::string setName();
    bool setRadioactive();
    void setRadioactive(bool radioactiveStatus);
    //Getters
    int getColor() const;
    int getSex() const;
    std::string getName() const;
    bool getRadioactive() const;
    int getAge() const;
    
    std::string toString();
    void increaseAge();
    
    Bunny* m_next;
    
private:
    int m_sex, m_color, m_age;
    bool m_radioactive;
    std::string m_name;
   // enum sex{male, female};
    //enum color{white, brown, black, spotted};
    int getNumberLines(std::string myfile);
    int numMaleNames = getNumberLines("male-names");
    int numFemaleNames = getNumberLines("female-names");
};
#endif
