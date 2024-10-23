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
        while (getline(inFile, line)) {
            int val1, val2 = 0;
            string name_spy = "";
            //cout << "Прочитана строка: " "\"" << line << "\"" << endl;   
            if (stringstream(line) >> name_spy >> val1 >> val2) {
                cout << "Имя шпиона: " << name_spy << "; Время наблюдения: " << val1 << "; Время нахождения в очереди: " << val2 << endl << endl;
                queueSpy.addToQueue(val1, val2, name_spy);
            }
            else { 
                cerr << "Строка " "\"" << line << "\"" " неправильно введена.\n";
                cout << "Пример правильного ввода: Шпион 30 50\n\n";
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
