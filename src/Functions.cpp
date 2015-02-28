#include <iostream>
#include <fstream>
#include <string>

#include "Poco/StreamCopier.h"

using namespace std;
using  Poco::StreamCopier;

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

