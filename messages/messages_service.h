#ifndef SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H
#define SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H

#include <hazelcast/client/hazelcast.h>
#include <vector>
#include <string>

using namespace hazelcast::client;

class MessagesService {
private:
    hazelcast_client hz;
    std::shared_ptr<iqueue> que;
    std::vector<std::string> messages_in_memory;
public:
    MessagesService(): hz{hazelcast::new_client().get()},
                       que{hz.get_queue("messages_queue").get()} {

    };

    void get_messages_from_q() {
        auto val = que->take<std::string>().get().get();
        messages_in_memory.push_back(val);
        std::cout << val << std::endl;
    }

    std::string get_messages() {
        std::string to_return = "(";
        for(const auto& elem : messages_in_memory) {
            to_return += elem + ", ";
        }
        to_return += ")";
        return to_return;
    }
};


#endif //SOFTWARE_ARCHITECTURE_MESSAGES_SERVICE_H
