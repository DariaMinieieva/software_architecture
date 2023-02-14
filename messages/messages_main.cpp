#include "messages_service.h"

int main() {
    httpserver::webserver web_serv = httpserver::create_webserver(8082);
    messages_service messages;
    web_serv.register_resource("/messages_service", &messages);
    web_serv.start(true);
    return 0;
}