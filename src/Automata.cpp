// Copyright 2024 Siryakov
#include "Automata.h"

Automata::Automata() {
    cash = 0;
    state = OFF;
    menu = { {"Вода", 50},
             {"Капучино", 100},
             {"Чай", 80},
             {"Латте", 150},
             {"Мокачино", 200},
             {"Горячий шоколад", 180} };
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
    if (state != OFF) {
        cash += amount;
        state = ACCEPT;
        getState();
        std::cout << "Добавлено " << amount
            << " р. Всего: "
            << cash
            << " р."
            << std::endl;
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
        std::cout << i + 1
            << ". "
            << menu[i].name
            << " - "
            << menu[i].price
            << " р." << std::endl;
    }
}

STATES Automata::getState() {
    switch (state) {
    case OFF:
        return OFF;
    case WAIT:
        return WAIT;
    case ACCEPT:
        return ACCEPT;
    case CHECK:
        return CHECK;
    case COOK:
        return COOK;
    default:
        return WAIT;
    }
}

bool Automata::choice(int option) {
    if (state == ACCEPT) {
        if (option >= 0 && option < menu.size()) {
            state = CHECK;
            getState();
            if (check(option)) {
                cash -= menu[option].price;
                cook(option);
                finish();
                std::cout << "Остаток на счету: " << cash << " р." << std::endl;
                return true;
            }
            else {
                std::cout << "Недостаточно денег для этого напитка."
                    << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Неверный выбор." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Выбор напитка невозможен в данный момент." << std::endl;
        return false;
    }
}

bool Automata::check(int option) {
    if (state == CHECK) {
        if (option >= 0 && option < menu.size()) {
            if (cash >= menu[option].price) {
                return true;
            }
            else {
                std::cout << "Недостаточно денег для этого напитка."
                    << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Неверный выбор." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Проверка невозможна в данный момент." << std::endl;
        return false;
    }
}

void Automata::cancel() {
    if (state != OFF) {
        state = WAIT;
        getState();
        std::cout << "Заказ отменен." << std::endl;
    }
    else {
        error("Отмена заказа невозможна в данный момент.");
    }
}

void Automata::cook(int option) {
    if (state == CHECK) {
        state = COOK;
        getState();
        std::cout << "Приготовление напитка: "
            << menu[option].name << std::endl;
        std::cout << "Пожалуйста, подождите..." << std::endl;
    }
    else {
        error("Приготовление напитка невозможно в данный момент.");
    }
}

void Automata::finish() {
    if (state == COOK) {
        state = WAIT;
        getState();
        std::cout << "Обслуживание завершено." << std::endl;
    }
    else {
        error("Завершение обслуживания невозможно в данный момент.");
    }
}

void Automata::error(const std::string& message) {
    std::cerr << "Ошибка: " << message << std::endl;
}

int Automata::getBalance() const { // Изменено: теперь возвращает int
    return cash;
}
