#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "Poco/StreamCopier.h"

#include "Position.h"

using namespace std;
using  Poco::StreamCopier;

//#define GTf3_DEBUG;

string GetToken_f3(string f3_page)
{
    string token;
    string to_find("token' value='");

    size_t found = f3_page.find(to_find);;

    if (found != string::npos)
    {
        #ifdef GTf3_DEBUG
        cout << "token FOUND " << found << '\n';
        #endif // GTf3_DEBUG
    }
    else
    {
        #ifdef GTf3_DEBUG
        cout << "TOKEN NOT FOUND!" << endl;
        #endif // GTf3_DEBUG
    }

    token = f3_page.substr(found, 50);
    found = token.find("='");
    token = token.substr(found+2, 50);
    found = token.find("'");
    token = token.substr(0,found);

    #ifdef GTf3_DEBUG
    cout<<endl<<"TOKEN :"<<token<<endl;
    cout<<endl<<"START OF TOKEN|"<<token<<"|END OF TOKEN"<<endl;
    #endif // GTf3_DEBUG

    return token;
}


string GetPlaneCP(string login_page, Position &starting_planet)
{
    string to_find = ("[" + to_string(starting_planet.getGalaxy()) + ":" + to_string(starting_planet.getSolarSystem()) +
                        ":" + to_string(starting_planet.getPlanet()) + "]&lt;/B&gt;&lt;BR&gt");
    string cp;

    size_t found = login_page.find(to_find);;

    if (found != string::npos)
    {
        #ifdef GTf3_DEBUG
        cout << "Suradnice FOUND " << found << '\n';
        #endif // GTf3_DEBUG
    }
    else
    {
        #ifdef GTf3_DEBUG
        cout << "Suradnice NOT FOUND!" << endl;
        #endif // GTf3_DEBUG
    }

    cp = login_page.substr(found - 150, 150);
    found = cp.find("cp=");
    cp = cp.substr(found+3, 40);
    found = cp.find("\"");
    cp = cp.substr(0, found);

    #ifdef GTf3_DEBUG
    cout<<endl<<"CP :"<<cp<<endl;
    cout<<endl<<"START OF CP|"<<cp<<"|END OF CP"<<endl;
    #endif // GTf3_DEBUG

    return cp;
}
