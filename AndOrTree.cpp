#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct Tree {
    int level;
    Tree* fath;
    Tree* left_child; 
    Tree* right_child;
    char data;
    Tree(char data = ' ') : data(data), fath(nullptr), left_child(nullptr), right_child(nullptr), level(0) {};
};

class LogicTree {
private:
    Tree* root;
    const set<char> logicOperations = {'*', '+'};
    int addElementToTree(Tree*& operation, char ch) {
        if (logicOperations.find(ch) != logicOperations.end()) {
            Tree* NewElement = new Tree(ch);
            if (!root) {
                operation = NewElement;
                root = operation;
                operation->level = 1;
            }
            else if (!operation->right_child) {
                operation->right_child = NewElement;
                NewElement->fath = operation;
                NewElement->level = ++operation->level;
                operation = operation->right_child;
            }
            else if (!operation->left_child) {
                operation->left_child = NewElement;
                NewElement->fath = operation;
                NewElement->level = ++operation->level;
                operation = operation->left_child;
            }
            return 1;
        }
        else if (operation) {
            Tree* NewElement = new Tree(ch);
            if (!operation->right_child) {
                operation->right_child = NewElement;
                NewElement->fath = operation;
                NewElement->level = 0;
            }
            else if (!operation->left_child) {
                operation->left_child = NewElement;
                NewElement->fath = operation;
                NewElement->level = 0;
                return 0;
            }
            return 2;
        } else {
            return 3;
        }
    }
public:
    LogicTree() : root(nullptr) {}; 

    int makeLogicTree(vector<char> temp_vector) {
        stack<Tree*> stackOfLogicOperations;
        Tree* operation = nullptr;
        int size_tree = 0;
        for (auto it = temp_vector.end(); it != temp_vector.begin();) {
            --it;
            if (!stackOfLogicOperations.empty()) {
                operation = stackOfLogicOperations.top();
            } else if (root){
                return 1;       
            }
            int push_pop_operation = addElementToTree(operation, *it);
            if (push_pop_operation == 1) {
                size_tree++;
                stackOfLogicOperations.push(operation);
            } else if (push_pop_operation == 0) {
                stackOfLogicOperations.pop();
            } else if (push_pop_operation == 3) {
                return 1;
            }
        }
        root->level = size_tree;
        return 0;
    }
    void drawBranches(int shift) {
        for (int i) {

        }
    }
    void printLogicTree() {
        int num_spaces = root->level * root->level;
        string spaces(num_spaces, ' ');
        cout << spaces << root->data;
        drawBranches(root->level);

    }
};

bool leaveProgram() {
   cout << "\n" "Чтобы продолжить нажмите любую клавишу. (Для выхода нажмите Esc).\n\n";
   int key = _getch();
   if (key == 27) {
       cout << "Завершение программы...";
       return true;
   }
}



int main() {
    setlocale(LC_ALL, "RU.UTF8");
    while (true) {
        LogicTree logicTree;
        cout << "Введите название файла: ";
        string nameFile;
        cin >> nameFile;
        ifstream inFile(nameFile);
        if (!inFile) {
            cerr << "Файл с названием " << nameFile << " не найден." << endl;
        } else {
            char ch = ' ';
            vector<char> logicalExpression;
            while (inFile.get(ch)) {
                logicalExpression.push_back(ch);
            }
            inFile.close();
            int result = logicTree.makeLogicTree(logicalExpression);
            if (result == 0) {
                cout << "Дерево заполнилось полностью. \n";
            } else {
                cout << "Не все символы вошли в структуру дерева: проверьте входные данные на наличие ошибок. \n";
            } 
            logicTree.printLogicTree();
        }  
        if (leaveProgram()) {
            return 0;
        }
    }
}
/*if (result == root && result != nullptr) {
                result->right_child = addElementToTree(*it);
                if (logicOperations.find(*it) != logicOperations.end()) { // проверяем является зн-е итератора операцией, поиском в сете
                    result = result->right_child;
                }
            } else if(root && result->right_child == nullptr) {
                result->right_child == addElementToTree(*it);
            }
            else if(result->right_child != nullptr) {
                result->left_child == addElementToTree(*it);
                if (logicOperations.find(*it) != logicOperations.end()) { // проверяем является зн-е итератора операцией, поиском в сете
                    result = result->left_child;
                }
            }
            else if (root == nullptr) {
                root, result = addElementToTree(*it);
            }
            */