#include "Resources.h"

Resources::Resources(int metal, int crystal, int deuterium) : M(metal), C(crystal), D(deuterium)
{
}

Resources::~Resources()
{
}

inline int Resources::getMetal(){return M;}
inline int Resources::getCrystal(){return C;}
inline int Resources::getDeuterium(){return D;}

inline bool Resources::setMetal(int new_metal_amount){M = new_metal_amount; return true;}
inline bool Resources::setCrystal(int new_crystal_amount){C = new_crystal_amount; return true;}
inline bool Resources::setDeuterium(int new_deuterium_amount){D = new_deuterium_amount; return true;}
