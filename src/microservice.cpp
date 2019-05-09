#include "microservice_controller.hpp"
#include "version.hpp"

using namespace web;
using namespace http;

void MicroserviceController::handleGet(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET));
}

void MicroserviceController::handlePost(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void MicroserviceController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void MicroserviceController::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void MicroserviceController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void MicroserviceController::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void MicroserviceController::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

json::value MicroserviceController::responseNotImpl(const http::method& method) {
    auto response = json::value::object();

    response["service"] = json::value::string(U("Markov Playground"));
    response["version"] = json::value::string(U(version));
    response["method"] = json::value::string(U(method));

    return response;
}