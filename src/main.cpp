#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "server.hpp"

using namespace std;
using namespace web;
using namespace web::http;
using namespace utility;
using namespace web::http::experimental::listener;

int main(int argc, char** argv) {

    Server server;

    server.accept().wait();

    return 0;
}
