#include <hazelcast/client/hazelcast.h>

using namespace hazelcast::client;

void task_1(std::shared_ptr<imap>& map) {
    for(int i = 0; i < 1000; i++) {
        map->put<int, int>(i, i);
    }
}

int main() {
    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("some_map").get();

    task_1(map);
    return 0;
}