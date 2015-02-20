#ifndef INCLUDES_H
#define INCLUDES_H
//--------------------------------------------------------------------------
#include "OGameSession.h"
#include "Position.h"
#include "Resources.h"
#include "ShipsParser.h"

#define HELP_SHORT "\"l\" for Login"<<endl<<"\"h\" for Help"<<endl<<"\"e\" for Exit"
#define INFO "OGame Expeditions Bot by R.K"

/**ships ogame numbers**/ /**
#define VT am203 // velky transporter
#define LS am204 // lachky stihac
#define TS am205 // tasky stihac
#define KR am206 // kriznik (cruiser)
#define MT am202 // male transporty
#define SpS am210 // Spion sondy
#define BS am207 //bojova lod (battleship)
#define BC am215 //bojovy kriznik (battlecruiser)
#define BB am211 //bombarder
#define DS am213 //Devastator
#define RC am209 //Recycler
#define CS am208 //colony ship
#define DS am214 //deadstar **/

namespace ships{
    std::string big_transporter("am203");
    std::string small_transporter("am202");
    std::string small_fighter("am204");
    std::string large_fighter("am205");
    std::string cruiser("am206");
    std::string spy_sond("am210");
    std::string battleship("am207");
    std::string battlecruiser("am215");
    std::string bomber("am211");
    std::string devastator("am213");
    std::string recycler("am209");
    std::string colony_ship("am208");
    std::string dead_star("am214");

    std::string ships_names[12] = {"Light fighter","Heavy fighter","Cruiser","Battleship",
                                   "Small cargo","Large cargo","Colony ship","Battlecuiser"
                                   "Bomber","Devastator","Dead Star","Recycler","Spy Sond"};
}

//---------------------------------------------------------------------------
#endif // INCLUDES_H
