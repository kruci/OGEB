#include <iostream>
#include <fstream>
#include <string>
#include "OGameSession.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPCookie.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "FleetVariables.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::HTMLForm;
using Poco::Net::HTTPCookie;
using Poco::Net::NameValueCollection;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

OGameSession::OGameSession(std::string server_prefix, std::string name, std::string pass) : server_prefix(server_prefix), name(name), pass(pass)
{
    full_game_server_name = server_prefix + "." + server_link + server_suffix;

    //extracting localisation
    char l[5];
    bool pomlcka = false;
    int lenght = server_prefix.length(), b = 0;

    for(int a = 0;a < lenght;a++)
    {
        if(server_prefix[a] == '-')
        {
            pomlcka = true;
            continue;
        }
        if(pomlcka == true)
        {
            l[b] =  server_prefix[a];
            b++;
        }

    }
    l[b] = 0;

    localisation = l;

    #ifdef DEBUG
    std::cout<<std::endl<<localisation<<std::endl;
    #endif // DEBUG

    session = new HTTPClientSession(server_prefix + "." + server_link);
    session->setKeepAlive(true);

}

OGameSession::~OGameSession()
{

}

bool OGameSession::login()
{
    /**1. stage of login**/
    HTTPClientSession* session1 = new HTTPClientSession(localisation + "." + server_link);
    session1->setKeepAlive(true);

    HTTPRequest req(HTTPRequest::HTTP_POST, server_suffix, HTTPMessage::HTTP_1_1);
    req.setContentType("application/x-www-form-urlencoded");
    req.setKeepAlive(true);
    std::string reqBody("kid=&uni=" + server_prefix + "." + server_link + "&login=" + name + "&pass=" + pass);
    req.setContentLength(reqBody.length());
    session1->sendRequest(req) << reqBody;

    HTTPResponse res;
    std::istream& rs = session1->receiveResponse(res);
    std::string redirect;

    //res.getCookies(cookies);
    redirect = res.get("Location");

    #ifdef DEBUG
    std::cout<<"#Login Request - stage 1"<<std::endl<<server_prefix<<"."<<server_link<<server_suffix<<std::endl;
    std::cout<<reqBody<<std::endl;
    req.write(std::cout);
    std::cout<<res.getStatus()<<" "<<res.getReason()<< std::endl;
    res.write(std::cout);
    std::cout<<"Redirecting to: "<<redirect<<std::endl<<std::endl;
    #endif // DEBUG

    /**2. stage of login**/
    URI ruri(redirect);
    HTTPRequest req2(HTTPRequest::HTTP_GET, ruri.getPathEtc(),HTTPMessage::HTTP_1_1);
    req2.setContentType("application/x-www-form-urlencoded");
    req2.setKeepAlive(true);
    std::string req2Body(ruri.getRawQuery());
    req2.setContentLength(req2Body.length());
    session->sendRequest(req2) << req2Body;

    HTTPResponse res2;
    std::istream& rs2 = session->receiveResponse(res2);
    std::string redirect2;
    redirect2 = res2.get("Location");
    res2.getCookies(rcookies);

    int number_of_cookies = rcookies.size();

    for(int a = 0;a < number_of_cookies;a++)
    {
        cookies.add(rcookies[a].getName(), rcookies[a].getValue());
    }

    #ifdef DEBUG
    std::cout<<"#Login Request - stage 2"<<std::endl<<server_prefix<<"."<<server_link<<ruri.getPathEtc()<<std::endl;
    std::cout<<req2Body<<std::endl;
    req2.write(std::cout);
    std::cout<<res2.getStatus()<<" "<<res2.getReason()<< std::endl;
    res2.write(std::cout);
    std::cout<<"Redirecting to: "<<redirect2<<std::endl<<std::endl;
    /*std::cout<<rcookies[0].toString()<<std::endl
             <<rcookies[0].getComment()<<std::endl
             <<rcookies[0].getDomain()<<std::endl
             <<rcookies[0].getMaxAge()<<std::endl
             <<rcookies[0].getName()<<std::endl
             <<rcookies[0].getPriority()<<std::endl
             <<rcookies[0].getSecure()<<std::endl
             <<rcookies[0].getValue()<<std::endl
             <<rcookies[0].getVersion()<<std::endl
             <<rcookies[0].getPath()<<std::endl;*/
    #endif // DEBUG

    /**3. stage of login**/
    URI ruri2(redirect2);
    HTTPRequest req3(HTTPRequest::HTTP_GET, ruri2.getPathEtc(),HTTPMessage::HTTP_1_1);
    req3.setContentType("application/x-www-form-urlencoded");
    req3.setKeepAlive(true);
    std::string req3Body(ruri2.getRawQuery());
    req3.setContentLength(req3Body.length());
    req3.setCookies(cookies);
    session->sendRequest(req3) << req3Body;

    HTTPResponse res3;
    std::istream& rs3 = session->receiveResponse(res3);
    //res3.getCookies(rcookies);

    #ifdef DEBUG
    std::cout<<"#Login Request - stage 3"<<std::endl<<server_prefix<<"."<<server_link<<ruri2.getPathEtc()<<std::endl;
    std::cout<<req3Body<<std::endl;
    req3.write(std::cout);
    std::cout<<res3.getStatus()<<" "<<res3.getReason()<< std::endl;
    res3.write(std::cout);
    #endif // DEBUG

    if(res3.getStatus() == 200)
    {
        #ifdef CLASS_STATUSPRINTING
        std::cout<<std::endl
                 <<"---------------------"<<std::endl
                 <<"| Login successful! |"<<std::endl
                 <<"---------------------"<<std::endl;
        #endif // CLASS_STATUSPRINTING
        return true;
    }
    #ifdef CLASS_STATUSPRINTING
    std::cout<<std::endl
    <<"----------------------"<<std::endl
    <<"| Connection failed! |"<<std::endl
    <<"----------------------"<<std::endl;
    #endif // CLASS_STATUSPRINTING
    return false;
}

bool OGameSession::sendFleet(Position* starting_position, Position* target_position, int mission_type, int ships[], int speed, int expedition_time, Resources* resources)
{
    return true;
}
