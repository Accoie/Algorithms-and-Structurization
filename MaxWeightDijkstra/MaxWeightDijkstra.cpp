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


class Graph {
private:
    std::vector<std::vector<int>> matrixOfWeight;
    std::map<int, std::string> nameOfVertex;
    
public:
    Graph() {
        matrixOfWeight = std::vector<std::vector<int>>();
        nameOfVertex = std::map<int, std::string>();
    }
    void makeVertex(int id, std::string name) {
        nameOfVertex[id] = name;
    }
    void addToMatrixOfValue(int row, int col, int weight) {
        if (row >= matrixOfWeight.size()) {
            matrixOfWeight.resize(row + 1);
        }
        if (col >= matrixOfWeight[row].size()) {
            matrixOfWeight[row].resize(col + 1);
        }
        matrixOfWeight[row][col] = weight;
    }
    void findShortestPath() {

    }
};
bool leaveProgram() {
    std::cout << "\n" "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc).\n\n";
    int key = _getch();
    if (key == 27) {
        std::cout << "Завершение программы...";
        return true;
    }
    return false;
} 
int main() {
    setlocale(LC_ALL, "RU.UTF8");
    while (true) {
        std::ifstream inFile("i1.txt");
        std::string line;
        Graph NewGraph;
        while (getline(inFile, line)) {
            int id = 0;
            std::string name = "";
            std::istringstream(line) >> id >> name;
            NewGraph.makeVertex(id, name);
        }
        inFile.close();
        std::ifstream iFile("i2.txt");
        while (getline(iFile, line)) {
            int first = 0; int second = 0; int weight = 0;
            std::istringstream(line) >> first >> second >> weight;
            NewGraph.addToMatrixOfValue(first, second, weight);
        }
        if (leaveProgram()) {
            return 0;
        }
    }
}