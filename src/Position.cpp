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

int Position::getGalaxy(){return G;}
int Position::getSolarSystem(){return SS;}
int Position::getPlanet(){return P;}

bool Position::setGalaxy(int new_galaxy){G = new_galaxy; return true;}
bool Position::setSolarSystem(int new_solar_system){SS = new_solar_system; return true;}
bool Position::setPlanet(int new_planet_position){P = new_planet_position; return true;}
