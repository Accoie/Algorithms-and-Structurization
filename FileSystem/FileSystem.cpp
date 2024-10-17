/*17. Информация  о  файлах  на  жестких  дисках   компьютера
записана с помощью дерева. Листьям соответствуют файлы. Удалить
все копии одного и того же файла, оставив самую позднюю.  Если
папка оказывается пустой, то она тоже должна быть удалена (10).

Студент: Шашкин Максим ПС-24
Среда выполнения: Visual Studio
*/


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
    int date;
    string name;
    Tree(string name = "", int date = 0, int level = 0) : name(name), date(date), fath(nullptr),  level(level) {};
};
struct Info {
    int level;
    int date;
    string name;
    Info() : name(""), date(0), level(0) {};
};
class FileSystem {
private:
    vector<Tree*> roots;
    Tree* prev;
    bool isFolder(Tree* element) {
        if (element->date == 0) {
            return true;
        } else {
            return false;
        }
    }
    void clearFileSystem() {

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
   
    void findCopiesOfFile(vector<Tree*> elements) {
        for (Tree* element : elements) {
            if (isFolder(element)) {
                findCopiesOfFile(element->sons);
            } else {

            }
        }
    }

public:
    /*static FileSystem& getInstance() {
        static FileSystem instance;
        return instance;
    }*/
    FileSystem() : roots({}), prev(nullptr) {};
    void addNewElementToTree(string name, int date, int level){
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
            while (ptr->level > new_node->level) {
                ptr = ptr->fath;
            }
            ptr->sons.push_back(new_node);
            new_node->fath = ptr;
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
        findCopiesOfFile(roots);
    }
    void printTree() {
        for (vector<Tree*>::iterator root = roots.begin(); root != roots.end(); ++root) {       
            printSons(*root);
        }
    }
    /*~FileSystem() {
        clearFileSystem();
    }*/
    
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
        }
    }
    istringstream(temp_line) >> element.name >> element.date;
    if (element.date) {
        cout << "Название файла: " << element.name << "\n"
             << "Дата создания: " << element.date << "\n"
             << "Количество папок, в которые вложен файл: " << element.level << "\n";
    } else {
        cout << "Название папки: " << element.name << "\n"
             << "Количество папок, в которые вложена папка: " << element.level << "\n";
    }
    
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
            //FileSystem& infoAboutFiles = FileSystem::getInstance();
            FileSystem infoAboutFiles;
            string line;
            while (getline(inFile, line)) {
                cout << line << "\n";
                Info element = getInfoAboutElementForTree(line);
                infoAboutFiles.addNewElementToTree(element.name, element.date, element.level);
            }
            cout << "\nИсходное дерево файловой системы:\n";
            infoAboutFiles.printTree();
            //infoAboutFiles.processTree();
        }
        if (leaveProgram()) {
            return 0;
        }
    }
}
