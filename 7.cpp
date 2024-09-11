#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1;
std::mutex mtx2;

void printMessage() {
    for (int i = 0; i < 10; ++i) {
        mtx2.lock(); // Попытка захвата второго мьютекса
        std::cout << "child stream" << std::endl;
        mtx1.unlock(); // Разблокировка первого мьютекса
    }
}

int main() {
    mtx1.lock(); // Изначально блокируем первый мьютекс

    std::thread t(printMessage);

    for (int i = 0; i < 10; ++i) {
        mtx1.lock(); // Попытка захвата первого мьютекса
        std::cout << "maternity stream" << std::endl;
        mtx2.unlock(); // Разблокировка второго мьютекса
    }

    t.join();
    return 0;
}
