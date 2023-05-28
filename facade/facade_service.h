#ifndef SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
#define SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H

#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cpr/cpr.h>
#include <string>
#include <random>
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
namespace bo = boost::uuids;

class FacadeService {
private:
    bo::random_generator  generator{};
    hazelcast_client hz;
    std::shared_ptr<iqueue> que;

    std::string msg_serv = "Messages";
    std::string log_serv = "Logging";

    Consul consul;
    Agent agent;
    Catalog catalog;
    Kv kv;

    std::string serv_id;
public:
    FacadeService(int port): hz{hazelcast::new_client().get()},
                     agent{consul},
                     catalog{consul},
                     kv{consul}{


        std::srand(time(nullptr));


        serv_id = "127.0.0.1:" + std::to_string(port) + "/Facade";
        agent.registerService(
                ppconsul::agent::kw::name = "Facade",
                ppconsul::agent::kw::port = port,
                ppconsul::agent::kw::address = "127.0.0.1",
                ppconsul::agent::kw::id = serv_id
        );

        kv.set("msg_queue", "messages_queue");
        kv.set("log_map", "logging_map");

        std::string val = kv.get("msg_queue", "not found");

        que = hz.get_queue(val).get();

    };



    cpr::Url get_consul_client(std::string name) {
        auto servs = catalog.service(name);
        auto rand_serv = servs[std::rand() % servs.size()];
        return "http://" + rand_serv.second.address + ":" + std::to_string(rand_serv.second.port) + "/" + name;
    }


    void add_messages(std::string msg) {
        que->put(msg).get();

        auto msg_uuid = bo::to_string(generator());
        cpr::Response r = cpr::Post(get_consul_client(log_serv),
                                    cpr::Payload{{msg_uuid, msg}});
    }


    std::string get_messages() {
        cpr::Response logs = cpr::Get(get_consul_client(log_serv));
        cpr::Response messages = cpr::Get(get_consul_client(msg_serv));
        return logs.text + ": " + messages.text;
    }
};


#endif //SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
