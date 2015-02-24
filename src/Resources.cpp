#include "Resources.h"

Resources::Resources(int metal, int crystal, int deuterium) : M(metal), C(crystal), D(deuterium)
{
}

Resources::~Resources()
{
}

int Resources::getMetal(){return M;}
int Resources::getCrystal(){return C;}
int Resources::getDeuterium(){return D;}

bool Resources::setMetal(int new_metal_amount){M = new_metal_amount; return true;}
bool Resources::setCrystal(int new_crystal_amount){C = new_crystal_amount; return true;}
bool Resources::setDeuterium(int new_deuterium_amount){D = new_deuterium_amount; return true;}
