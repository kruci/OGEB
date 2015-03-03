#include <iostream>
#include <algorithm>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif // WIN32 or *NIX

#include "Poco/Util/IniFileConfiguration.h"
#include "Poco/AutoPtr.h"

#include "OGameSession.h"
#include "Position.h"
#include "Resources.h"
#include "FleetVariables.h"
#include "Functions.h"

using namespace std;
using Poco::AutoPtr;
using Poco::Util::IniFileConfiguration;

int main()
{
    int ships[13] = {0};
    bool requests_set1 = true; //to detect if it is the first set of requests
    string server, pass, name, filename;
    OGameSession *OGSession = NULL;
    Position *Sp = NULL, *Tp = NULL; //Sp - Starting position, Tp - Target position
    Resources *res = NULL;
    time_t send, act_time; // time variables
    time_t rawtime;        //
    struct tm * timeinfo;  //
    string strtime;        //


    cout << "OGame Expeditions Bot by R.K" << endl << endl;
    cout << "server  : ";
    cin >> server;
    cout << "name    : ";
    cin >> name;
    cout << "password: ";

    #ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    #else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    #endif // WIN32 or *NIX

    cin >> pass;

    #ifdef WIN32
    SetConsoleMode(hStdin, mode);
    #else
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif // WIN32 or *NIX

    OGSession = new OGameSession(server, name, pass);

    cout << endl << "File name: ";
    cin >> filename;

    AutoPtr<IniFileConfiguration> conf = new IniFileConfiguration(filename);
    int speed = conf->getInt("Other.Speed");
    int hold_time = conf->getInt("Other.HoldTime");
    int number_of_expeditions = conf->getInt("Other.NumberOfExpeditions");

    Sp = new Position(conf->getInt("StartingPosition.G"), conf->getInt("StartingPosition.S"),
                      conf->getInt("StartingPosition.P"));

    Tp = new Position(conf->getInt("TargetPosition.G"), conf->getInt("TargetPosition.S"),
                      conf->getInt("TargetPosition.P"));

    res = new Resources(conf->getInt("Resources.M"), conf->getInt("Resources.C"),
                        conf->getInt("Resources.D"));

    for(int a = 0; a <= 12; a++)
    {
        ships[a] = conf->getInt("Ships." + to_string(a));
    }

    OGSession->login();

    /**Sending loop**/
    while(1)
    {
        act_time = clock();
        if( (act_time/CLOCKS_PER_SEC > send/CLOCKS_PER_SEC + 300) || requests_set1 == true)
        {
            requests_set1 = false;

            time (&rawtime);
            timeinfo = localtime (&rawtime);
            strtime = asctime(timeinfo);
            strtime.erase(remove(strtime.begin(), strtime.end(), '\n'), strtime.end());
            cout << endl <<"|" << strtime << " -----------------------------------|" << endl;

            if(OGSession->loginCheck() == false)
                OGSession->login();

            for(int as = 0, f = 0; as < number_of_expeditions;)
            {
                if(OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, speed, hold_time, *res) == true)
                {
                    as++;
                    cout << "Fleet Sent" << endl;
                }
                else
                {
                    f++;
                    if(OGSession->loginCheck() == false)
                    {
                        OGSession->login();
                    }
                }

                if(f >= 5)
                {
                    f = 0;
                    if(OGSession->loginCheck() == true)
                    {
                        cout << "Server does not accept send request!"<<endl;
                        as++;
                    }
                }
            }
            send = clock();
            cout << "|Fleets have been sent -----------------------------|" << endl;
        }
    }

    if(Sp != NULL)
        delete Sp;
    if(Tp != NULL)
        delete Tp;
    if(res != NULL)
        delete res;
    if(OGSession != NULL)
        delete OGSession;

    return 0;
}
