

#ifndef MICROSERVICES_LOGGING_CONTROLLER_H
#define MICROSERVICES_LOGGING_CONTROLLER_H

#include <iostream>
#include <httpserver.hpp>
#include <cpr/cpr.h>
#include "logging_service.h"

namespace ht = httpserver;


class LoggingController : public ht::http_resource {
private:
    LoggingService logging_service;
public:
    LoggingController(int port): logging_service{port} {};

    std::shared_ptr<ht::http_response> render_POST(const ht::http_request& req) {
        auto args = req.get_args();
        std::map<std::string, std::string> results;

        for (const auto& el : args) {
            results[std::string(el.first)] = std::string(el.second);
        }

        logging_service.add_to_log(results);
        return std::shared_ptr<ht::http_response>(new ht::string_response("200: ok"));

    }

    std::shared_ptr<ht::http_response> render_GET(const ht::http_request& req) {
        auto ttt = logging_service.get_log();
        return std::shared_ptr<ht::http_response>(new ht::string_response(ttt));
    }
};

#endif //MICROSERVICES_LOGGING_CONTROLLER_H
