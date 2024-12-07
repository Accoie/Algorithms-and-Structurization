/*22. Составить   программу  поиска  записи  с  включением  в 
сильно ветвящемся  Б-дереве  порядка N.  Б-дерево  хранится  и
обрабатывается в оперативной памяти (12).
Студент: Шашкин Максим ПС-24

*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <Windows.h>
#include <fstream>
#undef min
#undef max 

const int TREE_DEGREE = 2;

struct Key {
    int key;
    std::string value;
    Key(int key = 0, std::string value = "") : key(key), value(value) {}
};

struct Node {
    std::vector<Key> keys;
    std::vector<std::shared_ptr<Node>> child; // Changed from std::list to std::vector
    std::shared_ptr<Node> parent;
    bool is_leaf;
    Node(std::vector<Key> keys = {}, std::vector<std::shared_ptr<Node>> child = {}, bool is_leaf = true, std::shared_ptr<Node> parent = nullptr)
        : keys(keys), child(child), is_leaf(is_leaf), parent(parent) {}
};

bool compareByKeys(Key x, Key y) {
    return x.key < y.key;
}

std::shared_ptr<Node> insertKeyIntoKeys(std::shared_ptr<Node> node, Key key) {
    node->keys.push_back(key);
    std::sort(node->keys.begin(), node->keys.end(), compareByKeys);
    return node;
}

std::shared_ptr<Node> splitNode(std::shared_ptr<Node> node, Key key) {
    if (!node->parent) {
        node = insertKeyIntoKeys(node, key);
        Key parent_key = node->keys[TREE_DEGREE];
        node->keys.erase(node->keys.begin() + TREE_DEGREE);

        std::shared_ptr<Node> less_node = std::make_shared<Node>(std::vector<Key>(), std::vector<std::shared_ptr<Node>>(), true, node);
        std::shared_ptr<Node> more_node = std::make_shared<Node>(std::vector<Key>(), std::vector<std::shared_ptr<Node>>(), true, node);
       
        for (const Key& k : node->keys) {
            if (k.key < parent_key.key) less_node->keys.push_back(k);
            else more_node->keys.push_back(k);
        }
        if (!node->child.empty()) {
            less_node->is_leaf = false;
            more_node->is_leaf = false;
            for (int i = 0; i != node->child.size(); ++i) {
                if (i < less_node->keys.size() + 1) {
                    less_node->child.push_back(node->child[i]);
                    node->child[i]->parent = less_node;
                } else {
                    more_node->child.push_back(node->child[i]);
                    node->child[i]->parent = more_node;
                }
            }
        }
        node->keys = { parent_key };
        node->child = { less_node, more_node };
        node->is_leaf = false;

    } else {
        node = insertKeyIntoKeys(node, key);
        Key parent_key = node->keys[TREE_DEGREE];
        node->keys.erase(node->keys.begin() + TREE_DEGREE);

        std::shared_ptr<Node> more_node = std::make_shared<Node>(std::vector<Key>(), std::vector<std::shared_ptr<Node>>(), true, node->parent);
        std::vector<Key> temp_keys = node->keys;
 

        node->keys.clear();
        

        for (const Key& k : temp_keys) {
            if (k.key < parent_key.key) node->keys.push_back(k);
            else more_node->keys.push_back(k);
        }
        if (!node->child.empty()) {         
            more_node->is_leaf = false;
            std::shared_ptr<Node> temp_node = node;
            int co = 0;
            for (int i = 0; i != node->child.size(); ++i) {
                if (i > node->keys.size()) {
                    more_node->child.push_back(node->child[i]);
                    node->child[i]->parent = more_node;
                    node->child.erase(node->child.begin() + i);
                    --i;
                }
            }
        }

        auto& children = node->parent->child;
        auto it = std::find(children.begin(), children.end(), node);
        children.insert(it + 1, more_node);

        node->parent->keys.size() < 2 * TREE_DEGREE
            ? insertKeyIntoKeys(node->parent, parent_key)
            : splitNode(node->parent, parent_key);
    }
    return node;
}

std::shared_ptr<Node> addKeyIntoTree(std::shared_ptr<Node> node, Key newKey) {
    if (node->is_leaf) {
        node->keys.size() < 2 * TREE_DEGREE
            ? insertKeyIntoKeys(node, newKey)
            : splitNode(node, newKey);
    } else {
        for (int i = 0; i < node->keys.size(); ++i) {
            if (newKey.key < node->keys[i].key) {
                addKeyIntoTree(node->child[i], newKey);
                return node;
            } else if (i == node->keys.size() - 1) {
                addKeyIntoTree(node->child[i + 1], newKey);
                return node;
            }
        }
    }
    return node;
}

std::shared_ptr<Node> addValuesIntoTree(std::shared_ptr<Node> root) {
    while (true) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите ключ(число) и значение(строка): ";
        std::string line;
        std::getline(std::cin, line);
        int key;
        std::string value;
        if (std::stringstream(line) >> key >> value) {
            std::cout << "Ключ: " << key << ", Значение: " << value << "\n";
            Key newKey(key, value);
            root = addKeyIntoTree(root, newKey);
            std::ofstream outF("i.txt", std::ios::app);
            outF << key << " " << value << "\n";
        } else {
            std::cout << "Ошибка: некорректный ввод. Попробуйте ещё раз.\n";
        }
        std::cout << "Желаете вернуться в меню? Введите 1 ";
        int act = 2;
        
        std::cin >> act;
        if (act == 1) {
            return root;
        }
    }
    return root;
}

void printTree(std::shared_ptr<Node> root, int level) {
    for (int i = 0; i < level; ++i) {
        std::cout << ".";
    }
    for (const Key& k : root->keys) {
        std::cout << k.key << " ";
    }
    std::cout << "\n";
    ++level;
    for (const auto& child : root->child) {
        printTree(child, level);
    }
}

std::shared_ptr<Node> makeDefaultTree(std::shared_ptr<Node>& root) {
    std::ifstream inF("i.txt");
    std::string line;
    while (getline(inF, line)) {
        Key key;
        std::istringstream(line) >> key.key >> key.value;
        addKeyIntoTree(root, key);
    }
    return root;
}
bool findKeyInTree(std::shared_ptr<Node> node, int key) {
    bool is_found = false;
    for (const Key& k : node->keys) {
        if (k.key == key) {
            std::cout << "\n" << "Ключ: " << k.key << " Значение: " << k.value << "\n\n";
            return true;
        }
    }
    
    for (const auto& child : node->child) {
        if (findKeyInTree(child, key)) {
            return true;
        }
    }
    return is_found;
}
int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    Node rootNode({}, {}, true, nullptr);
    std::shared_ptr<Node> root = std::make_shared<Node>(rootNode);
    root = makeDefaultTree(root);
    while (true) {
        std::cout << "Выберите действие: 1 - добавить значение в Б-дерево\n"
            << "                   2 - показать Б-дерево\n"
            << "                   3 - найти значение в Б-дереве\n"
            << "                   4 - выйти из программы\n";
        int action = 4;
        std::cin >> action;
        switch (action) {
        case 1:
            root = addValuesIntoTree(root);
            break;
        case 2:
            std::cout << "\nБ-дерево:\n";
            printTree(root, 0);
            break;
        case 3: {
            std::cout << "Введите ключ: ";
            int find_key = 0;
            std::cin >> find_key;
            if (!findKeyInTree(root, find_key)) {
                std::cout << "\nКлюч " << find_key << " не найден\n\n";
            }
            break;
        }
        case 4:
            return 0;
        }
    }
    return 0;
}
