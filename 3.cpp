#include <iostream>
#include <thread>
#include <string>

void printMessage(const std::string& message) {
    for (int i = 0; i < 10; ++i) {
        std::cout << message << std::endl;
    }
}

int main() {
    std::thread t1(printMessage, "1 message");
    std::thread t2(printMessage, "2 message");
    std::thread t3(printMessage, "3 message");
    std::thread t4(printMessage, "4 message");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
