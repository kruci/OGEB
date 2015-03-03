#ifndef OGAMESESSION_H
#define OGAMESESSION_H

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
#include "Position.h"
#include "Resources.h"

#include <iostream>
#include <fstream>
#include <string>


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

class OGameSession
{
    private:
        std::string server_prefix, name, pass;
        std::string localisation;
        std::string server_link = "ogame.gameforge.com";
        std::string server_suffix = "/main/login";
        std::string full_game_server_name;
        std::vector <HTTPCookie> rcookies;
        HTTPClientSession *session;
        NameValueCollection cookies;
    public:
        OGameSession(std::string server_prefix, std::string name, std::string pass);
        virtual ~OGameSession();
        bool login();
        bool sendFleet(Position &starting_position, Position &target_position, int mission_type, int ships[], int speed, int expedition_time, Resources &resources);
        bool loginCheck();
};

#endif // OGAMESEASION_H
