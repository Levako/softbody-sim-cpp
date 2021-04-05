#include "../include/DisplayManager.h"
#include <stdio.h>

DisplayManager::DisplayManager() 
{
    _window.create(sf::VideoMode(SIZE, SIZE), "SoftbodySim");
}

DisplayManager::~DisplayManager() {}

void DisplayManager::runSim() 
{
    sf::Event event;
    sf::Clock deltaClock;
    sf::Vector2f mousePos;
    float deltaTime;
    bool startSim = false;
    bool objectExists = false; // Fix later

    while (_window.isOpen()) 
    {
        deltaTime = deltaClock.restart().asSeconds();

        while(_window.pollEvent(event)) 
        {
            mousePos = sf::Vector2f(sf::Mouse::getPosition(_window));
            
            // Create Softbody
            if (event.type == sf::Event::MouseButtonReleased
                && event.mouseButton.button == sf::Mouse::Left 
                && !startSim) 
            {
                _softbody = Softbody(mousePos);
                objectExists = true;
            }

            // Space for starting simulation
            if (event.type == sf::Event::KeyReleased
                && event.key.code == sf::Keyboard::Space) 
            {
                startSim = true;
            }
        }

        // If simulation started
        if (startSim)
        {
            // Update vertices' positions
            _softbody.updateVertices(deltaTime, sf::Mouse::getPosition(_window));
        }

        // Draw walls
        _window.clear(sf::Color::White);

        if (objectExists)
        {
            drawSoftbody();
        }

        _window.display();
    }
}

void DisplayManager::drawSoftbody() 
{
    sf::ConvexShape shape;
    std::vector<SoftbodyVertex> points;

    shape.setPointCount(VERTEX_COUNT);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(SHAPE_THICKNESS);

    points = _softbody.getVertices();    

    for (int vertexIndex = 0; vertexIndex < VERTEX_COUNT; vertexIndex++)
    {
        shape.setPoint(vertexIndex, points[vertexIndex].getPosition());
    }

    this->_window.draw(shape);
}
