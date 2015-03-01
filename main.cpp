#include <iostream>
#include <algorithm>
#include <ctime>

#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/AutoPtr.h"

#include "OGameSession.h"
#include "Position.h"
#include "Resources.h"
#include "ShipsParser.h"
#include "FleetVariables.h"
#include "Functions.h"

#define HELP_SHORT "\"l\" for Login"<<endl<<"\"h\" for Help"<<endl<<"\"e\" for Exit"
#define INFO "OGame Expeditions Bot by R.K"

using namespace std;
using Poco::AutoPtr;
using Poco::Util::IniFileConfiguration;

int main()
{
    char option;
    int number_of_expeditions;
    bool logged_in = false;
    string server, pass, name, filename;
    OGameSession *OGSession;
    Position *Sp = NULL, *Tp = NULL;
    Resources *res = NULL;
    int ships[13] = {0};
    time_t send, act_time;

    time_t rawtime;
    struct tm * timeinfo;
    string strtime;

    AutoPtr<IniFileConfiguration> xConf;
    int t1,t2,t3,s,ht;

    cout<<INFO<<endl<<endl;

    while(1)
    {
        cout<<HELP_SHORT<<endl;
        cin>>option;

        if(option == 'l' || logged_in == true)
        {
            if(logged_in == false)
            {
                cout<<"server  : ";
                cin>>server;
                cout<<"name    : ";
                cin>>name;
                cout<<"password: ";
                cin>>pass;

                OGSession = new OGameSession(server, name, pass);

                OGSession->login();
                logged_in = true;
            }

            cout<<endl<<"\"x\" for eXpedition"<<endl<<"\"o\" for lOg out"<<endl<<"\"e\" for Exit"<<endl;
            cin>>option;

            if(option == 'o')
            {
                if(logged_in == true)
                {
                    if(Sp != NULL)
                        delete Sp;
                    if(Tp != NULL)
                        delete Tp;
                    if(res != NULL)
                        delete res;

                    delete OGSession;
                    logged_in = false;
                }
                continue;
            }
            else if(option == 'e')
            {
                break;
            }
            else if(option == 'x')
            {
                cout<<"Number of parallel expeditions: ";
                cin>>number_of_expeditions;

                cout<<endl<<"\"f\" load conf File"<<endl<<"\"s\" for Same expeditions"<<endl<<"\"d\" for Different expeditions"<<endl<<"\"b\" for BACK"<<endl;
                cin>>option;

                if(option == 'f')
                {
                    cout<<"File name: ";
                    cin>>filename;

                    xConf = new IniFileConfiguration(filename);
                    t1 = xConf->getInt("StartingPosition.G");
                    t2 = xConf->getInt("StartingPosition.S");
                    t3 = xConf->getInt("StartingPosition.P");
                    //cout<<"s.G="<<t1<<"s.S="<<t2<<"s.P="<<t3<<endl;
                    Sp = new Position(t1,t2,t3);
                    t1 = xConf->getInt("TargetPosition.G");
                    t2 = xConf->getInt("TargetPosition.S");
                    t3 = xConf->getInt("TargetPosition.P");
                    //cout<<"t.G="<<t1<<"t.S="<<t2<<"t.P="<<t3<<endl;
                    Tp = new Position(t1,t2,t3);
                    s = xConf->getInt("Other.Speed");
                    ht = xConf->getInt("Other.HoldTime");
                    t1 = xConf->getInt("Resources.M");
                    t2 = xConf->getInt("Resources.C");
                    t3 = xConf->getInt("Resources.D");
                    //cout<<"r.M="<<t1<<"r.C="<<t2<<"r.D="<<t3<<endl;
                    //cout<<"s="<<s<<"ht="<<ht<<endl;
                    res = new Resources(t1,t2,t3);

                    for(int a = 0; a <= 12;a++)
                    {
                        ships[a] = xConf->getInt("Ships." + to_string(a));
                    }

                    /**Start**/
                    time (&rawtime);
                    timeinfo = localtime (&rawtime);
                    strtime = asctime(timeinfo);
                    strtime.erase(remove(strtime.begin(), strtime.end(), '\n'), strtime.end());
                    cout<<endl<<"|"<<strtime<<" -----------------------------------|"<<endl;
                    for(int as = 0; as < number_of_expeditions;)
                    {
                        if(OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, s, ht, *res) == true)
                        {
                            as++;
                        }
                    }
                    send = clock();
                    cout<<"|Fleets have been sent -----------------------------|"<<endl;

                    /**Sending loop**/
                    while(1)
                    {
                        act_time = clock();
                        if(act_time/CLOCKS_PER_SEC > send/CLOCKS_PER_SEC + 300)
                        {
                            time (&rawtime);
                            timeinfo = localtime (&rawtime);
                            strtime = asctime(timeinfo);
                            strtime.erase(remove(strtime.begin(), strtime.end(), '\n'), strtime.end());
                            cout<<endl<<"|"<<strtime<<" -----------------------------------|"<<endl;
                            OGSession->login();
                            for(int as = 0; as < number_of_expeditions;)
                            {
                                if(OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, s, ht, *res) == true)
                                {
                                    as++;
                                }
                            }
                            send = clock();
                            cout<<"|Fleets have been sent -----------------------------|"<<endl;
                        }
                    }
                }
                else if(option == 's')
                {
                    cout<<"Starting Galaxy      : ";
                    cin>>t1;
                    cout<<"Starting Solar system: ";
                    cin>>t2;
                    cout<<"Starting Planet      : ";
                    cin>>t3;
                    Sp = new Position(t1,t2,t3);

                    cout<<"Target Galaxy        : ";
                    cin>>t1;
                    cout<<"Target Solar system  : ";
                    cin>>t2;
                    cout<<"Target Planet        : ";
                    cin>>t3;
                    Tp = new Position(t1,t2,t3);

                    cout<<"Speed (10 = max) : ";
                    cin>>s;
                    cout<<"Hold Time(1 = 1h): ";
                    cin>>ht;

                    cout<<"Load with resources?(y/n) : ";
                    cin>>option;
                    if(option == 'y')
                    {
                        cout<<"Metal    : ";
                        cin>>t1;
                        cout<<"Crystal  : ";
                        cin>>t2;
                        cout<<"Deuterium: ";
                        cin>>t3;
                        res = new Resources(t1,t2,t3);
                    }
                    else
                    {
                        res = new Resources(0,0,0);
                    }

                    for(int g = 0;g <= 12;g++)
                    {
                        cout<<ships::ships_names[g]<<" :";
                        cin>>ships[g];
                    }

                    /*OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, s, ht, *res);
                    return 0;*/

                    /**space for exp loop**/
                    time (&rawtime);
                    timeinfo = localtime (&rawtime);
                    strtime = asctime(timeinfo);
                    strtime.erase(remove(strtime.begin(), strtime.end(), '\n'), strtime.end());
                    cout<<endl<<"|"<<strtime<<" -----------------------------------|"<<endl;
                    for(int as = 0; as < number_of_expeditions;)
                    {
                        if(OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, s, ht, *res) == true)
                        {
                            as++;
                        }
                    }
                    send = clock();
                    cout<<"|Fleets have been sent -----------------------------|"<<endl;

                    while(1)
                    {
                        act_time = clock();
                        if(act_time/CLOCKS_PER_SEC > send/CLOCKS_PER_SEC + 300)
                        {
                            time (&rawtime);
                            timeinfo = localtime (&rawtime);
                            strtime = asctime(timeinfo);
                            strtime.erase(remove(strtime.begin(), strtime.end(), '\n'), strtime.end());
                            cout<<endl<<"|"<<strtime<<" -----------------------------------|"<<endl;
                            OGSession->login();
                            for(int as = 0; as < number_of_expeditions;)
                            {
                                if(OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, s, ht, *res) == true)
                                {
                                    as++;
                                }
                            }
                            send = clock();
                            cout<<"|Fleets have been sent -----------------------------|"<<endl;
                        }
                    }

                }
                else if(option == 'd')
                {

                }
                else if(option == 'b')
                {
                    continue;
                }
            }

        }
        else if(option == 'e')
        {
            break;
        }
        else if(option == 'h')
        {
            cout<<"No help for you!"<<endl;
        }
        else
        {
            cout<<"Invalid input"<<endl;
        }
        cout<<endl;
    }
    if(Sp != NULL)
        delete Sp;
    if(Tp != NULL)
        delete Tp;
    if(res != NULL)
        delete res;
    if(logged_in == true)
        delete OGSession;

    return 0;
}
