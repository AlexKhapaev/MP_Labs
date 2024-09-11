#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx1;
std::mutex mtx2;

void printMessage() {
    for (int i = 0; i < 10; ++i) {
        mtx2.lock(); // ������� ������� ������� ��������
        std::cout << "child stream" << std::endl;
        mtx1.unlock(); // ������������� ������� ��������
    }
}

int main() {
    mtx1.lock(); // ���������� ��������� ������ �������

    std::thread t(printMessage);

    for (int i = 0; i < 10; ++i) {
        mtx1.lock(); // ������� ������� ������� ��������
        std::cout << "maternity stream" << std::endl;
        mtx2.unlock(); // ������������� ������� ��������
    }

    t.join();
    return 0;
}
