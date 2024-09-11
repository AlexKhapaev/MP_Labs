#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool parentTurn = true; // Флаг, указывающий, чей ход выводить сообщение

void printMessage() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !parentTurn; }); // Ждем, пока не станет очередь дочернего потока
        std::cout << "child stream" << std::endl;
        parentTurn = true; // Устанавливаем очередь родительского потока
        cv.notify_one(); // Уведомляем родительский поток
    }
}

int main() {
    std::thread t(printMessage);

    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return parentTurn; }); // Ждем, пока не станет очередь родительского потока
        std::cout << "maternity stream" << std::endl;
        parentTurn = false; // Устанавливаем очередь дочернего потока
        cv.notify_one(); // Уведомляем дочерний поток
    }

    t.join();
    return 0;
}
