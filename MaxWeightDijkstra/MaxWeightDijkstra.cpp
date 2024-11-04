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
    int mark;
    Vertex() : prev_vertex(0), mark(-1) {};
};
int findMaxMark(std::vector<Vertex> marks, std::vector<Vertex> result_marks) {
    int max = marks[0].mark;
    int num = 0;
    for (int i = 1; i != marks.size(); ++i) {
        if (marks[i].mark > max && result_marks[i].mark == -1) {
            max = marks[i].mark;
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
int changeTempMarks(int num_last_result_mark, std::vector<Vertex> result_marks, std::vector<Vertex> &temp_marks, std::vector<std::vector<int>>matrixOfWeight) {
    for (int i = 1; i != matrixOfWeight[num_last_result_mark].size(); ++i) {
        if (i != num_last_result_mark && matrixOfWeight[num_last_result_mark][i] != 0) {
            int M = min(result_marks[num_last_result_mark].mark, matrixOfWeight[num_last_result_mark][i]);
            temp_marks[i].mark = max(M, temp_marks[i].mark);
            M = temp_marks[i].mark ? temp_marks[i].prev_vertex = num_last_result_mark : 0;
        }
    }
    return 0;
}
std::vector<Vertex> findMaxWeight(int path_begin, int path_end, std::vector<std::vector<int>>matrixOfWeight) {
    std::vector<Vertex> temp_marks = {};
    for (int i = 0; i != matrixOfWeight.size(); ++i) {
        temp_marks.push_back({});
        if (i == path_begin) {
            temp_marks[i].mark = INFINITY_INT;
        }
    }
    std::vector<Vertex> result_marks = temp_marks;
    int num_last_result = path_begin;
    int count = 0;
    while (result_marks[path_end].mark == -1) { 
        changeTempMarks(num_last_result, result_marks, temp_marks, matrixOfWeight);
        num_last_result = findMaxMark(temp_marks, result_marks);
        result_marks[num_last_result] = temp_marks[num_last_result];
        std::cout << "Шаг " << ++count << ": ";
        if (result_marks[path_end].mark != -1) {
            result_marks = temp_marks;
        }
        for (int i = 1; i != temp_marks.size(); ++i) {
            if (result_marks[i].mark != -1) {
                if (result_marks[i].mark == INFINITY_INT) {
                    std::cout << "C[" << i << "] = " << "INF" << " ";
                } else {
                    std::cout << "C[" << i << "] = " << result_marks[i].mark << "(" << result_marks[i].prev_vertex << ")" << "  ";
                }
            } else {
                if (temp_marks[i].mark == -1) {
                    std::cout << "D[" << i << "] = " << temp_marks[i].mark << "  ";
                } else {
                    std::cout << "D[" << i << "] = " << temp_marks[i].mark << "(" << temp_marks[i].prev_vertex << ")" << "  ";
                }
                
            }    
        }
        std::cout << "\n\n";
    }
    result_marks = temp_marks;
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
        std::vector<Vertex> max_weight = findMaxWeight(path_begin, path_end, matrixOfWeight);
        std::cout << "\nМаксимальный груз между городом " << vertex_names[path_begin] << " и " 
                  << vertex_names[path_end] << " = " << max_weight[path_end].mark << "\n\n";
        if (leaveProgram()) {
            return 0;
        }
    }
}