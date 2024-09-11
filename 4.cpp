#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> stopThread(false);

void printMessage() {
    while (!stopThread) {
        std::cout << "Hello!" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread t(printMessage);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    stopThread = true; // Прерывание потока
    t.join();
    return 0;
}
