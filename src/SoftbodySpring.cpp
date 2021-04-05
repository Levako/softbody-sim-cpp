#include "../include/SoftbodySpring.h"

SoftbodySpring::SoftbodySpring(int startIndex, int endIndex, float length) 
{
    this->_indexStart = startIndex;
    this->_indexEnd = endIndex;
    this->_length = length;
    this->_vector = sf::Vector2f(0, 0);
}

int SoftbodySpring::getIndexStart() 
{
    return this->_indexStart;
}

int SoftbodySpring::getIndexEnd()
{
    return this->_indexEnd;
}

float SoftbodySpring::getLength()
{
    return this->_length;
}

void SoftbodySpring::setVector(sf::Vector2f vec)
{
    this->_vector = vec;
}

sf::Vector2f SoftbodySpring::getVector() 
{
    return this->_vector;
}