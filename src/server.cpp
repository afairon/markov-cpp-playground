#include "server.hpp"

using namespace std;

pplx::task<void> Server::accept() {
    return _listener.open();
}

pplx::task<void> Server::shutdown() {
    return _listener.close();
}