#include <hazelcast/client/hazelcast.h>
#include <thread>
using namespace hazelcast::client;


void writer_func() {
    auto hz = hazelcast::new_client().get();
    auto que = hz.get_queue("read_write").get();

    for (int i = 0; i < 100; i++) {
        que->put(i).get();
        std::cout << "Writer: put " << i << std::endl;
    }

    que->put(-1).get();
    std::cout << "Writer: put poison pill" << std::endl;

}

void reader_func(int number) {
    auto hz = hazelcast::new_client().get();
    auto que = hz.get_queue("read_write").get();

    while (true) {
        auto value = que->take<int>().get().get();
        std::cout << "Reader number " << number << " read: " << value << std::endl;

        if (value == -1) {
            que->put(-1).get();
            std::cout << "Reader put poison pill. Stop." << std::endl;

            break;
        }
    }

}

int main() {

    std::vector<std::thread> clients;
    clients.emplace_back(writer_func);

    clients.emplace_back(reader_func, 1);
//    clients.emplace_back(reader_func, 2);

    for (auto& client : clients) {
        client.join();
    }

    return 0;
}