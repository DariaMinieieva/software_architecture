#ifndef FACADE_LOGGING_SERVICE_H
#define FACADE_LOGGING_SERVICE_H

#include <iostream>
#include <httpserver.hpp>
#include <cpr/cpr.h>
#include <hazelcast/client/hazelcast.h>
#include <ppconsul/agent.h>
#include <ppconsul/catalog.h>
#include "ppconsul/kv.h"


using ppconsul::Consul;
using namespace ppconsul::agent;
using namespace ppconsul::catalog;
using namespace ppconsul::kv;

using namespace hazelcast::client;


namespace ht = httpserver;

class LoggingService {
private:
    hazelcast_client hz;
    std::shared_ptr<imap> logging_map;

    Consul consul;
    Agent agent;
    Catalog catalog;
    Kv kv;

    std::string serv_id;
public:
    LoggingService(int port): hz{hazelcast::new_client().get()},
                              agent{consul},
                              catalog{consul},
                              kv{consul} {

        auto val = kv.get("log_map", "not found");
        logging_map = hz.get_map(val).get();

        serv_id = "127.0.0.1:" + std::to_string(port) + "/Logging";

        agent.registerService(
                ppconsul::agent::kw::name = "Logging",
                ppconsul::agent::kw::port = port,
                ppconsul::agent::kw::address = "127.0.0.1",
                ppconsul::agent::kw::id = "127.0.0.1:" + std::to_string(port) + "/Logging"
        );
    }


    void add_to_log(const std::map<std::string, std::string>& args) {
        for (const auto& el : args) {
            logging_map->put<std::string, std::string>(el.first, el.second).get();
            std::cout << el.second << std::endl;
        }

    }

    std::string get_log() {
        std::string res = "[";
        for (const auto& el : logging_map->values<std::string>().get()) {
            res += el + ", ";
        }

        res += "]";


        return res;
    }
};

#endif //FACADE_LOGGING_SERVICE_H
