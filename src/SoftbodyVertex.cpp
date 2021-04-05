#include "../include/SoftbodyVertex.h"

SoftbodyVertex::SoftbodyVertex() {}

SoftbodyVertex::SoftbodyVertex(sf::Vector2f position) {
    setPosition(position);
    this->_velocity = sf::Vector2f(0, 0);
    this->_force = sf::Vector2f(0, 0);
}

SoftbodyVertex::~SoftbodyVertex() {}

sf::Vector2f SoftbodyVertex::getPosition() 
{
    return this->_position;
}

 sf::Vector2f SoftbodyVertex::getVelocity()
 {
     return this->_velocity;
 }

void SoftbodyVertex::addForce(sf::Vector2f force)
{
    this->_force += force;
}

void SoftbodyVertex::setPosition(sf::Vector2f position)
{
    this->_position = position;
}

void SoftbodyVertex::setPositionX(float x)
{
    this->_position.x = x;
}

void SoftbodyVertex::setPositionY(float y)
{
    this->_position.y = y;
}

void SoftbodyVertex::setVelocityX(float vx)
{
    this->_velocity.x = vx;
}

void SoftbodyVertex::setVelocityY(float vy)
{
    this->_velocity.y = vy;
}

sf::Vector2f SoftbodyVertex::getForce()
{
    return this->_force;
}

void SoftbodyVertex::setForce(sf::Vector2f force)
{
    this->_force = force;
}