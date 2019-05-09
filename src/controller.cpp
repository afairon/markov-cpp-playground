#include "controller.hpp"

using namespace std;
using namespace web;
using namespace http;

vector<string> Controller::requestPath(const http_request& message) {
    auto relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}