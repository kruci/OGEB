#ifndef SHIPS_H
#define SHIPS_H
//--------------------------------------------------------------------------

namespace ships{
    extern std::string big_transporter;
    extern std::string small_transporter;
    extern std::string small_fighter;
    extern std::string large_fighter;
    extern std::string cruiser;
    extern std::string spy_sond;
    extern std::string battleship;
    extern std::string battlecruiser;
    extern std::string bomber;
    extern std::string devastator;
    extern std::string recycler;
    extern std::string colony_ship;
    extern std::string dead_star;

    extern std::string ships_names[13];
    extern std::string ships_strings[13];
}

namespace mission{

    enum missions_names{
        expedition = 15,
        clonozation,
        recycling,
        transport = 3,
        deploy = 4,
        spy = 6,
        ali_def,
        attack = 1,
        ali_attack,
        moon_destruction
    };
}

//---------------------------------------------------------------------------
#endif // SHIPS_H
