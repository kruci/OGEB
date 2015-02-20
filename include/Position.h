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

        inline int getGalaxy();
        inline int getSolarSystem();
        inline int getPlanet();

        inline bool setGalaxy(int new_galaxy);
        inline bool setSolarSystem(int new_solar_system);
        inline bool setPlanet(int new_planet_position);
};

#endif // POSITION_H
