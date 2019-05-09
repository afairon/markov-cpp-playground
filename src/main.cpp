#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "markov.hpp"
#include "microservice_controller.hpp"
#include "interupt_handler.hpp"
#include "chain.hpp"
#include "utils.hpp"

using namespace std;
using namespace web;
using namespace web::http;
using namespace utility;
using namespace web::http::experimental::listener;

int main(int argc, char** argv) {

    srand(time(NULL));
    
    MicroserviceController server("http://127.0.0.1:34568");

    Chain chain(2);
    for (int i = 0; i < argc; ++i) {
        chain.Read(argv[i]);
    }

    server.setChain(&chain);

    try {
        server.accept().wait();

        cout << "Listening on " << server.uri() << endl;
        cout << "Waiting for incoming connections..." << endl;

        InteruptHandler::waitInterupt();

        server.shutdown().wait();
    } catch (exception& e) {
        cerr << "Something wrong happened!" << endl;
        cerr << "Error: " << e.what() << endl;
        cerr << "Shutting down server" << endl;
    }

    return 0;
}
