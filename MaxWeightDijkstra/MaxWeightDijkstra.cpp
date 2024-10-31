/*Имеется  сеть  автомобильных  дорог.  Для каждой дороги
известна максимальная масса груза, которую можно  провезти  по 
этой   дороге.   С   помощью  алгоритма  Дейкстры   определить 
максимальный   груз,   который  можно  провезти  между   двумя 
указанными городами. Проиллюстрировать в таблице по шагам этапы
поиска (9)
Студент: Шашкин Максим ПС-24
Источник:
*/
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>


bool leaveProgram() {
    std::cout << "\n" "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc).\n\n";
    int key = _getch();
    if (key == 27) {
        std::cout << "Завершение программы...";
        return true;
    }
    return false;
}
void findMaxWeightPath() {

}
int main() {
    setlocale(LC_ALL, "RU.UTF8");
    while (true) {
        std::ifstream inFile("i1.txt");
        std::string line;
        int id = 0;
        std::string name = "";
        
        std::map<int, std::string> vertex_names;
        while (getline(inFile, line)) {         
            std::istringstream(line) >> id >> name;
            vertex_names[id] = name;
        }
        inFile.close();
        std::ifstream iFile("i2.txt");
        std::vector<std::vector<int>> matrixOfWeight(id + 1, std::vector<int>(id + 1));
        while (getline(iFile, line)) {
            int first = 0; int second = 0; int weight = 0;
            std::istringstream(line) >> first >> second >> weight;
            matrixOfWeight[first][second] = weight;
        }
        findMaxWeightPath();
        if (leaveProgram()) {
            return 0;
        }
    }
}