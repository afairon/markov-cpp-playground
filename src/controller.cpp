#include "controller.hpp"

using namespace std;
using namespace web;
using namespace http;

std::string Controller::uri() const {
    return _listener.uri().to_string();
}

pplx::task<void> Controller::accept() {
    opHandlers();
    return _listener.open();
}

pplx::task<void> Controller::shutdown() {
    return _listener.close();
}

vector<string> Controller::requestPath(const http_request& message) {
    auto relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}