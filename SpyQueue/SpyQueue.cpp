/*15. У множества шпионов,  собравшихся вместе для наблюдения
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
#include <SpyQueueProcessing.h>

using namespace std;


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
            cout << "Прочитана строка: " "\"" << line << "\"" << endl;
            if (stringstream(line) >> val1 >> val2) {
                queueSpy.addToQueue(val1, val2, count++);
            }
            else { 
                cerr << "Строка " "\"" << line << "\"" " неправильно введена.\n";
                cout << "Пример правильного ввода: 30 50\n\n";
            }
        }
        cout << "\n";
        inFile.close();
        queueSpy.makeProtocol();
        cout << "\n" "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc).\n\n";
        int key = _getch();
        if (key == 27) {
            cout << "Завершение программы...";
            return 0;
        }
    }
    return 0;
}
