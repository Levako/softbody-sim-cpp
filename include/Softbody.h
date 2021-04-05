#include "Protocol.h"
#include "SoftbodyVertex.h"
#include "SoftbodySpring.h"
#include <SFML/Graphics.hpp>
#include <cmath>

#ifndef SOFTBODY_H
#define SOFTBODY_H

class Softbody 
{
public:
    // C'tors and D'tors
    Softbody();
    Softbody(sf::Vector2f position);
    ~Softbody();

    // Getters
    sf::Vector2f getVertexPosition(int index);
    std::vector<SoftbodyVertex> getVertices();

    void addVertexForce(int index, sf::Vector2f force);
    void addGlobalForce(sf::Vector2f force);
    void updateVertices(float deltaTime, sf::Vector2i mousePos);
    void accumalateForces(sf::Vector2i mousePos);
    void accumalateMotion(float deltaTime);



private:
    std::vector<SoftbodyVertex> _vertices;
    std::vector<SoftbodySpring> _springs;
    float _pressure;
    float _mass;
    
    void addSpring(int index, int start, int end);
};

#endif