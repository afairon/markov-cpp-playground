#include "controller.hpp"

using namespace std;
using namespace web;
using namespace http;

// uri returns address of server
std::string Controller::uri() const {
    return _listener.uri().to_string();
}

// accept open connection
pplx::task<void> Controller::accept() {
    opHandlers();
    return _listener.open();
}

// shutdown close connection
pplx::task<void> Controller::shutdown() {
    return _listener.close();
}

// relativePath returns relative path
string Controller::relativePath(const http_request& message) {
    return uri::decode(message.relative_uri().path());
}

// requestPath returns uri vector
vector<string> Controller::requestPath(const http_request& message) {
    auto relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}