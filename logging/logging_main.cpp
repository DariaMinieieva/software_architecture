#include "logging_controller.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "You should specify port" << std::endl;
        return -1;
    }
    httpserver::webserver web_serv = httpserver::create_webserver(atoi(argv[1]));
    LoggingController logging;
    web_serv.register_resource("/logging_service", &logging);
    web_serv.start(true);

}