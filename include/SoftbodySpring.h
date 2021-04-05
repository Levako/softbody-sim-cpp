#include "Protocol.h"
#include <SFML/Graphics.hpp>

#ifndef SOFTBODY_SPRING_H
#define SOFTBODY_SPRING_H

class SoftbodySpring 
{
public:
    SoftbodySpring(int indexStart, int indexEnd, float length);
    
    int getIndexStart();
    int getIndexEnd();
    float getLength();
    sf::Vector2f getVector();

    void setVector(sf::Vector2f vec);

private:
    int _indexStart, _indexEnd;
    float _length;
    sf::Vector2f _vector;

};

#endif