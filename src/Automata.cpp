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
    } else {
        error("Автомат уже включен.");
    }
}

void Automata::off() {
    if (state == WAIT) {
        state = OFF;
        getState();
        std::cout << "Автомат выключен." << std::endl;
    } else {
        error("Автомат уже выключен.");
    }
}

void Automata::coin(int amount) {
    if (state == WAIT || state == ACCEPT) {
        cash += amount;
        state = ACCEPT;
        getState();
        std::cout << "Добавлено " << amount << " р. Всего: " << cash << " р." << std::endl;
    } else {
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
            cout << "OFF" << endl;
            break;
        case WAIT:
            cout << "WAIT" << endl;
            break;
        case ACCEPT:
            cout << "ACCEPT" << endl;
            break;
        case CHECK:
            cout << "CHECK" << endl;
            break;
        case COOK:
            cout << "COOK" << endl;
            break;
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
            } else {
                std::cout << "Недостаточно денег для этого напитка." << std::endl;
                return false;
            }
        } else {
            std::cout << "Неверный выбор." << std::endl;
            return false;
        }
    } else {
        std::cout << "Выбор напитка невозможен в данный момент." << std::endl;
        return false;
    }
}

bool Automata::check(int option) {
    if (state == CHECK) {
        if (option >= 0 && option < menu.size()) {
            if (cash >= menu[option].price) {
                return true;
            } else {
                std::cout << "Недостаточно денег для этого напитка." << std::endl;
                return false

