#include "microservice_controller.hpp"
#include "version.hpp"

using namespace web;
using namespace http;

void MicroserviceController::opHandlers() {
    _listener.support(methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&MicroserviceController::handlePatch, this, std::placeholders::_1));
    _listener.support(methods::HEAD, std::bind(&MicroserviceController::handleHead, this, std::placeholders::_1));
    _listener.support(methods::OPTIONS, std::bind(&MicroserviceController::handleOptions, this, std::placeholders::_1));
}

file_type MicroserviceController::getExt(const std::string& file) const {
    std::string ext = file.substr(file.find_last_of(".") + 1);
    if (ext == "html") {
        return HTML;
    } else if (ext == "css") {
        return CSS;
    } else if (ext == "js") {
        return JS;
    } else if (ext == "jpg" || ext == "jpeg") {
        return JPEG;
    } else if (ext == "png") {
        return PNG;
    } else if (ext == "webp") {
        return WEBP;
    } else if (ext == "ico") {
        return ICO;
    }

    return UNKNOWN;
}

void MicroserviceController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path.size() > 1 && path[0] == "api" && path[1] == "predict") {
            auto response = json::value::object();
            response["key"] = json::value::string("val");
            message.reply(status_codes::OK, response);
            return;
        }
    }
    message.reply(status_codes::NotFound, "404 NOT FOUND");
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