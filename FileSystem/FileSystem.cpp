/*17. Информация  о  файлах  на  жестких  дисках   компьютера
записана с помощью дерева. Листьям соответствуют файлы. Удалить
все копии одного и того же файла, оставив самую позднюю.  Если
папка оказывается пустой, то она тоже должна быть удалена (10).

Студент: Шашкин Максим ПС-24
Среда выполнения: Visual Studio
*/

#include <algorithm>
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <vector>

using namespace std;

struct Tree {
    int level;
    Tree* fath;
    vector<Tree*> sons;
    string date;
    string name;
    Tree(string name = "", string date = "", int level = 0) : name(name), date(date), fath(nullptr), level(level) {};
};
struct Info {
    int level;
    string date;
    string name;
    Info() : name(""), date(""), level(0) {};
};
class FileSystem {
private:
    vector<Tree*> roots;
    Tree* prev;
    bool isFolder(Tree* element) {
        if (element->date == "") {
            return true;
        } else {
            return false;
        }
    }
    void printInfo(Tree* element) {
        for (int i = 0; i < element->level; ++i) {
            cout << '.';
        }
        if (isFolder(element)) {
            cout << element->name << " " << "\n";
        } else {
            cout << element->name << " " << element->date << "\n";
        }
    }
    void printSons(Tree* father) {
        printInfo(father);
        for (Tree* son : father->sons) {
            if (isFolder(son)) {
                printSons(son);
            } else {
                printInfo(son);
            }
        }
    }
    vector<Tree*> findFiles(vector<Tree*> result, vector<Tree*> elements) {
        for (vector<Tree*>::iterator element = elements.begin(); element != elements.end(); ++element) {
            if (isFolder(*element)) {
                result = findFiles(result, (*element)->sons);
            } else {
                result.push_back(*element);
            }
        }
        return result;
    }
    static bool compareByDate(Tree* x, Tree* y) {
        stringstream date = stringstream(x->date);
        int day_x = 0, month_x = 0, year_x = 0;
        int day_y = 0, month_y = 0, year_y = 0;
        char separator = '/';
        date >> day_x >> separator >> month_x >> separator >> year_x;
        date = stringstream(y->date);
        date >> day_y >> separator >> month_y >> separator >> year_y;
        if (year_x != year_y) {
            return year_x > year_y;
        } else if (month_x != month_y) {
            return month_x > month_y;
        } else if (day_x != day_y) {
            return day_x > day_y;
        } else {
            return false;
        }
    }
    static bool compareByDateName(Tree* x, Tree* y) {
        if (x->name != y->name) {
            return x->name < y->name;
        } else {
            return compareByDate(x, y);
        }
    }
    vector<Tree*> filterUniqueFilesMaxDate(vector<Tree*> &elements) { 
        sort(elements.begin(), elements.end(), compareByDateName);
        vector<Tree*>uniqueFiles;
        for (Tree* element : elements) {
            if (uniqueFiles.empty() || element->name != uniqueFiles.back()->name) {
                uniqueFiles.push_back(element);
            }
        }
        return uniqueFiles;
    }
    bool deleteCopiesOfFiles(vector<Tree*> &uniqueFiles, vector<Tree*> &elements) {
        bool flag = false;
        for (int i = 0; i != elements.size();) {
            cout << elements[i]->level << " " << elements[i]->name << "" << elements[i]->date << endl;
            if (isFolder(elements[i])) {
                bool result = deleteCopiesOfFiles(uniqueFiles, elements[i]->sons);
                auto it = find(roots.begin(), roots.end(), elements[i]);
                if (result && elements[i]->sons.empty() && it == roots.end()) {
                    delete elements[i];
                    elements.erase(elements.begin() + i);
                    flag = true;
                } else {
                    ++i;
                }  
            } else {
                auto it = find(uniqueFiles.begin(), uniqueFiles.end(), elements[i]);
                if (it == uniqueFiles.end()) {
                    delete elements[i];
                    elements.erase(elements.begin() + i);
                    flag = true;
                } else {
                    uniqueFiles.erase(it);
                    ++i;
                }
            }
        }
        return flag;
    }
public:
    FileSystem() : roots({}), prev(nullptr) {};
    void addNewElementToTree(string name, string date, int level){
        Tree* new_node = new Tree(name, date, level);
        if (new_node->level == 0) {
            roots.push_back(new_node);
            prev = new_node;
        } else if (new_node->level == prev->level) {
            new_node->fath = prev->fath;
            prev->fath->sons.push_back(new_node);
            prev = new_node;
        } else if (new_node->level < prev->level) {
            Tree* ptr = prev->fath;
            while (ptr->level >= new_node->level) {
                ptr = ptr->fath;
            }
            ptr->sons.push_back(new_node);
            new_node->fath = ptr;
            prev = new_node;
        } else if (new_node->level > prev->level && isFolder(prev)) {
            if (prev == roots.back()) {
                prev->sons.push_back(new_node);
                new_node->fath = prev;
                prev = new_node;
                return;
            } else {
                prev->sons.push_back(new_node);
                new_node->fath = prev;
                prev = new_node;
            }
        } else {
            cerr << "\nОшибка добавления элемента в дерево. Проверьте правильность входных данных \n\n";
        }
    }
    void processTree() {
        vector<Tree*> result = {};
        vector<Tree*> files = findFiles(result, roots);
        vector<Tree*> uniqueFiles = filterUniqueFilesMaxDate(files);
        deleteCopiesOfFiles(uniqueFiles, roots);
    }
    void printTree() {
        for (vector<Tree*>::iterator root = roots.begin(); root != roots.end(); ++root) {       
            printSons(*root);
        }
    }
    ~FileSystem() {
    }
    
};

bool leaveProgram() {
    cout << "\n" "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc).\n\n";
    int key = _getch();
    if (key == 27) {
        cout << "Завершение программы...";
        return true;
    }
    return false;
}

Info getInfoAboutElementForTree(string line) {
    string temp_line = "";
    bool is_char_readed = false;
    Info element;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '.' && !is_char_readed) {
            element.level++;
        } else {
          temp_line += line[i];
          is_char_readed = true;
        }
    }
    istringstream(temp_line) >> element.name >> element.date; 
    return element;
}

int main() {
    setlocale(LC_ALL, "RU.UTF8");
    while (true) { 
        cout << "Введите название файла: ";
        string nameFile;
        cin >> nameFile;
        ifstream inFile(nameFile);
        if (!inFile) {
            cerr << "Файл с названием " << nameFile << " не найден." << endl;
        }
        else {
            FileSystem infoAboutFiles;
            string line;
            while (getline(inFile, line)) {
                Info element = getInfoAboutElementForTree(line);
                infoAboutFiles.addNewElementToTree(element.name, element.date, element.level);
            }
            cout << "\nИсходное дерево файловой системы:\n";
            infoAboutFiles.printTree();
            infoAboutFiles.processTree();
            cout << "\nДерево после удаления копий файлов и пустых папок:\n";
            infoAboutFiles.printTree();
        }
        if (leaveProgram()) {
            return 0;
        }
    }
}
