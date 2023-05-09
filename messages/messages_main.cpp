#include "messages_controller.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "You should specify port" << std::endl;
        return -1;
    }
    httpserver::webserver web_serv = httpserver::create_webserver(atoi(argv[1]));
    MessagesController messages;
    web_serv.register_resource("/messages_service", &messages);
    web_serv.start(false);

    while(true) {
        messages.get_messages_from_q();
    }
    return 0;
}