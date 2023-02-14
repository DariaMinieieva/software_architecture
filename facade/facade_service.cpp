#include "facade_service.h"

std::shared_ptr<ht::http_response> facade_service::render_POST(const ht::http_request& req) {
    auto msg_uuid = bo::to_string(generator());

    cpr::Response r = cpr::Post(cpr::Url{"http://localhost:8081/logging_service"},
                                cpr::Payload{{msg_uuid, std::string(req.get_content())}});

    return std::shared_ptr<ht::http_response>(new ht::string_response("ok: 200"));
}

std::shared_ptr<ht::http_response> facade_service::render_GET(const ht::http_request& req) {
    cpr::Response logs = cpr::Get(cpr::Url{"http://localhost:8081/logging_service"});
    cpr::Response messages = cpr::Get(cpr::Url{"http://localhost:8082/messages_service"});
    return std::shared_ptr<ht::http_response>(new ht::string_response(logs.text + ": " + messages.text));
}