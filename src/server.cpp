#include "server.hpp"

using namespace std;

string Server::uri() const {
    return _listener.uri().to_string();
}

pplx::task<void> Server::accept() {
    return _listener.open();
}

pplx::task<void> Server::shutdown() {
    return _listener.close();
}