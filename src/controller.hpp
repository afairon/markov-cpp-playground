#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <string>
#include <vector>
#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class Controller {
    protected:
        http_listener _listener;
    public:
        Controller(const std::string& addr) {
            uri_builder uri(addr);
            _listener = http_listener(uri.to_uri());
        }
        ~Controller() {};
        virtual void handleGet(http_request message) = 0;
        virtual void handlePost(http_request message) = 0;
        virtual void handlePut(http_request message) = 0;
        virtual void handleDelete(http_request message) = 0;
        virtual void handlePatch(http_request message) = 0;
        virtual void handleHead(http_request message) = 0;
        virtual void handleOptions(http_request message) = 0;
        
        virtual void opHandlers() = 0;

        std::vector<std::string> requestPath(const http_request& message);

        std::string uri() const;
        pplx::task<void> accept();
        pplx::task<void> shutdown();
};

#endif