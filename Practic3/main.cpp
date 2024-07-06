#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include<fstream>
#include<iomanip>
#include<queue>

using namespace std;
struct avl_node {
    int data;
    struct avl_node* left;
    struct avl_node* right;
};

class avlTree {
    
public:
    int height(avl_node*);
    int diff(avl_node*);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* left_rotation(avl_node*);
    avl_node* right_rotation(avl_node*);
    avl_node* balance(avl_node*);
    bool Checkbalance(avl_node*);
    avl_node* FindMin(avl_node*);
    avl_node* DelMin(avl_node*);
    avl_node* AddElem(avl_node*, int);
    avl_node* DeleteElem(avl_node*, int);
    avl_node* FindElem(avl_node*, int, bool&);
    void printTree(avl_node*, int);
    void inorder(avl_node*);
    void preorder(avl_node*);
    void postorder(avl_node*);
    void widthorder(avl_node*);
    avlTree(){
    }
};

// Высота АВЛ дерева
int avlTree::height(avl_node* headTree)
{
    int h = 0;
    if (headTree != NULL)
    {
        int l_height = height(headTree->left);
        int r_height = height(headTree->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
// Разница в высоте
int avlTree::diff(avl_node* headTree)
{
    int l_height = height(headTree->left);
    int r_height = height(headTree->right);
    int b_factor = r_height - l_height;
    return b_factor;
}
// Малый правый поворот
avl_node* avlTree::rr_rotation(avl_node* headTree)
{
    avl_node* temp;
    temp = headTree->right;
    headTree->right = temp->left;
    temp->left = headTree;
    return temp;
}
// Малый левый поворот
avl_node* avlTree::ll_rotation(avl_node* headTree)
{
    avl_node* temp;
    temp = headTree->left;
    headTree->left = temp->right;
    temp->right = headTree;
    return temp;
}
avl_node* avlTree::left_rotation(avl_node* headTree)
{
    avl_node* temp = headTree->right;
    headTree->right = temp->left;
    temp->left = headTree;
    return temp;
}
avl_node* avlTree::right_rotation(avl_node* headTree)
{
    avl_node* temp = headTree->left;
    headTree->left = temp->right;
    temp->right = headTree;
    return temp;
}
// Большой левый поворот
avl_node* avlTree::lr_rotation(avl_node* headTree)
{
    avl_node* temp;
    temp = headTree->left;
    headTree->left = rr_rotation(temp);
    return ll_rotation(headTree);
}
// Большой правый поворот
avl_node* avlTree::rl_rotation(avl_node* headTree)
{
    avl_node* temp;
    temp = headTree->right;
    headTree->right = ll_rotation(temp);
    return rr_rotation(headTree);
}
// Балансировка АВЛ дерева
avl_node* avlTree::balance(avl_node* headTree){
    int bal_factor = diff(headTree);
    if (bal_factor == 2)
    {
        if (diff(headTree->right) < 0)
            headTree->right = right_rotation(headTree->right);
        return left_rotation(headTree);
    }
    if (bal_factor == -2)
    {
        if (diff(headTree->left) > 0)
            headTree->left = left_rotation(headTree->left);
        return right_rotation(headTree);
    }
    return headTree;
}
// Проверка на сбалансированность АВЛ дерева
bool avlTree::Checkbalance(avl_node* headTree)
{
    int bal_factor = diff(headTree);
    if (bal_factor > 1)
    {
        return false;
    }
    else if (bal_factor < -1)
    {
       return false;
    }
    else {
        return true;
    }
}
// Добавление элемента в дерево c балансировкой
avl_node* avlTree::AddElem(avl_node* temp, int value)
{
    if (temp == NULL)
    {
        temp = new avl_node;
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    else if (value < temp->data)
    {
        temp->left = AddElem(temp->left, value);
    }
    else if (value >= temp->data)
    {
        temp->right = AddElem(temp->right, value);
    }
    return balance(temp);
}
// Вывод АВЛ дерева
void avlTree::printTree(avl_node* headTree, int level = 0) {
    if (headTree != nullptr) {
        printTree(headTree->right, level + 1);
        for (int i = 0; i < level; ++i) {
            cout << "    ";
        }
        cout << headTree->data << setw(4) << "\n";
        printTree(headTree->left, level + 1);
    }
}
// Прямой обход в АВЛ дереве
void avlTree::preorder(avl_node* tree)
{
    if (tree == NULL)
        return;
    cout << tree->data << "  ";
    preorder(tree->left);
    preorder(tree->right);
}
// Симметричный обход в АВЛ дереве
void avlTree::inorder(avl_node* tree)
{
    if (tree == NULL)
        return;
    inorder(tree->left);
    cout << tree->data << "  ";
    inorder(tree->right);
}
//  Обратный обход в АВЛ дереве
void avlTree::postorder(avl_node* tree)
{
    if (tree == NULL)
        return;
    postorder(tree->left);
    postorder(tree->right);
    cout << tree->data << "  ";
}
void avlTree::widthorder(avl_node* root) {
    if (root == nullptr) {
        return;
    }

    queue<avl_node*> q;
    q.push(root);

    while (!q.empty()) {
        avl_node* current = q.front();
        cout << current->data << " ";
        q.pop();

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}
avl_node* avlTree::FindMin(avl_node* temp) {
    return temp->left ? FindMin(temp->left) : temp;
}
avl_node* avlTree::DelMin(avl_node* temp) {
    if (temp->left == nullptr) return temp->right;
    temp->left = DelMin(temp->left);
    return balance(temp);
}
avl_node* avlTree::DeleteElem(avl_node* root, int value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->data) {
        root->left = DeleteElem(root->left, value);
    }
    else if (value > root->data) {
        root->right = DeleteElem(root->right, value);
    }
    else if (value == root->data) {
        /*if (root->left == nullptr) {
            avl_node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            avl_node* temp = root->left;
            delete root;
            return temp;
        }*/

        avl_node* q = root->left;
        avl_node* r = root->right;
        delete root;
        if (!r) return q;
        avl_node* min = FindMin(r);
        min->right = DelMin(r);
        min->left = q;
        return balance(min);
    }
    else {
        cout << "Элемента с данным значением нет в дереве" << endl;
    }
    return balance(root);
}
avl_node* avlTree::FindElem(avl_node* root, int value, bool& f) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->data) {
        root->left = FindElem(root->left, value, f);
    }
    else if (value > root->data) {
        root->right = FindElem(root->right, value, f);
    }
    else {
        if (value == root->data) {
            cout << "Элемент присутствует в дереве" << endl;
            f = true;
        }
    }
    return root;
}


int menu() {
    int ch;
    cout << "Меню:" << endl;
    cout << "1)Чтение скобочной записи (создание двоичного дерева)" << endl;
    cout << "2)Вывод двоичного дерева" << endl;
    cout << "3)Создание АВЛ дерева из двоичного" << endl;
    cout << "4)Вывод АВЛ дерева" << endl;
    cout << "5)Добавление элемента в АВЛ дерево" << endl;
    cout << "6)Удаление элемента из АВЛ дерева" << endl;
    cout << "7)Поиск элемента в АВЛ дереве" << endl;
    cout << "8)Обход (вывод) АВЛ дерева" << endl;
    cout << "0)Выход" << endl;
    cout << "> ";
    cin >> ch;
    return ch;
}
bool check(string line) {
    int count = 0;
    //char symbol = ' ';
    if (line[0] == ')') return false;
    if (line[line.length() - 1] == '(') return false;
    for (int i = 0; i < line.length(); i++) {
        //symbol = line[i];
        //if (((symbol > 47) && (symbol < 58)) || (symbol == 40) || (symbol == 41) ||(symbol == ' ')) continue;
        //else return false;
        if ((line[i] == '(') && (line[i + 1] == ')') && (i < line.length())) return false;
        if (line[i] == '(') count++;
        else if (line[i] == ')') {
            count--;
        }
    }
    if (count < 0) return false;
    else return true;
}
avl_node* insertBracketForm(const string& str, size_t& index, int& count) {
    if (index >= str.length()) {
        return nullptr;
    }

    // Пропускаем пробелы и открывающую скобку
    while (index < str.length() && (str[index] == ' ' || str[index] == '(')) {
        ++index;
    }

    // Если достигнут конец строки или закрывающая скобка, возвращаем nullptr
    if (index >= str.length() || str[index] == ')') {
        return nullptr;
    }

    // Считываем значение узла
    int value;
    stringstream ss;
    while (index < str.length() && isdigit(str[index])) {
        ss << str[index++];
    }
    ss >> value;
    count++;

    // Создаем узел и рекурсивно добавляем его потомков
    avl_node* root = new avl_node;
    root->data = value;
    root->left = insertBracketForm(str, index, count);
    root->right = insertBracketForm(str, index, count);
    index++;

    return root;
}
avl_node* parsing_question(avl_node* root, int& count) {
    string line;
    size_t index = 0;
    ifstream file("text.txt");
    if (file.is_open())
    {
        while (getline(file, line, '\0'))
        {
            cout << line << endl;
        }
    }
    file.close();
    if (check(line) == false) {
        cout << "В скобочной последовательности присутствуют ошибки в записи" << endl;
    }
    else {
        root = insertBracketForm(line, index, count);
    }
    return root;
}
int* CreateAVLtree(avl_node* root, avlTree treefunc, int count) {
    if (root == nullptr) {
        return 0;
    }

    queue<avl_node*> q;
    int* p = new int[count], index = 0;
    q.push(root);

    while (!q.empty()) {
        avl_node* current = q.front();
        p[index] = current->data;
        index++;
        q.pop();

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
    return p;
}
avl_node* avl_question(avl_node* root, avlTree treefunc, int count) {
    int* arr = CreateAVLtree(root, treefunc, count);
    avl_node* AVLtree = nullptr;
    for (int i = 0; i < count; i++) {
        AVLtree = treefunc.AddElem(AVLtree, *arr);
        arr++;
    }
    return AVLtree;
}
avl_node* delete_question(avl_node* root, avlTree treefunc, int value) {
    root = treefunc.DeleteElem(root, value);
    return root;
}
avl_node* add_question(avl_node* root, avlTree treefunc, int value) {
    root = treefunc.AddElem(root, value);
    return root;
}
void order_question(avl_node* root, avlTree treefunc) {
    int ch;
    cout << "Обходы:" << endl;
    cout << "1) Прямой обход" << endl;
    cout << "2) Симметричный обход" << endl;
    cout << "3) Обратный обход" << endl;
    cout << "4) Обход в ширину" << endl;
    cout << "> ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        treefunc.preorder(root);
        break;
    case 2:
        treefunc.inorder(root);
        break;
    case 3:
        treefunc.postorder(root);
        break;
    case 4:
        treefunc.widthorder(root);
        break;
    default:
        cout << "Введено неправильное значение" << endl;
        break;
    }
    cout << endl;
}

int main()
{
    setlocale(0, "");
    avlTree treefunc;
    bool f = false;
    avl_node* RootBinTree = nullptr, *RootAvlTree = nullptr;
    int ch, value, countElem = 0;
    while (true)
    {
        ch = menu();
        switch (ch)
        {
        case 1:
            RootBinTree = parsing_question(RootBinTree, countElem);
            break;
        case 2:
            treefunc.printTree(RootBinTree);
            break;
        case 3:
            RootAvlTree = avl_question(RootBinTree, treefunc, countElem);
            break;
        case 4:
            treefunc.printTree(RootAvlTree);
            break;
        case 5:
            cout << "Введите число: ";
            cin >> value;
            RootAvlTree = add_question(RootAvlTree, treefunc, value);
            break;
        case 6:
            cout << "Введите число: ";
            cin >> value;
            RootAvlTree = delete_question(RootAvlTree, treefunc, value);
            break;
        case 7:
            cout << "Введите число: ";
            cin >> value;
            RootAvlTree = treefunc.FindElem(RootAvlTree, value, f);
            if (f == false) {
                cout << "Элемента с данным значением нет в дереве" << endl;
            }
            break;
        case 8:
            if (RootAvlTree == nullptr) {
                order_question(RootBinTree, treefunc);
            }
            else {
                order_question(RootAvlTree, treefunc);
            }
            break;
        case 0:
            return 0;
            break;
        default:
            break;
        }
    }
    
}