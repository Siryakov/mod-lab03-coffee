// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

// Тест проверки включения автомата
TEST(TEST1, TurnOn) {
    Automata automata;
    automata.on();
    EXPECT_EQ(STATES::WAIT, automata.getState());
}

// Тест проверки добавления монеты
TEST(TEST2, AddCoin) {
    Automata automata;
    automata.on();
    automata.coin(250);
    automata.coin(300);
    EXPECT_EQ(STATES::ACCEPT, automata.getState());
}

// Тест проверки выбора напитка
TEST(TEST3, ChooseDrink) {
    Automata automata;
    automata.on();
    automata.coin(250);
    automata.coin(300);
    automata.choice(3);
    EXPECT_EQ(STATES::ACCEPT, automata.getState()); 
}

// Тест проверки состояния после проверки и приготовления напитка
TEST(TEST4, CheckAndCook) {
    Automata automata;
    automata.on();
    automata.coin(250);
    automata.coin(300);
    automata.choice(3);
    automata.check(3);
    automata.cook(3);
    EXPECT_EQ(STATES::COOK, automata.getState()); 
}

// Тест проверки остатка на счету после приготовления напитка
TEST(TEST5, GetBalanceAfterCooking) {
    Automata automata;
    automata.on();
    automata.coin(800);
    automata.choice(5);
    automata.check(5);
    automata.cook(5);
    automata.finish(); 
    EXPECT_EQ(300, automata.getBalance());
}

// Тест проверки отмены заказа
TEST(TEST6, CancelOrder) {
    Automata automata;
    automata.on();
    automata.coin(800);
    automata.choice(5);
    automata.cancel();
    EXPECT_EQ(STATES::WAIT, automata.getState());
}

// Тест проверки приготовления напитка
TEST(TEST7, CookDrink) {
    Automata automata;
    automata.on();
    automata.coin(800);
    automata.choice(5);
    automata.check(5);
    automata.cook(5);
    EXPECT_EQ(STATES::WAIT, automata.getState());
}

// Тест проверки выключения автомата после завершения обслуживания
TEST(TEST8, TurnOffAfterService) {
    Automata automata;
    automata.on();
    automata.coin(800);
    automata.choice(5);
    automata.check(5);
    automata.cook(5);
    automata.finish();
    automata.off();
    EXPECT_EQ(STATES::OFF, automata.getState());
}

// Тест проверки отмены заказа без предварительного внесения денег
TEST(TEST9, CancelWithoutPayment) {
    Automata automata;
    automata.on();
    automata.cancel();
    EXPECT_EQ(STATES::WAIT, automata.getState());
}

// Тест проверки выбора напитка без предварительного внесения денег
TEST(TEST10, ChooseDrinkWithoutPayment) {
    Automata automata;
    automata.on();
    automata.choice(3);
    EXPECT_EQ(0, automata.getBalance());
}
