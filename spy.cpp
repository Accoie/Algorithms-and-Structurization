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
Среда выполнения: VScode (компилятор g++)
Источники: */

#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <conio.h>
#include <sstream>

using namespace std;

struct Spy{
	int specTime, queueTime; // время наблюдения, время ожидания
	Spy* Next;
	Spy(int specTime = 0, int queueTime = 0) // конструктор: инициализируем члены класса
		: specTime(specTime), queueTime(queueTime), Next(nullptr) {	
	}
};

class QueueSpy{
private:
	Spy* first;
	Spy* last;

public:
	QueueSpy(): first(nullptr), last(nullptr){}
	void addSpy(int val1, int val2)
	{
		Spy* newSpy = new Spy(val1, val2);
		if (last){
			last -> Next = newSpy;
		} else {
			if (!first){
				first = newSpy;
			}
		}
		last = newSpy;
	}
};

int main()
{
	string nameFile, line;
	setlocale(LC_ALL, "RU.UTF8");
	QueueSpy queueSpy;
	while(true){
		cout << "Введите название файла: ";
		cin >> nameFile;
		ifstream inFile(nameFile);
		if (!inFile) {
			cerr << "Файл с названием " << nameFile << " не найден" << endl;
		}
		while (getline(inFile, line)) {
		 	int val1, val2;
			stringstream(line) >> val1 >> val2;
			queueSpy.addSpy(val1, val2);
		}
		cout << "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc)" << endl;
		int key = _getch();
		if (key == 27) {
			cout << "Завершение программы...";
			break;
		} 
	}

	return 0;
}
