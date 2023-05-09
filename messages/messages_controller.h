#ifndef MICROSERVICES_MESSAGES_CONTROLLER_H
#define MICROSERVICES_MESSAGES_CONTROLLER_H

#include <iostream>
#include <httpserver.hpp>
#include "messages_service.h"

namespace ht = httpserver;

class MessagesController : public ht::http_resource {
private:
    MessagesService message_service{};
public:
    std::shared_ptr<ht::http_response> render_GET(const ht::http_request&) {
        return std::shared_ptr<ht::http_response>(new ht::string_response(message_service.get_messages()));
    }

    void get_messages_from_q() {
        return message_service.get_messages_from_q();
    }
};

#endif //MICROSERVICES_MESSAGES_CONTROLLER_H
