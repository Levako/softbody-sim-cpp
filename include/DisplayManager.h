#include <SFML/Graphics.hpp>
#include "Protocol.h"
#include "Softbody.h"

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

class DisplayManager 
{
public:
    DisplayManager();
    ~DisplayManager();

    void runSim();
    void drawSoftbody();

private:
    sf::RenderWindow _window;
    Softbody _softbody;
};

#endif
