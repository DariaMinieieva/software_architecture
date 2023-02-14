#ifndef SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
#define SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H

#include <iostream>
#include <httpserver.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cpr/cpr.h>
#include <string>

namespace ht = httpserver;
namespace bo = boost::uuids;

class facade_service : public ht::http_resource {
private:
    bo::random_generator  generator;

public:
    std::shared_ptr<ht::http_response> render_POST(const ht::http_request& req);
    std::shared_ptr<ht::http_response> render_GET(const ht::http_request& req);
};


#endif //SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
