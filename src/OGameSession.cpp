#include <iostream>
#include <fstream>
#include <string>

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

#include "OGameSession.h"
#include "FleetVariables.h"
//#include "Position.h"
#include "Resources.h"
#include "FleetVariables.h"
#include "Functions.h"

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

    //StreamCopier::copyStream(rs3, std::cout);

    #ifdef SAVE_HTML_FILES
    std::ofstream login;
    login.open("login.html");
    StreamCopier::copyStream(rs3, login);
    login.close();
    #endif // SAVE_HTML_FILES

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

bool OGameSession::sendFleet(Position &starting_position, Position &target_position, int mission_type, int ships[], int speed, int expedition_time, Resources &resources)
{
    std::string shipsrequest("");
    std::string token("");
    std::string ShipStringAndNumber[13];
    std::string ShipStringAndNumber_pf[13];
    std::string pf_ships("");
    for(int tt = 0;tt <=12;tt++)
    {
        ShipStringAndNumber[tt] = "&" + ships::ships_strings[tt] + "=" + std::to_string(ships[tt]);
        ShipStringAndNumber_pf[tt] = "%26" + ships::ships_strings[tt] + "%3D" + std::to_string(ships[tt]);
        if(ships[tt] > 0)
        {
            shipsrequest = shipsrequest + ShipStringAndNumber[tt];
            pf_ships = pf_ships + ShipStringAndNumber_pf[tt];
        }
    }

    std::string sresources = ("&metal=" + std::to_string(resources.getMetal()) + "&crystal=" + std::to_string(resources.getCrystal()) +"&deuterium="
                              + std::to_string(resources.getDeuterium()));

    /**page=fleet1--------------------------------------------------------------------------------------**/
    HTTPRequest fleet1(HTTPRequest::HTTP_GET, "/game/index.php?page=fleet1", HTTPMessage::HTTP_1_1);
    fleet1.setContentType("application/x-www-form-urlencoded");
    fleet1.setKeepAlive(true);
    std::string fleet1_reqBody("page=fleet1");
    fleet1.setContentLength(fleet1_reqBody.length());
    fleet1.setCookies(cookies);
    session->sendRequest(fleet1) << fleet1_reqBody;

    HTTPResponse fleet1_res;
    std::istream& fleet1_resString = session->receiveResponse(fleet1_res);

    #ifdef SAVE_HTML_FILES
    std::ofstream pagef1;
    pagef1.open("pagef1.html");
    StreamCopier::copyStream(fleet1_resString, pagef1);
    pagef1.close();
    #endif // SAVE_HTML_FILES

    #ifdef DEBUG
    std::cout<<std::endl<<"#Sending Fleet - stage 1"<<std::endl<<server_prefix<<"."<<server_link<<"/game/index.php?page=fleet1"<<std::endl;
    std::cout<<fleet1_reqBody<<std::endl;
    fleet1.write(std::cout);
    std::cout<<fleet1_res.getStatus()<<" "<<fleet1_res.getReason()<< std::endl;
    fleet1_res.write(std::cout);
    #endif // DEBUG

    /**page=fleet2--------------------------------------------------------------------------------------**/
    std::string linkf2 = ("/game/index.php?page=fleet2%26galaxy%3D" +std::to_string(starting_position.getGalaxy())
                          +"%26system%3D"+std::to_string(starting_position.getSolarSystem())
                          +"%26position%3D"+std::to_string(starting_position.getPlanet())
                          +"%26type%3D1&mission%3D"+std::to_string(mission_type)+"%26speed%3D"+std::to_string(speed)
                          + pf_ships);

     std::string fleet2_reqBody = ("galaxy="+std::to_string(starting_position.getGalaxy())+"&system="+std::to_string(starting_position.getSolarSystem())
                                  +"&position="+std::to_string(starting_position.getPlanet())+
                                  "&type=1&mission="+std::to_string(mission_type)+"&speed="+std::to_string(speed)+shipsrequest);


    HTTPRequest fleet2(HTTPRequest::HTTP_POST,"/game/index.php?page=fleet2&" + fleet2_reqBody/*linkf2*/, HTTPMessage::HTTP_1_1);
    fleet2.setContentType("application/x-www-form-urlencoded");
    fleet2.setKeepAlive(true);
    fleet2.setCookies(cookies);
    std::ostream& myOStream = session->sendRequest(fleet2);
    myOStream << fleet2_reqBody;

    HTTPResponse fleet2_res;
    std::istream& fleet2_resString = session->receiveResponse(fleet2_res);

    //std::cerr << fleet2_resString.rdbuf();

    #ifdef SAVE_HTML_FILES
    std::ofstream pagef2;
    pagef2.open("pagef2.html");
    StreamCopier::copyStream(fleet2_resString, pagef2);
    pagef2.close();
    #endif // SAVE_HTML_FILES


    #ifdef DEBUG
    std::cout<<"#Sending Fleet - stage 2"<<std::endl<<server_prefix<<"."<<server_link<<"/game/index.php?page=fleet2"<<std::endl;
    std::cout<<fleet2_reqBody<<std::endl;
    fleet2.write(std::cout);
    std::cout<<fleet2_res.getStatus()<<" "<<fleet2_res.getReason()<< std::endl;
    fleet2_res.write(std::cout);
    #endif // DEBUG

    /**page=fleet3--------------------------------------------------------------------------------------**/
    //%26 = & %3D =  =
    std::string linkf3 = ("/game/index.php?page=fleet3%26type%3D1%26mission3D" + std::to_string(mission_type) + "%26union%3D0" +
                          pf_ships + "%26galaxy%3D" + std::to_string(target_position.getGalaxy())+"%26system%3D" +
                          std::to_string(target_position.getSolarSystem()) + "%26position%3D" +
                          std::to_string(target_position.getPlanet()) + "%26acsValues%3D-" + "%26speed%3D" + std::to_string(speed));

    std::string fleet3_reqBody = ("type=1&mission=" + std::to_string(mission_type) + "&union=0" + shipsrequest + "&galaxy=" +
                                 std::to_string(target_position.getGalaxy())+"&system="+std::to_string(target_position.getSolarSystem()) +
                                 "&position="+std::to_string(target_position.getPlanet()) + "&acsValues=-" + "&speed=" + std::to_string(speed));


    HTTPRequest fleet3(HTTPRequest::HTTP_POST, "/game/index.php?page=fleet3&" + fleet3_reqBody /* linkf3*/, HTTPMessage::HTTP_1_1);
    fleet3.setContentType("application/x-www-form-urlencoded");
    fleet3.setKeepAlive(true);
    fleet3.setContentLength(fleet3_reqBody.length());
    fleet3.setCookies(cookies);

    session->sendRequest(fleet3) << fleet3_reqBody;
    HTTPResponse fleet3_res;
    std::istream& fleet3_resString = session->receiveResponse(fleet3_res);

    /*std::ofstream pagef3;
    pagef3.open("pagef3.html");
    StreamCopier::copyStream(fleet3_resString, pagef3);
    pagef3.close();*/

    #ifdef DEBUG
    std::cout<<"#Sending Fleet - stage 3"<<std::endl<<server_prefix<<"."<<server_link<<"/game/index.php?page=fleet3"<<std::endl;
    std::cout<<fleet3_reqBody<<std::endl;
    fleet3.write(std::cout);
    std::cout<<fleet3_res.getStatus()<<" "<<fleet3_res.getReason()<< std::endl;
    fleet3_res.write(std::cout);
    #endif // DEBUG

    /**Get token---------------------------------------------------------------------------------**/
    token = GetToken_f3(fleet3_resString);

    #ifdef DEBUG
    std::cout<<std::endl<<std::endl<<"token ="<<token<<std::endl<<std::endl;
    #endif // DEBUG

    /**Send--------------------------------------------------------------------------------------**/
    std::string fleet4_reqBody = ("holdingtime=" + std::to_string(expedition_time) + "&expeditiontime=" + std::to_string(expedition_time) + "&token=" +
                                  token + "&galaxy=" +
                                  std::to_string(target_position.getGalaxy())+"&system="+std::to_string(target_position.getSolarSystem()) +
                                  "&position="+std::to_string(target_position.getPlanet()) + "&type=1&mission=" + std::to_string(mission_type) +
                                  "&union2=0&holdingOrExpTime=" + "&speed=" + std::to_string(speed) +
                                  "&acsValues=-" + shipsrequest + sresources);

    HTTPRequest fleet4(HTTPRequest::HTTP_POST, "/game/index.php?page=movement"/*&" + fleet4_reqBody*/, HTTPMessage::HTTP_1_1);
    fleet4.setContentType("application/x-www-form-urlencoded");
    fleet4.setKeepAlive(true);
    fleet4.setContentLength(fleet4_reqBody.length());
    fleet4.setCookies(cookies);
    session->sendRequest(fleet4) << fleet4_reqBody;

    HTTPResponse fleet4_res;
    std::istream& fleet4_resString = session->receiveResponse(fleet4_res);

    #ifdef SAVE_HTML_FILES
    std::ofstream movement;
    movement.open("movement.html");
    StreamCopier::copyStream(fleet4_resString, movement);
    movement.close();
    #endif // SAVE_HTML_FILES

    #ifdef DEBUG
    std::cout<<"#Sending Fleet - stage 4"<<std::endl<<server_prefix<<"."<<server_link<<"/game/index.php?page=movement"<<std::endl;
    std::cout<<fleet4_reqBody<<std::endl;
    fleet4.write(std::cout);
    std::cout<<fleet4_res.getStatus()<<" "<<fleet4_res.getReason()<< std::endl;
    fleet4_res.write(std::cout);
    #endif // DEBUG


    if(fleet4_res.getStatus() == 200)
        return true;
    else
        return false;
}
