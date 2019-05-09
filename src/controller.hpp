#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <string>
#include <vector>
#include <cpprest/http_listener.h>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class Controller {
    protected:
        http_listener _listener;
    public:
        Controller() {}
        ~Controller() {}
        virtual void handleGet(http_request message) = 0;
        virtual void handlePost(http_request message) = 0;
        virtual void handlePut(http_request message) = 0;
        virtual void handleDelete(http_request message) = 0;
        virtual void handlePatch(http_request message) = 0;
        virtual void handleHead(http_request message) = 0;
        virtual void handleOptions(http_request message) = 0;

        std::vector<std::string> requestPath(const http_request& message);
};

#endif