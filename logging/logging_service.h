#ifndef FACADE_LOGGING_SERVICE_H
#define FACADE_LOGGING_SERVICE_H

#include <iostream>
#include <httpserver.hpp>
#include "tbb/concurrent_hash_map.h"
#include <cpr/cpr.h>

// from tbb concurrent map documentation
class hash_comp_func {
public:
    static size_t hash( const std::string& x ) {
        size_t h = 0;
        for( const char* s = x.c_str(); *s; ++s )
            h = (h*17)^*s;
        return h;
    }

    static bool equal(const std::string& x, const std::string& y ) {
        return x==y;
    }
};


namespace ht = httpserver;
typedef  tbb::concurrent_hash_map<std::string, std::string, hash_comp_func> logging_map;

class logging_service : public ht::http_resource {
private:
    logging_map log_data;
public:
    std::shared_ptr<ht::http_response> render_POST(const ht::http_request& req);
    std::shared_ptr<ht::http_response> render_GET(const ht::http_request&);
};

#endif //FACADE_LOGGING_SERVICE_H
