﻿/*15. У множества шпионов,  собравшихся вместе для наблюдения
секретного     объекта,    имеется    единственный    бинокль.
Сформировалась очередь на этот  бинокль.  Для  каждого  шпиона
задан   период   наблюдения   в  минутах  и  предельное  время
нахождения в очереди. После наблюдения каждый шпион становится
снова  в  конец  очереди.  Как  только  для какого-либо шпиона
истекает предельное время нахождения в очереди, он покидает ее
(даже  если  в  этот момент владеет биноклем) и отправляется к
резиденту. Вывести протокол наблюдения шпионов за объектом(9).

Студент: Шашкин Максим ПС-24
Среда выполнения: Visual Studio
Источники: */

#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>

using namespace std;

struct Spy {
    int spec_time, queue_time, number;
    Spy* next;
    Spy(int spec_time = 0, int queue_time = 0, int number = 0) 
        : spec_time(spec_time), queue_time(queue_time), number(number), next(nullptr) {
    }
};

class QueueSpy {
private:
    Spy* first;
    Spy* last;

public:
    QueueSpy() : first(nullptr), last(nullptr) {}
    void addToQueue(int val1, int val2, int number)
    {
        Spy* newSpy = new Spy(val1, val2, number);
        if (last) {
            last->next = newSpy;
        }        		
        else {
            if (!first) {
                first = newSpy;	
            }
        }
        last = newSpy;
    }
    void makeProtocol() {
        int сurr_time = 0;
        while (first != nullptr)
        {
            if (first->queue_time - сurr_time >= 0) {
                сurr_time += first->spec_time;
                first->queue_time += first->spec_time;
                if (first != nullptr) {
                    if (first != last) {
                        cout << "Шпион #" << first->number << " понаблюдал за объектом "<< first->spec_time << " минут.\n";
                        last->next = first;
                        last = first;
                        first = first->next;
                        last->next = nullptr;
                    }
                    else {
                        cout << "Шпион #" << first->number << " понаблюдал за объектом " << first->spec_time << " минут.\n";
                        delete first;
                        first = nullptr;
                        last = nullptr;
                        return;
                    }
                }
            }
            else if (first != last) {
                cout << "Шпион #" << first->number << " ушел к резиденту.\n";
                Spy* temp = first;
                first = first->next;
                delete temp;
            } else {
                cout << "Шпион #" << first->number << " ушел к резиденту.\n";
                delete first;
                first = nullptr;
                last = nullptr;
                return;
            }
        }
    }
};

int main()
{
    string nameFile, line;
    setlocale(LC_ALL, "RU.UTF8");
    QueueSpy queueSpy;
    while (true) {
        cout << "Введите название файла: ";
        cin >> nameFile;
        ifstream inFile(nameFile);
        if (!inFile) {
            cerr << "Файл с названием " << nameFile << " не найден." << endl;
        }
        int count = 1;
        while (getline(inFile, line)) {
            int val1, val2 = 1;
            if (stringstream(line) >> val1 >> val2) {
                queueSpy.addToQueue(val1, val2, count++);
            }
            else { 
                cerr << "Строка " "\"" << line << "\"" << " неправильно введена." << endl;
                cout << "Пример правильного ввода: 30 50\n";
            }
        }
        inFile.close();
        queueSpy.makeProtocol();
        cout << "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc)." << endl;
        int key = _getch();
        if (key == 27) {
            cout << "Завершение программы...";
            return 0;
        }
    }
    return 0;
}
