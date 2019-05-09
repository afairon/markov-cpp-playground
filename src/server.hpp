#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <string>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

using namespace web;
using namespace http::experimental::listener;

class Server {
    protected:
        http_listener _listener;
    public:
        Server(const std::string addr) {
            uri_builder uri(addr);
            _listener = http_listener(uri.to_uri());
        }
        ~Server() {}

        std::string uri() const;

        pplx::task<void> accept();
        pplx::task<void> shutdown();
};

#endif