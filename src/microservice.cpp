#include <iostream>
#include <cpprest/filestream.h>
#include "microservice_controller.hpp"
#include "version.hpp"
#include "utils.hpp"

using namespace web;
using namespace http;

// opHandlers init REST method
void MicroserviceController::opHandlers() {
    _listener.support(methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&MicroserviceController::handlePatch, this, std::placeholders::_1));
    _listener.support(methods::HEAD, std::bind(&MicroserviceController::handleHead, this, std::placeholders::_1));
    _listener.support(methods::OPTIONS, std::bind(&MicroserviceController::handleOptions, this, std::placeholders::_1));
}

// getExt returns file type
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

// serveStatic serve static files
void MicroserviceController::serveStatic(const std::string& filepath, const http_request& message) {
    auto path = requestPath(message);
    std::string uri, file, ext, content_type;
    file_type type;
    if (path.size() < 2) {
        message.reply(status_codes::NotFound);
        return;
    }

    uri = "static";
    for (int i = 1; i < path.size(); ++i) {
        uri += "/";
        uri += path[i];
    }

    file = path[path.size()-1];

    type = getExt(file);

    switch (type) {
        case HTML:
            content_type = "text/html; charset=UTF-8";
            break;
        case CSS:
            content_type = "text/css; charset=UTF-8";
            break;
        case JS:
            content_type = "text/javascript; charset=UTF-8";
            break;
        case JPEG:
            content_type = "image/jpeg";
            break;
        case PNG:
            content_type = "image/png";
            break;
        case WEBP:
            content_type = "image/webp";
            break;
        default:
            content_type = "application/octet-stream";
            break;
    }

    concurrency::streams::fstream::open_istream(U(uri), std::ios::in).then([=](concurrency::streams::istream is) {
        message.reply(status_codes::OK, is, content_type).then([=](pplx::task<void> t) {
            try {
                t.get();
            } catch (...) {
                message.reply(status_codes::InternalError);
            }
        });
    }).then([=](pplx::task<void> t) {
        try {
            t.get();
        } catch (...) {
            message.reply(status_codes::NotFound);
        }
    });

    return;
}

// handleGet handles GET event
void MicroserviceController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "static") {
            return serveStatic("static", message);
        } else if (path.size() > 1 && path[0] == "api" && path[1] == "generate") {
            auto response = json::value::object();
            NGram tokens = {StartToken};
            for (; tokens.back() != EndToken;) {
                NGram::const_iterator begin = tokens.begin() + tokens.size()-1;
                NGram::const_iterator last = tokens.begin() + tokens.size();
                NGram sub(begin, last);
                std::string next = chain->Generate(sub);
                tokens.push_back(next);
            }
            NGram::const_iterator begin = tokens.begin() + 1;
            NGram::const_iterator last = tokens.begin() + tokens.size() - 1;
            NGram sub(begin, last);
            std::string generated = join(sub, " ");
            response["next"] = json::value::string(generated);
            message.reply(status_codes::OK, response);
            return;
        }
    }
    concurrency::streams::fstream::open_istream("static/index.html", std::ios::in).then([=](concurrency::streams::istream is) {
        message.reply(status_codes::OK, is, "text/html; charset=UTF-8");
    });
}

// handlePost handles POST event
void MicroserviceController::handlePost(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {

        // Precict word
        if (path.size() > 1 && path[0] == "api" && path[1] == "predict") {
            auto response = json::value::object();
            auto req = message.extract_json().get();
            auto seq = req["seq"].as_string();
            std::string next = chain->Generate(split(seq, ' '));
            response["next"] = json::value::string("");
            if (next.length() > 1 && next != EndToken) {
                response["next"] = json::value::string(next);
            }
            message.reply(status_codes::OK, response);
            return;

        // Train user-defined model
        } else if (path.size() > 1 && path[0] == "api" && path[1] == "train") {
            auto response = json::value::object();
            auto req = message.extract_json().get();
            auto seq = req["seq"].as_string();
            chain->Add(split(seq, ' '));
            response["OK"] = json::value::boolean(true);
            message.reply(status_codes::OK, response);
            return;
        }
    }
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

// handlePut handles PUT event
void MicroserviceController::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

// handleDelete handles DELETE event
void MicroserviceController::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

// handlePatch handles Patch event
void MicroserviceController::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

// handleHead handles HEAD event
void MicroserviceController::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

// handleOptions handles OPTIONS event
void MicroserviceController::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

// responseNotImpl returns default message when method has not been implemented yet
json::value MicroserviceController::responseNotImpl(const http::method& method) {
    auto response = json::value::object();

    response["service"] = json::value::string(U("Markov Playground"));
    response["version"] = json::value::string(U(version));
    response["method"] = json::value::string(U(method));

    return response;
}

// setChain assigns Markov chain to controller
void MicroserviceController::setChain(WordPrediction* ch) {
    chain = ch;
}