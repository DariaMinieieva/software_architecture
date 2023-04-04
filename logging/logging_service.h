#ifndef FACADE_LOGGING_SERVICE_H
#define FACADE_LOGGING_SERVICE_H

#include <iostream>
#include <httpserver.hpp>
#include <cpr/cpr.h>
#include <hazelcast/client/hazelcast.h>

using namespace hazelcast::client;


namespace ht = httpserver;

class LoggingService {
private:
    hazelcast_client hz;
    std::shared_ptr<imap> logging_map;
public:
    LoggingService(): hz{hazelcast::new_client().get()}, logging_map{hz.get_map("logging_map").get()} {

    }

    void add_to_log(const std::map<std::string, std::string>& args) {
        for (const auto& el : args) {
            logging_map->put<std::string, std::string>(el.first, el.second).get();
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
