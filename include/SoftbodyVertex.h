#include <SFML/Graphics.hpp>
#include "../include/Protocol.h"

#ifndef SOFTBODY_VERTEX_H
#define SOFTBODY_VERTEX_H

class SoftbodyVertex
{
public:
    // C'tors and D'tors
    SoftbodyVertex();
    SoftbodyVertex(sf::Vector2f position);
    ~SoftbodyVertex();

    // Getters
    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    sf::Vector2f getForce();

    //Setters
    void setPosition(sf::Vector2f position);
    void setPositionX(float x);
    void setPositionY(float y);
    void setVelocityX(float vx);
    void setVelocityY(float vy);    
    void setForce(sf::Vector2f force);

    void addForce(sf::Vector2f force);

private:
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    sf::Vector2f _force;
};

#endif