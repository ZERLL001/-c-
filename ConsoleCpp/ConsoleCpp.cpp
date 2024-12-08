#include <iostream>
#include <windows.h>
#include <thread>
#include <atomic>

std::atomic<bool> running(false);
std::atomic<int> cps(10);

void Clicker() {
    while (true) {
        if (running) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / cps));
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void ToggleClicker() {
    while (true) {
        if (GetAsyncKeyState('Z') & 0x8000) {
            running = !running;
            std::cout << (running ? "Кликер включен" : "Кликер выключен") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ShowMenu() {
    while (true) {
        system("cls");
        std::cout << "=== Меню кликера ===" << std::endl;
        std::cout << "1. Старт" << std::endl;
        std::cout << "2. Настройка CPS (текущее значение: " << cps << ")" << std::endl;
        std::cout << "3. Выход" << std::endl;
        std::cout << "Выберите опцию: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Кликер запущен. Нажмите 'Z' для включения/выключения." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        case 2:
            int new_cps;
            std::cout << "Введите новое значение CPS (1-20): ";
            std::cin >> new_cps;
            if (new_cps >= 1 && new_cps <= 20) {
                cps = new_cps;
                std::cout << "CPS установлен на " << cps << std::endl;
            }
            else {
                std::cout << "Неверное значение. CPS должно быть от 1 до 20." << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        case 3:
            std::cout << "Выход из программы..." << std::endl;
            exit(0);
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::thread clicker_thread(Clicker);
    std::thread toggle_thread(ToggleClicker);
    ShowMenu();

    return 0;
}