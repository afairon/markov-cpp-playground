#ifndef ROUTER_HPP_
#define ROUTER_HPP_

#include <map>
#include <string>
#include <vector>

#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

class Router {
    private:
        std::map<std::string, void (*)(http_request)> routes;
    public:
        Router() {}
        ~Router() {}
        void GET(const std::string& endpoint);
        void POST(const std::string& endpoint);
        void PUT(const std::string& endpoint);
        void DEL(const std::string& endpoint);
        void PATCH(const std::string& endpoint);
        void HEAD(const std::string& endpoint);
        void OPTIONS(const std::string& endpoint);
};

#endif