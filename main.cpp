#include <iostream>

#include "OGameSession.h"
#include "Position.h"
#include "Resources.h"
#include "ShipsParser.h"
#include "FleetVariables.h"

#define HELP_SHORT "\"l\" for Login"<<endl<<"\"h\" for Help"<<endl<<"\"e\" for Exit"
#define INFO "OGame Expeditions Bot by R.K"

using namespace std;

int main()
{
    char option;
    int number_of_expeditions;
    bool logged_in = false;
    string server, pass, name;
    OGameSession *OGSession;
    Position *Sp, *Tp;
    Resources *res;
    int ships[13] = {0};

    cout<<INFO<<endl<<endl;

    while(1)
    {
        cout<<HELP_SHORT<<endl;
        cin>>option;

        if(option == 'l')
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

            cout<<endl<<"\"x\" for eXpedition"<<endl<<"\"o\" for lOg out"<<endl<<"\"e\" for Exit"<<endl;
            cin>>option;

            if(option == 'o')
            {
                continue;
            }
            else if(option == 'e')
            {
                return 0;
            }
            else if(option == 'x')
            {
                cout<<"Number of parallel expeditions: ";
                cin>>number_of_expeditions;

                cout<<endl<<"\"s\" for Same expeditions"<<endl<<"\"d\" for Different expeditions"<<endl<<"\"e\" for Exit"<<endl;
                cin>>option;

                if(option == 's')
                {
                    int t1,t2,t3,s,ht;

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

                    /**space for exp loop**/
                    //for(int as = 0; as <= number_of_expeditions;as++)
                    //{
                        OGSession->sendFleet(*Sp, *Tp, 15, ships, s, ht, *res);
                    //}

                }
                else if(option == 'd')
                {

                }
                else if(option == 'x')
                {
                    return 0;
                }
            }

        }
        else if(option == 'e')
        {
            return 0;
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

        //for fresh login after logout
        if(logged_in == true)
        {
            delete Sp;
            delete Tp;
            delete res;
            delete OGSession;
            logged_in = false;
        }
    }
    return 0;
}
