#include <iostream>
#include "facade_service.h"

int main() {
    httpserver::webserver web_serv = httpserver::create_webserver(8080);
    facade_service facade;
    web_serv.register_resource("/facade_service", &facade);
    web_serv.start(true);
    return 0;
}