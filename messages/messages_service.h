#ifndef SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H
#define SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H

#include <iostream>
#include <httpserver.hpp>

namespace ht = httpserver;

class messages_service : public ht::http_resource {
public:
    std::shared_ptr<ht::http_response> render_GET(const ht::http_request&);
};

#endif //SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H
