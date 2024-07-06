#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
using namespace std;

struct Stack {
    char op;
    double val;
    Stack* prev;
    Stack* next;
};
const double PI = 3.14159265;
Stack* CreateNode(char op) {
    Stack* newNode = new Stack();
    newNode->op = op;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}
Stack* CreateNode(double op) {
    Stack* newNode = new Stack();
    newNode->val = op;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}
int LengthOfStack(Stack* HeadStack) {
    int length = 0;
    Stack* head = HeadStack;
    while (head != nullptr) {
        head = head->next;
        length++;
    }
    return length;
}
Stack* addElem(char op,Stack* HeadStack) {
    int length = LengthOfStack(HeadStack);
    if (length == 0) {
        cout << "Stack is empty" << endl;
        return nullptr;
    }
    Stack* newNode = CreateNode(op);
    Stack* head = HeadStack;
    while (head->next != nullptr) {
        head = head->next;
    }
    Stack* current = head;
    current->next = newNode;
    newNode->prev = current;
    return HeadStack;
}
Stack* addElem(double op, Stack* HeadStack) {
    int length = LengthOfStack(HeadStack);
    if (length == 0) {
        cout << "Stack is empty" << endl;
        return nullptr;
    }
    Stack* newNode = CreateNode(op);
    Stack* head = HeadStack;
    while (head->next != nullptr) {
        head = head->next;
    }
    Stack* current = head;
    current->next = newNode;
    newNode->prev = current;
    return HeadStack;
}
Stack* delElem(char* buff_op, Stack* HeadStack) {
    if (LengthOfStack(HeadStack) == 1)  return HeadStack;
    if (LengthOfStack(HeadStack) > 1) {
        Stack* head = HeadStack;
        while (head->next != nullptr) {
            head = head->next;
        }
        *buff_op = head->op;
        head->prev->next = nullptr;
        head->prev = nullptr;
        head->next = nullptr;
        delete head;
        return HeadStack;
    }
}
Stack* delElem(double* buff_op, Stack* HeadStack) {
    if (LengthOfStack(HeadStack) == 1)  return HeadStack;
    if (LengthOfStack(HeadStack) > 1) {
        Stack* head = HeadStack;
        while (head->next != nullptr) {
            head = head->next;
        }
        *buff_op = head->val;
        head->prev->next = nullptr;
        head->prev = nullptr;
        head->next = nullptr;
        delete head;
        return HeadStack;
    }
}
void printList(Stack* headstack) {
    Stack* head = headstack;
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}
char* NewArr(string str) {
    int len = str.length();
    char* arr = new char[len];
    for (int i = 0; i < len; i++) {
        arr[i] = str[i];
    }
    return &arr[0];
}
void showText(char* arr, string str) {
    int len = str.length();
    for (int i = 0; i < len; i++) {
        cout << arr[i];
    }
    cout << endl;
}
bool IsOperation(char val) {
    if ((val == '+') || (val == '*') || (val == '^') || (val == '/') || (val == '-') || (val == '(') || (val == ')'))
        return 1;
    else
        return 0;
}
bool IsValue(char val) {
    if (((val >= '0') && (val <= '9')) || (val == ','))
        return 1;
    else
        return 0;
}
int Priority(char op) {
    switch (op)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '/':
        return 2;
    case '*':
        return 2;
    case '^':
        return 3;
    case '(':
        return 4;
    case ')':
        return 4;
    }
}
char LastElemStack(Stack* HeadStack) {
    Stack* head = HeadStack;
    while (head->next != nullptr){
        head = head->next;
    }
    return head->op;
}
string SortingMachine(char *arr, string str) {
    int len = str.length();
    Stack* HeadStack = nullptr;
    string postfixText = "";
    char buff_op;
    for (int i = 0; i < len; i++) {
        if (IsValue(arr[i]) == 1) postfixText += arr[i];
        if (IsValue(arr[i] == 0) || (arr[i] == ' ')) postfixText += " ";
        if (((arr[i] == 'c') && (arr[i + 1] == 'o') && (arr[i + 2] == 's')) || ((arr[i] == 's') && (arr[i + 1] == 'i') && (arr[i + 2] == 'n'))) {
            postfixText += arr[i];
            postfixText += arr[i + 1];
            postfixText += arr[i + 2];
            postfixText += " ";
            postfixText += arr[i + 3];
            postfixText += " ";
            i += 3;
        }
        if ((IsOperation(arr[i]) == 1) && (LengthOfStack(HeadStack) == 0)) HeadStack = CreateNode(arr[i]);
        else {
            if ((IsOperation(arr[i]) == 1) && (LengthOfStack(HeadStack) > 0)) {
                if (Priority(LastElemStack(HeadStack)) <= Priority(arr[i])) HeadStack = addElem(arr[i], HeadStack);
                else {
                    if (LengthOfStack(HeadStack) > 1) {
                        while (LengthOfStack(HeadStack) > 1) {
                            HeadStack = delElem(&buff_op, HeadStack);
                            postfixText += " ";
                            postfixText += buff_op;
                        }
                        postfixText += " ";
                        postfixText += HeadStack->op;
                        HeadStack->op = arr[i];
                    }
                    else {
                        postfixText += " ";
                        postfixText += HeadStack->op;
                        HeadStack->op = arr[i];
                    }
                }
            }
        }
    }
    if (LengthOfStack(HeadStack) > 1) {
        while (LengthOfStack(HeadStack) > 1) {
            HeadStack = delElem(&buff_op, HeadStack);
            postfixText += " ";
            postfixText += buff_op;
        }
        postfixText += HeadStack->op;
    }
    else {
        postfixText += " ";
        postfixText += HeadStack->op;
    }
    return postfixText;
}
string DelBracket(string Text) {
    int f = 0;
    for (int i = 0; i < Text.length(); i++) {
        if ((Text[i] == '(') || (Text[i] == ')')) {
            Text.erase(i, 1);
            i--;
        }
    }
    for (int i = 0; i < Text.length() - 1; i++) {
        if ((Text[i] == ' ') && (Text[i + 1] == ' ')) {
            Text.erase(i, 1);
            i--;
        }
    }
    return Text;
}
double FunctionValue(char op, double val1, double val2){
    switch (op)
    {
    case '+':
        return val2 + val1;
    case '-':
        return val2 - val1;
    case '*':
        return val2 * val1;
    case '/':
        return val2 / val1;
    case '^':
        return pow(val2, val1);
    default:
        break;
    }
}
double ValueOfExpression(string text) {
    Stack* HeadStack = nullptr;
    double value = 0, val1 = 0, val2 = 0, buff_val = 0;
    string txtval = "";
    bool f = 0;
    for (int i = 0; i < text.length(); i++) {
        if ((text[i] == 'c') && (text[i + 1] == 'o') && (text[i + 2] == 's')) {
            i += 4;
            while (IsValue(text[i]) == 1) {
                txtval += text[i];
                i++;
            }
            value = stod(txtval);
            value = cos(value * PI / 180);
            if (LengthOfStack(HeadStack) == 0) HeadStack = CreateNode(value);
            else {
                if (LengthOfStack(HeadStack) > 0) HeadStack = addElem(value, HeadStack);
            }
            txtval = "";
        }
        if ((text[i] == 's') && (text[i + 1] == 'i') && (text[i + 2] == 'n')) {
            i += 4;
            while (IsValue(text[i]) == 1) {
                txtval += text[i];
                i++;
            }
            value = stod(txtval);
            value = sin(value * PI / 180);
            if (LengthOfStack(HeadStack) == 0) HeadStack = CreateNode(value);
            else {
                if (LengthOfStack(HeadStack) > 0) HeadStack = addElem(value, HeadStack);
            }
            txtval = "";
        }
        if (IsValue(text[i]) == 1) {
            txtval += text[i];
        }
        if (((IsValue(text[i]) == 0) || (text[i] == ' ')) && (IsOperation(text[i]) == 0) && (txtval.length()>0)) {
            value = stod(txtval);
            if (LengthOfStack(HeadStack) == 0) HeadStack = CreateNode(value);
            else {
                if (LengthOfStack(HeadStack) > 0) HeadStack = addElem(value, HeadStack);
            }
            txtval = "";
        }
        if (IsOperation(text[i]) == 1) {
            HeadStack = delElem(&buff_val, HeadStack);
            val1 = buff_val;
            if (LengthOfStack(HeadStack) > 1) {
                HeadStack = delElem(&buff_val, HeadStack);
                val2 = buff_val;
                f = 1;
            }
            else {
                val2 = HeadStack->val;
                f = 0;
            }
            value = FunctionValue(text[i], val1, val2);
            if (f == 0) HeadStack->val = value;
            else HeadStack = addElem(value, HeadStack);
        }
        printList(HeadStack);
    }
    value = HeadStack->val;
    return value;
}


int main()
{
    setlocale(0, "");
    string str, finalText;
    char* p = nullptr;
    double val;
    int menu;
    while(true){
        cout << "Меню:" << endl;
        cout << "1 - Перевод инфиксной записи выражения в постфиксную." << endl;
        cout << "0 - выход из программы." << endl;
        cout << "> ";
        cin >> menu;
        cin.get();
        switch (menu)
        {
        case(1):
            cout << "Введите выражение" << endl << ">";
            getline(cin, str);
            p = NewArr(str);
            finalText = SortingMachine(p, str);
            finalText = DelBracket(finalText);
            cout << endl << "Постфиксная запись выражения: ";
            cout << finalText << endl;
            val = ValueOfExpression(finalText);
            cout << "Значение выражения: " << val << endl;
            break;
        case(0):
            return 0;
        default:
            cout << "Введено неправильное значение." << endl;
            break;
        }
        delete[] p;
        p = nullptr;
    }
}