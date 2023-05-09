#ifndef MICROSERVICES_FACADE_CONTROLLER_H
#define MICROSERVICES_FACADE_CONTROLLER_H

#include <httpserver.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cpr/cpr.h>
#include <string>
#include "facade_service.h"
#include <iostream>

namespace ht = httpserver;
namespace bo = boost::uuids;

class FacadeController : public ht::http_resource {
private:
    bo::random_generator  generator;
    FacadeService facade_service{};

public:
    FacadeController(){};
    std::shared_ptr<ht::http_response> render_POST(const ht::http_request& req) {
        facade_service.add_messages(std::string(req.get_content()));
        return std::shared_ptr<ht::http_response>(new ht::string_response("ok: 200"));
    }

    std::shared_ptr<ht::http_response> render_GET(const ht::http_request& req) {
        return std::shared_ptr<ht::http_response>(new ht::string_response(facade_service.get_messages()));
    }
};
#endif //MICROSERVICES_FACADE_CONTROLLER_H
