#ifndef SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H
#define SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H

#include <hazelcast/client/hazelcast.h>
#include <vector>
#include <string>

#include <ppconsul/agent.h>
#include <ppconsul/catalog.h>
#include "ppconsul/kv.h"


using ppconsul::Consul;
using namespace ppconsul::agent;
using namespace ppconsul::catalog;
using namespace ppconsul::kv;


using namespace hazelcast::client;

class MessagesService {
private:
    Consul consul;
    Agent agent;
    Catalog catalog;
    Kv kv;

    hazelcast_client hz;
    std::shared_ptr<iqueue> que;
    std::vector<std::string> messages_in_memory;

    std::string serv_id;
public:
    MessagesService(int port): agent{consul},
                               catalog{consul},
                               kv{consul},
                               hz{hazelcast::new_client().get()} {

        std::string val = kv.get("msg_queue", "not found");

        que = hz.get_queue(val).get();

        serv_id = "127.0.0.1:" + std::to_string(port) + "/Messages";

        agent.registerService(
                ppconsul::agent::kw::name = "Messages",
                ppconsul::agent::kw::port = port,
                ppconsul::agent::kw::address = "127.0.0.1",
                ppconsul::agent::kw::id = serv_id
        );
    };


    void get_messages_from_q() {
        auto val = que->take<std::string>().get().get();
        messages_in_memory.push_back(val);
        std::cout << val << std::endl;
    }

    std::string get_messages() {
        std::string to_return = "(";
        for(const auto& elem : messages_in_memory) {
            to_return += elem + ", ";
        }
        to_return += ")";
        return to_return;
    }
};


#endif //SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H
