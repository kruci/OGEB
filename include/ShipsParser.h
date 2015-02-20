#ifndef SHIPSPARSER_H
#define SHIPSPARSER_H

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
#include <iostream>



class ShipsParser
{
    private:
    public:
        ShipsParser();
        virtual ~ShipsParser();
    protected:

};

#endif // SHIPSPARSER_H
