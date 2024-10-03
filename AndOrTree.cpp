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
public:
    LogicTree() : root(nullptr) {};

    Tree* addElemToTree(char ch) {
        Tree* NewElem = new Tree(ch);
        return NewElem;
    }

    void makeLogicTree(vector<char> temp_vector) {
        Tree* node = nullptr;
        stack<Tree*> stackOfLogicOperations;
        for (auto it = temp_vector.end(); it != temp_vector.begin();) {
            bool success = true;
            node = addElemToTree(*it);
            if (logicOperations.find(*it) != logicOperations.end()) { // check is our char operation
                node = stackOfLogicOperations.top();
                if (root == nullptr) {
                    root = node;
                    node->level = 1;
                } else if (!node->right_child) {

                } else if (!node->left_child) {

                } else {
                    stackOfLogicOperations.pop();
                    success = false;
                }
                // добавляем в дерево
            } else { // block for operands
                if(!stackOfLogicOperations.empty()){
                    node = stackOfLogicOperations.top();
                    if (node->right_child == nullptr) {
                        
                    } else if(node->left_child == nullptr){

                    }
                }
                
            }
            if (success) {
                it--;
            }
        }
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
            logicTree.makeLogicTree(logicalExpression);
            
        }  
        if (leaveProgram()) {
            return 0;
        }
    }
    return 0;
}
/*if (result == root && result != nullptr) {
                result->right_child = addElemToTree(*it);
                if (logicOperations.find(*it) != logicOperations.end()) { // проверяем является зн-е итератора операцией, поиском в сете
                    result = result->right_child;
                }
            } else if(root && result->right_child == nullptr) {
                result->right_child == addElemToTree(*it);
            }
            else if(result->right_child != nullptr) {
                result->left_child == addElemToTree(*it);
                if (logicOperations.find(*it) != logicOperations.end()) { // проверяем является зн-е итератора операцией, поиском в сете
                    result = result->left_child;
                }
            }
            else if (root == nullptr) {
                root, result = addElemToTree(*it);
            }
            */