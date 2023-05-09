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

using namespace hazelcast::client;

namespace ht = httpserver;
namespace bo = boost::uuids;

class FacadeService {
private:
    bo::random_generator  generator{};
    std::vector<cpr::Url> message_clients{"http://localhost:8081/messages_service",
                                          "http://localhost:8082/messages_service"};

    std::vector<cpr::Url> logging_clients{cpr::Url{"http://localhost:8083/logging_service"},
                                             cpr::Url{"http://localhost:8084/logging_service"},
                                             cpr::Url{"http://localhost:8085/logging_service"}};
    hazelcast_client hz;
    std::shared_ptr<iqueue> que;
public:
    FacadeService(): hz{hazelcast::new_client().get()},
                     que{hz.get_queue("messages_queue").get()}  {
        std::srand(time(nullptr));
    };

    cpr::Url get_random_log_client() {

        return logging_clients[std::rand() % logging_clients.size()];
    }

    cpr::Url get_random_message_client() {
//        std::srand(time(nullptr));
        return message_clients[std::rand() % message_clients.size()];
    }

    void add_messages(std::string msg) {
        que->put(msg).get();

        auto msg_uuid = bo::to_string(generator());
        cpr::Response r = cpr::Post(get_random_log_client(),
                                    cpr::Payload{{msg_uuid, msg}});
    }


    std::string get_messages() {
        cpr::Response logs = cpr::Get(get_random_log_client());
        cpr::Response messages = cpr::Get(get_random_message_client());
        return logs.text + ": " + messages.text;
    }
};


#endif //SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
