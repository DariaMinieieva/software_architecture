#include "logging_service.h"

std::shared_ptr<ht::http_response> logging_service::render_POST(const ht::http_request& req) {
    auto args = req.get_args();
    for (const auto& el : args) {
        logging_map::accessor a;
        log_data.insert(a, std::string(el.first));
        a->second = std::string(el.second);

        std::cout << a->second << std::endl;
        a.release();
    }
    return std::shared_ptr<ht::http_response>(new ht::string_response("200: ok"));
}

std::shared_ptr<ht::http_response> logging_service::render_GET(const ht::http_request&) {
    std::string res = "[";
    for (const auto& el: log_data) {
        res += el.second + ", ";

    }
    res.pop_back();
    res.pop_back();
    res += "]";

    return std::shared_ptr<ht::http_response>(new ht::string_response(res));
}