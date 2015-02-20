#include "Position.h"
#include <iostream>
#include <string>

Position::Position(int galaxy, int solar_system, int planet) : G(galaxy), SS(solar_system), P(planet)
{

}

Position::~Position()
{
    //dtor
}

inline int Position::getGalaxy(){return G;}
inline int Position::getSolarSystem(){return SS;}
inline int Position::getPlanet(){return P;}

inline bool Position::setGalaxy(int new_galaxy){G = new_galaxy; return true;}
inline bool Position::setSolarSystem(int new_solar_system){SS = new_solar_system; return true;}
inline bool Position::setPlanet(int new_planet_position){P = new_planet_position; return true;}
