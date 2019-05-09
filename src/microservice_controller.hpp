#ifndef MICROSERVICE_CONTROLLER_HPP_
#define MICROSERVICE_CONTROLLER_HPP_

#include "controller.hpp"

class MicroserviceController : public Controller {
    private:
        static json::value responseNotImpl(const http::method& method);
    public:
        MicroserviceController() : Controller() {}
        ~MicroserviceController() {}
        void handleGet(http_request message) override;
        void handlePost(http_request message) override;
        void handlePut(http_request message) override;
        void handleDelete(http_request message) override;
        void handlePatch(http_request message) override;
        void handleHead(http_request message) override;
        void handleOptions(http_request message) override;
};

#endif