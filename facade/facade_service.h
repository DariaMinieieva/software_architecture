#ifndef SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
#define SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H

#include <iostream>
#include <httpserver.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cpr/cpr.h>
#include <string>
#include <random>

namespace ht = httpserver;
namespace bo = boost::uuids;

class FacadeService {
private:
    bo::random_generator  generator{};
    std::string message_client;
    std::vector<cpr::Url> logging_clients{cpr::Url{"http://localhost:8082/logging_service"},
                                             cpr::Url{"http://localhost:8083/logging_service"},
                                             cpr::Url{"http://localhost:8084/logging_service"}};

public:
    FacadeService(): message_client{"http://localhost:8081/messages_service"}{

    };

    cpr::Url get_random_log_client() {
        std::srand(time(nullptr));
        return logging_clients[std::rand() % logging_clients.size()];
    }

    void add_messages(std::string msg) {
        auto msg_uuid = bo::to_string(generator());

        cpr::Response r = cpr::Post(get_random_log_client(),
                                    cpr::Payload{{msg_uuid, msg}});

    }


    std::string get_messages() {
        cpr::Response logs = cpr::Get(get_random_log_client());
        cpr::Response messages = cpr::Get(cpr::Url{message_client});
        return logs.text + ": " + messages.text;
    }
};


#endif //SOFTWARE_ARCHITECTURE_FACADE_SERVICE_H
