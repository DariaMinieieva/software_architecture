#include <hazelcast/client/hazelcast.h>
#include <thread>
using namespace hazelcast::client;
std::string KEY_VALUE = "1";



void task_2_not_lock(std::shared_ptr<imap>& map) {

    map->put<std::string, int>(KEY_VALUE, 0).get();

    for (int i = 0; i < 1000; i++){
        auto value = map->get<std::string, int>(KEY_VALUE).get();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        map->put<std::string, int>(KEY_VALUE, ++value.get()).get();
    }

}

void task_2_pessimistic_lock(std::shared_ptr<imap>& map) {
    map->put<std::string, int>(KEY_VALUE, 0).get();

    for (int i = 0; i < 1000; i++){
        map->lock(KEY_VALUE).get();
            int value = map->get<std::string, int>(KEY_VALUE).get().get();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            map->put<std::string, int>(KEY_VALUE, ++value).get();

        map->unlock(KEY_VALUE).get();
    }

}

void task_2_optimistic_lock(std::shared_ptr<imap>& map) {
    map->put<std::string, int>(KEY_VALUE, 0).get();

    for (int i = 0; i < 1000; i++){
        while(true){
            int value = map->get<std::string, int>(KEY_VALUE).get().get();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if(map->replace<std::string, int>(KEY_VALUE, value, value+1).get()) {
                break;
            }
        }
    }

}

void prepare_client() {
    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("some_map").get();

    //! uncomment needed function
    task_2_optimistic_lock(map);
//    task_2_pessimistic_lock(map);
//    task_2_not_lock(map);
}

int main() {

    std::vector<std::thread> clients_threads;


    for (int i = 0; i < 3; i++){
        clients_threads.emplace_back(prepare_client);
    }

    for (auto& client: clients_threads) {
        client.join();
    }


    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("some_map").get();
    std::cout << "Final result is " << map->get<std::string, int>(KEY_VALUE).get() << std::endl;

    return 0;
}