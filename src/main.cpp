// Copyright 2024 siryakov
#include <iostream>
#include "Automata.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Automata coffeeMachine;

    // Включение автомата
    coffeeMachine.on();

    // Добавление монет
    coffeeMachine.coin(50);
    coffeeMachine.coin(100);
    coffeeMachine.coin(200);

    // Получение и отображение полного меню
    coffeeMachine.getMenu();

    // Выбор напитка
    coffeeMachine.choice(2);

    // Получение остатка на счету
    coffeeMachine.getBalance();

    // Отмена заказа
    coffeeMachine.cancel();

    // Выключение автомата
    coffeeMachine.off();

    return 0;
}
