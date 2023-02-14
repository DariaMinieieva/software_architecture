#include "messages_service.h"

std::shared_ptr<ht::http_response> messages_service::render_GET(const ht::http_request&) {
    return std::shared_ptr<ht::http_response>(new ht::string_response("not implemented yet"));
}