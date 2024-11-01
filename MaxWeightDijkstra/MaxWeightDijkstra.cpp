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
#include <limits>

const int INFINITY_INT = std::numeric_limits<int>::max();

bool leaveProgram() {
    std::cout << "\n" "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc).\n\n";
    int key = _getch();
    if (key == 27) {
        std::cout << "Завершение программы...";
        return true;
    }
    return false;
}
struct Vertex {
    int prev_vertex;
    int temp_mark;
    Vertex() : prev_vertex(0), temp_mark(-1) {};
};
int findMaxMark(std::vector<Vertex> marks, std::vector<Vertex> result_marks) {
    int max = marks[0].temp_mark;
    int num = 0;
    for (int i = 1; i != marks.size(); ++i) {
        if (marks[i].temp_mark > max && result_marks[i].temp_mark == -1) {
            max = marks[i].temp_mark;
            num = i;
        }
    }
    return num;
}
int min(int a, int b) {
    return a < b ? a : b;
}
int max(int a, int b) {
    return a > b ? a : b;
}
int changeTempMarks(int num_last_result_mark, std::vector<Vertex> result_marks, std::vector<Vertex>& temp_marks, std::vector<std::vector<int>>matrixOfWeight) {
    for (int i = 1; i != matrixOfWeight[num_last_result_mark].size(); ++i) {
        int M = min(result_marks[num_last_result_mark].temp_mark, matrixOfWeight[num_last_result_mark][i]);
        int D = max(M, temp_marks[i].temp_mark);
        M > temp_marks[i].temp_mark ? temp_marks[i].prev_vertex = i : 0;
    }
}
std::vector<Vertex> findMaxWeight(int path_begin, int path_end, std::vector<std::vector<int>>matrixOfWeight) {
    std::vector<Vertex> temp_marks = {};
    for (int i = 0; i != matrixOfWeight.size(); ++i) {
        temp_marks.push_back({});
        if (i == path_begin) {
            temp_marks[i].temp_mark = INFINITY_INT;
        }
    }
    std::vector<Vertex> result_marks = temp_marks;
    int num_last_result_mark = path_begin;
    while (result_marks[path_end].temp_mark == -1) {
        if (num_last_result_mark == path_begin) {
            changeTempMarks(num_last_result_mark, result_marks, temp_marks, matrixOfWeight);
        } else {
            num_last_result_mark = findMaxMark(temp_marks, result_marks);
            result_marks[num_last_result_mark] = temp_marks[num_last_result_mark];
        }
        
        result_marks[num_last_result_mark].temp_mark;
    }
    return result_marks;
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
        inFile.open("i2.txt");
        std::vector<std::vector<int>> matrixOfWeight(id + 1, std::vector<int>(id + 1));
        while (getline(inFile, line)) {
            int first = 0; int second = 0; int weight = 0;
            std::istringstream(line) >> first >> second >> weight;
            matrixOfWeight[first][second] = weight;
        }
        std::cout << "Введите начальную и конечную вершину. Максимальная вершина: " << id << std::endl;
        int path_begin, path_end;
        std::cin >> path_begin >> path_end;
        findMaxWeight(path_begin, path_end, matrixOfWeight);
        if (leaveProgram()) {
            return 0;
        }
    }
}