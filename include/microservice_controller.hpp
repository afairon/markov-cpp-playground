#ifndef MICROSERVICE_CONTROLLER_HPP_
#define MICROSERVICE_CONTROLLER_HPP_

#include <string>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

#include "controller.hpp"
#include "markovchain.hpp"

using namespace web;
using namespace http;
using namespace http::experimental::listener;

// File text extension
typedef enum {
    UNKNOWN,
    HTML,
    CSS,
    JS,
    JPEG,
    PNG,
    WEBP,
    ICO
} file_type;

// Controller for handling REST method
class MicroserviceController : public Controller {
    private:
        file_type getExt(const std::string& file) const;
        static json::value responseNotImpl(const http::method& method);
        void serveStatic(const std::string& path, const http_request& message);
        WordPrediction* chain;
    public:
        MicroserviceController(const std::string& addr) : Controller(addr) {}
        ~MicroserviceController() {}
        void handleGet(http_request message) override;
        void handlePost(http_request message) override;
        void handlePut(http_request message) override;
        void handleDelete(http_request message) override;
        void handlePatch(http_request message) override;
        void handleHead(http_request message) override;
        void handleOptions(http_request message) override;

        void opHandlers() override;

        void setChain(WordPrediction* chain);
};

#endif