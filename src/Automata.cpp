// Copyright 2024 osenvesen
#include "Automata.h"

Automata::Automata() {
    cash = 0;
    state = OFF;
    menu = { {"Вода", 50}, {"Капучино", 100}, {"Чай", 80}, 
        {"Латте", 150}, {"Мокачино", 200}, {"Горячий шоколад", 180} };
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        getState();
        std::cout << "Автомат включен." << std::endl;
    }
    else {
        error("Автомат уже включен.");
    }
}

void Automata::off() {
    if (state == WAIT) {
        state = OFF;
        getState();
        std::cout << "Автомат выключен." << std::endl;
    }
    else {
        error("Автомат уже выключен.");
    }
}

void Automata::coin(int amount) {
    if (state == WAIT || state == ACCEPT) {
        cash += amount;
        state = ACCEPT;
        getState();
        std::cout << "Добавлено " << amount << " р. Всего: " << cash << " р." << std::endl;
    }
    else {
        error("Нельзя добавить монеты в данный момент.");
    }
}

void Automata::getMenu() {
    if (menu.empty()) {
        std::cerr << "Ошибка: Меню пусто." << std::endl;
        return;
    }

    std::cout << "Меню:" << std::endl;
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << i + 1 << ". " << menu[i].name << " - " << menu[i].price << " р." << std::endl;
    }
}

void Automata::getState() {
    switch (state) {
    case OFF:
        std::cout << "OFF" << std::endl;
        break;
    case WAIT:
        std::cout << "WAIT" << std::endl;
        break;
    case ACCEPT:
        std::cout << "ACCEPT" << std::endl;
        break;
    case CHECK:
        std::cout << "CHECK" << std::endl;
        break;
    case COOK:
        std::cout << "COOK" << std::endl;
        break;
    }
}

bool Automata::choice(int option) {
    if (state == ACCEPT) {
        if (option >= 0 && option < menu.size()) {
            state = CHECK;
            getState();
            if (check(option)) {
                cash -= menu[option].price; // вычитаем стоимость напитка из доступных средств
                cook(option);
                finish();
                std::cout << "Остаток на счету: " << cash << " р." << std::endl;
                return true; // Успешно выбран напиток и средств хватает
            }
            else {
                std::cout << "Недостаточно денег для этого напитка." << std::endl;
                return false; // Недостаточно средств
            }
        }
        else {
            std::cout << "Неверный выбор." << std::endl;
            return false; // Неверный выбор напитка
        }
    }
    else {
        std::cout << "Выбор напитка невозможен в данный момент." << std::endl;
        return false; // Невозможно сделать выбор
    }
}

bool Automata::check(int option) {
    if (state == CHECK) {
        if (option >= 0 && option < menu.size()) {
            if (cash >= menu[option].price) {
                return true;
            }
            else {
                std::cout << "Недостаточно денег для этого напитка." << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Неверный выбор." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Проверка наличия средств невозможна в текущем состоянии." << std::endl;
        return false;
    }
}

void Automata::cancel() {
    if (state == ACCEPT || state == CHECK) {
        cash = 0;
        state = WAIT;
        std::cout << "Заказ отменен. Деньги возвращены." << std::endl;
    }
    else {
        std::cout << "Нет заказа для отмены." << std::endl;
    }
}

void Automata::cook(int option) {
    if (state == CHECK) {
        state = COOK;
        getState();
        std::cout << "Приготовление " << menu[option].name << "..." << std::endl;
        // Имитация процесса приготовления
    }
    else {
        std::cout << "Не получается приготовить напиток." << std::endl;
    }
}

void Automata::finish() {
    if (state == COOK) {
        state = WAIT;
        getState();
    }
    else {
        error("неудалось завершить обслуживание");
    }
}

void Automata::error(const std::string& message) {
    std::cerr << "Ошибка: " << message << std::endl;
}

void Automata::getBalance() const {
    std::cout << "Остаток на счету: " << cash << " р." << std::endl;
}