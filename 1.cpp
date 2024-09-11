#include <iostream>
#include <thread>

void printMessage() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "child stream" << std::endl;
    }
}

int main() {
    std::thread t(printMessage);
    for (int i = 0; i < 10; ++i) {
        std::cout << "maternity stream" << std::endl;
    }
    t.join();
    return 0;
}
