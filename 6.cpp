#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool parentTurn = true; // ����, �����������, ��� ��� �������� ���������

void printMessage() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !parentTurn; }); // ����, ���� �� ������ ������� ��������� ������
        std::cout << "child stream" << std::endl;
        parentTurn = true; // ������������� ������� ������������� ������
        cv.notify_one(); // ���������� ������������ �����
    }
}

int main() {
    std::thread t(printMessage);

    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return parentTurn; }); // ����, ���� �� ������ ������� ������������� ������
        std::cout << "maternity stream" << std::endl;
        parentTurn = false; // ������������� ������� ��������� ������
        cv.notify_one(); // ���������� �������� �����
    }

    t.join();
    return 0;
}
