#include "logging_controller.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "You should specify port" << std::endl;
        return -1;
    }
    httpserver::webserver web_serv = httpserver::create_webserver(atoi(argv[1]));
    LoggingController logging(atoi(argv[1]));
    web_serv.register_resource("/Logging", &logging);
    web_serv.start(true);

}