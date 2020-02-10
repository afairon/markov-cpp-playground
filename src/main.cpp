#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "microservice_controller.hpp"
#include "interrupt_handler.hpp"
#include "markovchain.hpp"
#include "utils.hpp"

using namespace std;
using namespace web;
using namespace web::http;
using namespace utility;
using namespace web::http::experimental::listener;

int main(int argc, char** argv) {

    srand(time(NULL));
    
    MicroserviceController server("http://127.0.0.1:34568");

    // Initialize markov chain
    MarkovChain chain(2);
    for (int i = 1; i < argc; ++i) {
        chain.Read(argv[i]);
    }

    server.setChain(&chain);

    try {
        // Waiting for incoming connections
        server.accept().wait();

        cout << "Listening on " << server.uri() << endl;
        cout << "Waiting for incoming connections..." << endl;

        InterruptHandler::waitInterrupt();

        server.shutdown().wait();
    } catch (exception& e) {
        cerr << "Something wrong happened!" << endl;
        cerr << "Error: " << e.what() << endl;
        cerr << "Shutting down server" << endl;
    }

    return 0;
}
