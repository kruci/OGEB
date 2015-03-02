#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "Poco/StreamCopier.h"

#include "Position.h"

using namespace std;
using  Poco::StreamCopier;

//#define GTf3_DEBUG;

string GetToken_f3(istream &ofstr)
{
    ofstream pagef3;
    pagef3.open("pagef3.html");
    StreamCopier::copyStream(ofstr, pagef3);
    pagef3.close();

    /**------**/
    ifstream file;
    string line;
    string s_file("");
    string to_find("token");
    file.open("pagef3.html");
    size_t found;// = line.find(to_find);
    string token;

    if(file.is_open())
    {
        while(std::getline(file,line))
        {
            #ifdef GTf3_DEBUG
            cout<<line<<endl;
            #endif // GTf3_DEBUG
            s_file = s_file + line + '\n';
            found = line.find(to_find);

            if (found!=string::npos)
            {
                #ifdef GTf3_DEBUG
                cout << "token FOUND " << found << '\n';
                #endif // GTf3_DEBUG
                break;
            }

        }
        file.close();
  }

    const char *line_with_token = new char[line.length()];
    line_with_token = line.c_str();

    #ifdef GTf3_DEBUG
    cout<<"REST OF LINE :";

    for(int a = found; a < line.length();a++)
    {
        cout<<line_with_token[a];

    }
    #endif // GTf3_DEBUG

    found = line.find("value");
    if (found!=string::npos)
    {
        for(int a = found+6, number_of_toknes = 0; a < line.length();a++)
        {
            if(line_with_token[a] == '\'')
            {
                number_of_toknes++;
                if(number_of_toknes >= 2)
                {
                    break;
                }
                continue;
            }
            token = token + line_with_token[a];
        }

        #ifdef GTf3_DEBUG
        cout<<endl<<"TOKEN :"<<token<<endl;
        cout<<endl<<"START OF TOKEN|"<<token<<"|END OF TOKEN"<<endl;
        #endif // GTf3_DEBUG
    }
    #ifndef SAVE_HTML_FILES
    remove("pagef3.html");
    #endif //SAVE_HTML_FILES

    return token;
}


string GetPlaneCP(string login_file, Position &starting_planet)
{
    /*ofstream login;
    login.open("login.html");
    StreamCopier::copyStream(ofstr, login);
    login.close();*/

    string suradnice = ("[" + to_string(starting_planet.getGalaxy()) + ":" + to_string(starting_planet.getSolarSystem()) +
                        ":" + to_string(starting_planet.getPlanet()) + "]&lt;/B&gt;&lt;BR&gt");
    /**------**/
    ifstream file;
    string line;
    string s_file("");
    file.open(login_file);
    size_t found;// = line.find(to_find);
    string token;
    string last_line("");
    int a = 0;
    bool equalm = false;

    if(file.is_open())
    {
        while(std::getline(file,line))
        {
            a++;
            #ifdef GTf3_DEBUG
            cout<<line<<endl;
            #endif // GTf3_DEBUG
            s_file = s_file + line + '\n';
            found = line.find(suradnice);

            if (found!=string::npos)
            {
                #ifdef GTf3_DEBUG
                cout <<endl<<endl<< "Coordinates found " << found << '\n';
                #endif // GTf3_DEBUG
                break;
            }

        }
        file.close();
    }

    file.open(login_file);
    for(int as = 1;as < a;as++)
    {
        std::getline(file,last_line);
    }
    file.close();
    #ifdef GTf3_DEBUG
    cout<<endl<<"Lane before: "<<last_line<<endl;
    #endif // GTf3_DEBUG

    const char *line_with_token = new char[last_line.length()];
    line_with_token = last_line.c_str();
    found = last_line.find("cp=");

    #ifdef GTf3_DEBUG
    cout<<"Full line: "<<last_line<<endl<<endl;
    cout<<"Rest of line: ";

    //found = last_line.find("cp=");

    for(int a = found; a < last_line.length();a++)
    {
        cout<<line_with_token[a];

    }
    #endif // GTf3_DEBUG

    if (found!=string::npos)
    {
        for(int a = found; a < line.length();a++)
        {
            if(line_with_token[a] == '=')
            {
                equalm = true;
                a++;
            }
            if(line_with_token[a] == '\"')
                break;
            if(equalm == true)
                token = token + line_with_token[a];
        }

        #ifdef GTf3_DEBUG
        cout<<endl<<"TOKEN :"<<token<<endl;
        cout<<endl<<"START OF TOKEN|"<<token<<"|END OF TOKEN"<<endl;
        #endif // GTf3_DEBUG
    }
    return token;
}
