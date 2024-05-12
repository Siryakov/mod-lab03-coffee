#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK,
    FINISH
};

struct Drink {
    std::string name;
    int price;

    Drink(const std::string& _name, int _price) : name(_name), price(_price) {}
};

class Automata {
private:
    int cash;
    std::vector<Drink> menu ;
    std::vector<int> prices;
    STATES state;

public:
    Automata();
    void on(); //включение автомата;
    void off(); //выключение автомата;
    void coin(int amount); //занесение денег на счёт пользователем;
    void getMenu(); //считывание меню с напитками и ценами для пользователя;
    void getState(); //считывание текущего состояния для пользователя;
    bool choice(int option); //выбор напитка пользователем;
    bool check(int option); //проверка наличия необходимой суммы;
    void cancel(); //отмена сеанса обслуживания пользователем;
    void cook(int option); //имитация процесса приготовления напитка;
    void finish(); //завершение обслуживания пользователя.
    void error(const std::string& message); 

    void getBalance() const;
};


