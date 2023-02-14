#include "logging_service.h"

int main() {
    httpserver::webserver web_serv = httpserver::create_webserver(8081);
    logging_service logging;
    web_serv.register_resource("/logging_service", &logging);
    web_serv.start(true);
    return 0;
}