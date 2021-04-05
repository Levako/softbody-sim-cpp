#include "../include/Softbody.h"

Softbody::Softbody() {}

Softbody::Softbody(sf::Vector2f shapePosition) 
{
    sf::Vector2f pointPosition;

    // Iterate on radians of the circle
    for (float angle = 0, index = 0; angle<=2*PI; angle+=(2*PI)/VERTEX_COUNT, index++) 
    {
        pointPosition = sf::Vector2f(shapePosition.x + RADIUS*cos(angle),
                                     shapePosition.y + RADIUS*sin(angle));
        _vertices.push_back(SoftbodyVertex(pointPosition));
    }

    for (int index = 0; index < VERTEX_COUNT - 1; index++) 
    {
        addSpring(index, index, index + 1);
    }

    addSpring(VERTEX_COUNT - 1, VERTEX_COUNT - 1, 0);

    _pressure = 0;
    _mass = SHAPE_MASS;
}

Softbody::~Softbody() {}

void Softbody::addSpring(int index, int j, int k)
{
    float length = sqrt(pow(_vertices[j].getPosition().x - _vertices[k].getPosition().x , 2) +
                         pow(_vertices[j].getPosition().y - _vertices[k].getPosition().y , 2));
        
    _springs.push_back(SoftbodySpring(j, k, length));
}

void Softbody::addVertexForce(int index, sf::Vector2f force) 
{
    this->_vertices[index].addForce(force);
}

void Softbody::addGlobalForce(sf::Vector2f force)
{
    for (auto vertix : this->_vertices)
    {
        vertix.addForce(force);
    }
}

void Softbody::accumalateForces(sf::Vector2i mousePos) 
{
    float x1, y1, x2, y2;
    float vx12, vy12;
    float r12d;
    float force;
    float forceVecX, forceVecY;
    float volume;
    float pressureVec;

    // Forces //

    // Gravity
    /* 
        Very important to note, that in addition to setting the GRAVITY
        we RESET the forces
    */ 
    for (int vertexIndex = 0; vertexIndex < VERTEX_COUNT; vertexIndex++)
    {
        forceVecX = 0;
        forceVecY = (_pressure - MAX_PRESSURE) >= 0 ? FORCE_COEFFICIENT*_mass : 0;

        _vertices[vertexIndex].setForce(sf::Vector2f(forceVecX, forceVecY));
    }

    // Mouse force - Left-Mouse press "drag" effect
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        x1 = _vertices[0].getPosition().x;
		y1 = _vertices[0].getPosition().y;
		x2 = mousePos.x;
		y2 = mousePos.y;
        
        // Distance
        r12d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

        force = (r12d - 2.2) * 25 + (_vertices[0].getVelocity().x * (x1 - x2) + _vertices[0].getVelocity().y * (y1 - y2)) * 60 / r12d;
        forceVecX = ((x1 - x2) / r12d)  * force;
        forceVecY = ((y1 - y2) / r12d)  * force;

        _vertices[0].addForce(sf::Vector2f(-forceVecX, -forceVecY));
    }

    // Spring linear force calculation, by Hooke's Law.
    for (int vertexIndex = 0; vertexIndex < VERTEX_COUNT; vertexIndex++)
    {
        // Positions of start and end indices per spring
        x1 = _vertices[_springs[vertexIndex].getIndexStart()].getPosition().x;
        y1 = _vertices[_springs[vertexIndex].getIndexStart()].getPosition().y;
        x2 = _vertices[_springs[vertexIndex].getIndexEnd()].getPosition().x;
        y2 = _vertices[_springs[vertexIndex].getIndexEnd()].getPosition().y;

        // Square distance
        r12d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

        if (r12d != 0)
        {
            // Velocites of start and end points
            vx12 = _vertices[_springs[vertexIndex].getIndexStart()].getVelocity().x -
                   _vertices[_springs[vertexIndex].getIndexEnd()].getVelocity().x;
            vy12 = _vertices[_springs[vertexIndex].getIndexStart()].getVelocity().y -
                   _vertices[_springs[vertexIndex].getIndexEnd()].getVelocity().y;

            // Force value
            force = (r12d -  _springs[vertexIndex].getLength()) * KS +
                    (vx12 * (x1 - x2) +
                    vy12 * (y1 - y2)) * KD / r12d;

            // Force vector on each axis
            forceVecX = ((x1 - x2) / r12d ) * force;
            forceVecY = ((y1 - y2) / r12d ) * force;

            // Force for starting vertex
            _vertices[_springs[vertexIndex].getIndexStart()].addForce(sf::Vector2f(-forceVecX, -forceVecY));

            // Force for ending vertex
            _vertices[_springs[vertexIndex].getIndexEnd()].addForce(sf::Vector2f(forceVecX, forceVecY));
        }

        // Set spring vector
        _springs[vertexIndex].setVector(sf::Vector2f((-(y1 - y2) / r12d), ((x1 - x2) / r12d)));
    }

    volume = 0;

    // Calculate convex' volume
    for (int index = 0; index < VERTEX_COUNT; index++) 
    {
        x1 = _vertices[_springs[index].getIndexStart()].getPosition().x;
        y1 = _vertices[_springs[index].getIndexStart()].getPosition().y;
        x2 = _vertices[_springs[index].getIndexEnd()].getPosition().x;
        y2 = _vertices[_springs[index].getIndexEnd()].getPosition().y;

		r12d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        
		volume = volume + (0.5 * fabs(x1 - x2) * fabs(_springs[index].getVector().x) * (r12d));
	}

    // Calculation of pressure force, Derived governing equation
    for (int vertexIndex = 0; vertexIndex < VERTEX_COUNT; vertexIndex++)
    {
        // Positions of start and end indices per spring
        x1 = _vertices[_springs[vertexIndex].getIndexStart()].getPosition().x;
        y1 = _vertices[_springs[vertexIndex].getIndexStart()].getPosition().y;
        x2 = _vertices[_springs[vertexIndex].getIndexEnd()].getPosition().x;
        y2 = _vertices[_springs[vertexIndex].getIndexEnd()].getPosition().y;

        // Square distance
        r12d = sqrt(pow(x1 - x2, 2)+ pow(y1 - y2, 2));

        // Pressure vector
        pressureVec = r12d * _pressure * (1.0f/volume);

        _vertices[_springs[vertexIndex].getIndexStart()]
                 .addForce(sf::Vector2f(_springs[vertexIndex].getVector().x * pressureVec,
                                        _springs[vertexIndex].getVector().y * pressureVec));
        _vertices[_springs[vertexIndex].getIndexEnd()]
                 .addForce(sf::Vector2f(_springs[vertexIndex].getVector().x * pressureVec,
                                        _springs[vertexIndex].getVector().y * pressureVec));
    }
}

void Softbody::accumalateMotion(float deltaTime)
{
    float dry, drx;

    for (int index = 0; index < VERTEX_COUNT; index++)
    {
        //  X velocity
        _vertices[index].setVelocityX(_vertices[index].getVelocity().x +
                                     (_vertices[index].getForce().x / _mass) * deltaTime);
        
        // X  BOUNDIRES //
        drx = _vertices[index].getVelocity().x * deltaTime;
        if (_vertices[index].getPosition().x + drx < -SIZE)
        {
            drx = -SIZE - _vertices[index].getPosition().x;
            _vertices[index].setVelocityX(-0.1 * _vertices[index].getVelocity().x);
        }

        // X position
        _vertices[index].setPositionX(_vertices[index].getPosition().x + drx);

        //  Y velocity
        _vertices[index].setVelocityY(_vertices[index].getVelocity().y +
                                      _vertices[index].getForce().y * deltaTime);

        // Y  BOUNDIRES //
        dry = _vertices[index].getVelocity().y * deltaTime;
        if (_vertices[index].getPosition().y + dry < -SIZE)
        {
            dry = -SIZE - _vertices[index].getPosition().y;
            _vertices[index].setVelocityY(-0.1 * _vertices[index].getVelocity().y);
        }

        // Y position
        _vertices[index].setPositionY(_vertices[index].getPosition().y + dry);
    }
}

void Softbody::updateVertices(float deltaTime, sf::Vector2i mousePos) 
{
    accumalateForces(mousePos);
    accumalateMotion(deltaTime);

    if (_pressure < MAX_PRESSURE)
    {
		_pressure += MAX_PRESSURE / 300;
	}
}

sf::Vector2f Softbody::getVertexPosition(int index)
{
    return this->_vertices[index].getPosition();
}

std::vector<SoftbodyVertex> Softbody::getVertices() 
{
    return this->_vertices;
}