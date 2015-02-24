#ifndef POSITION_H
#define POSITION_H

#include <iostream>

class Position
{
    private:
        int G, SS, P;
    public:
        Position(int galaxy, int solar_system, int planet);
        virtual ~Position();

        int getGalaxy();
        int getSolarSystem();
        int getPlanet();

        bool setGalaxy(int new_galaxy);
        bool setSolarSystem(int new_solar_system);
        bool setPlanet(int new_planet_position);
};

#endif // POSITION_H
