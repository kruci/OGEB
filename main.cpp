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
    char option;
    int number_of_expeditions;
    int ships[13] = {0};
    int t1,t2,t3,s,ht;
    bool requests_set1 = true;
    string server, pass, name, filename;
    OGameSession *OGSession = NULL;
    Position *Sp = NULL, *Tp = NULL;
    Resources *res = NULL;
    AutoPtr<IniFileConfiguration> xConf;
    time_t send, act_time;
    time_t rawtime;
    struct tm * timeinfo;
    string strtime;


    cout << "OGame Expeditions Bot by R.K"<<endl<<endl;
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

    cin >> pass;

    SetConsoleMode(hStdin, mode);
    #else
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cin >> pass;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif // WIN32 or *NIX


    OGSession = new OGameSession(server, name, pass);

    cout << endl << "File name: ";
    cin >> filename;

    xConf = new IniFileConfiguration(filename);
    t1 = xConf->getInt("StartingPosition.G");
    t2 = xConf->getInt("StartingPosition.S");
    t3 = xConf->getInt("StartingPosition.P");
    Sp = new Position(t1,t2,t3);
    t1 = xConf->getInt("TargetPosition.G");
    t2 = xConf->getInt("TargetPosition.S");
    t3 = xConf->getInt("TargetPosition.P");
    Tp = new Position(t1,t2,t3);
    s = xConf->getInt("Other.Speed");
    ht = xConf->getInt("Other.HoldTime");
    number_of_expeditions = xConf->getInt("Other.NumberOfExpedition");
    t1 = xConf->getInt("Resources.M");
    t2 = xConf->getInt("Resources.C");
    t3 = xConf->getInt("Resources.D");
    res = new Resources(t1,t2,t3);

    for(int a = 0; a <= 12; a++)
    {
        ships[a] = xConf->getInt("Ships." + to_string(a));
    }

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

            OGSession->login();
            for(int as = 0, f = 0; as < number_of_expeditions;)
            {
                if(OGSession->sendFleet(*Sp, *Tp, mission::expedition, ships, s, ht, *res) == true)
                {
                    as++;
                    cout << "Fleet Sent" << endl;
                }
                else
                {
                    f++;
                    cout << "f ";
                }

                if(f >= 30)
                {
                    f = 0;
                    OGSession->login();
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
