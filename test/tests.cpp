// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

// Тест проверки включения автомата
TEST(TEST1, TurnOn) {
    Automata automata;
    automata.on();
    EXPECT_EQ(States::WAIT, automata.getState());
}

// Тест проверки добавления монеты
TEST(TEST2, AddCoin) {
    Automata automata;
    automata.on();
    automata.coin(250);
    automata.coin(300);
    EXPECT_EQ(States::ACCEPT, automata.getState());
}

// Тест проверки выбора напитка
TEST(TEST3, ChooseDrink) {
    Automata automata;
    automata.on();
    automata.coin(250);
    automata.coin(300);
    automata.choice(3);
    EXPECT_EQ(States::ACCEPT, automata.getState());
}

// Тест проверки состояния после проверки и приготовления напитка
TEST(TEST4, CheckAndCook) {
    Automata automata;
    automata.on();
    automata.coin(250);
    automata.coin(300);
    automata.choice(3);
    automata.check();
    EXPECT_EQ(States::COOK, automata.getState());
}

// Тест проверки остатка на счету после приготовления напитка
TEST(TEST5, GetBalanceAfterCooking) {
    Automata automata;
    automata.on();
    automata.coin(800);
    automata.choice(5);
    automata.check();
    automata.cook();
    EXPECT_EQ(300, automata.getBalance());
}

// Тест проверки выключения автомата
TEST(TEST6, TurnOff) {
    Automata automata;
    automata.on();
    automata.coin(800);
    automata.choice(5);
    automata.check();
    automata.cook();
    automata.finish();
    automata.off();
    EXPECT_EQ(States::OFF, automata.getState());
}
