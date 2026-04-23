#include "Task2.h"

#include <string>
#include <iostream>

using namespace std;

class CountryCapitalList {
public:
    // Коди помилок
    enum ErrorCode {
        OK = 0,
        NOT_FOUND = 1
    };

private:
    struct Pair {
        string country;
        string capital;
    };

    Pair* data;
    int size;
    int capacity;
    int CodeError;

    void resize() {
        capacity *= 2;
        Pair* newData = new Pair[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    // Конструктор
    CountryCapitalList() : size(0), capacity(10), CodeError(OK) {
        data = new Pair[capacity];
    }

    // Деструктор
    ~CountryCapitalList() {
        delete[] data;
    }

    // Функція створення набору (додавання асоціативних сутностей)
    void add(const string& country, const string& capital) {
        // Якщо країна вже є, оновлюємо столицю
        for (int i = 0; i < size; ++i) {
            if (data[i].country == country) {
                data[i].capital = capital;
                return;
            }
        }
        // Якщо місця немає, розширюємо масив
        if (size >= capacity) {
            resize();
        }
        // Додаємо новий запис
        data[size].country = country;
        data[size].capital = capital;
        size++;
    }

    string& operator[](const string& country) {
        CodeError = OK;
        for (int i = 0; i < size; ++i) {
            if (data[i].country == country) {
                return data[i].capital;
            }
        }

        CodeError = NOT_FOUND;

        static string emptyValue = "";
        emptyValue = "";
        return emptyValue;
    }

    string operator()(const string& country) {
        CodeError = OK;
        for (int i = 0; i < size; ++i) {
            if (data[i].country == country) {
                return data[i].capital;
            }
        }
        CodeError = NOT_FOUND;
        return "";
    }

    int getError() const {
        return CodeError;
    }

    friend ostream& operator<<(ostream& os, const CountryCapitalList& dict) {
        if (dict.size == 0) {
            os << "Empty List." << endl;
            return os;
        }
        os << "--- List (Country - Capital) ---" << endl;
        for (int i = 0; i < dict.size; ++i) {
            os << dict.data[i].country << " - " << dict.data[i].capital << endl;
        }
        return os;
    }

    // Перевантаження дружньої операції введення
    friend istream& operator>>(istream& is, CountryCapitalList& dict) {
        int count;
        cout << "How many entries do you want to add? ";
        if (is >> count) {
            is.ignore(); // Очищуємо буфер після вводу числа
            for (int i = 0; i < count; ++i) {
                std::string country, capital;
                cout << "Input Country name: ";
                getline(is, country);
                cout << "Input Capital name: ";
                getline(is, capital);
                dict.add(country, capital);
            }
        }
        return is;
    }
};

void task2()
{
    CountryCapitalList myDict;

    cout << "ADD VIA add()" << endl;
    myDict.add("Ukraine", "Kyiv");
        myDict.add("Germany", "Berlin");
    myDict.add("United Kingdom", "London");

    cout << myDict << endl;

    cout << "OUTPUT VIA []" << endl;
    cout << "Capital of Ukraine: " << myDict["Ukraine"] << endl;

    cout << "INPUT VIA []" << endl;
    myDict["Ukraine"] = "Kyiv (updated)";
    cout << "Capital after being updated : " << myDict["Ukraine"] << "\n" << endl;

    cout << "OUTPUT VIA ()" << endl;
    cout << "Capital of Germany: " << myDict("Germany") << "\n" << endl;

    cout << "ERROR PROCESSING:" << endl;
    string searchCapital = myDict["France"];
    if (myDict.getError() == CountryCapitalList::NOT_FOUND) {
        cout << "[ERROR] Couldn't find country 'France' " << endl;
    }
}
