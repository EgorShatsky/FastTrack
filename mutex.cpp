#include <iostream>
#include <thread>
#include <chrono>
#include <shared_mutex>

std::shared_mutex mtx;
int sharedData = 0;

void Read() {
    while (true) {
        mtx.lock_shared();
        std::cout << "Reader read data: " << sharedData << std::endl;
        mtx.unlock_shared();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Write() {
    while (true) {
        mtx.lock();
        sharedData++;
        std::cout << "Writer wrote data: " << sharedData << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread reader(Read);
    std::thread writer(Write);

    reader.join();
    writer.join();
}
