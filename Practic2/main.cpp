#include <iostream>
#include <math.h>
using namespace std;

struct Stack {
    int size;
    double* root;
    Stack* prev;
    Stack* next;
};

Stack* CreateNode(int size, double& HeadArr) {
    Stack* newNode = new Stack();
    newNode->size = size;
    newNode->root = &HeadArr;
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
Stack* addElem(int size, double& HeadArr, Stack* HeadStack) {
    if(LengthOfStack(HeadStack) == 0){
        HeadStack = CreateNode(size, HeadArr);
        return HeadStack;
    }
    if (LengthOfStack(HeadStack) > 0) {
        Stack* newNode = CreateNode(size, HeadArr);
        Stack* head = HeadStack;
        while (head->next != nullptr) {
            head = head->next;
        }
        Stack* current = head;
        current->next = newNode;
        newNode->prev = current;
        return HeadStack;
    }
}
Stack* delElem(int& buff_size, Stack* HeadStack) {
    Stack* head = HeadStack;
    if (LengthOfStack(HeadStack) == 0) {
        return HeadStack;
    }
    if (LengthOfStack(HeadStack) == 1) {
        buff_size = HeadStack->size;
        HeadStack = nullptr;
        delete head;
        return HeadStack;
    }
    if (LengthOfStack(HeadStack) > 1) {
        while (head->next != nullptr) {
            head = head->next;
        }
        buff_size = head->size;
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
        cout << "size of subarray: " << head->size << endl;
        cout << "root of subarray: " << head->root << endl;
        head = head->next;
    }
    cout << endl;
}
Stack* EndOfStack(Stack* HeadStack) {
    Stack* head = HeadStack;
    while (head->next != nullptr) {
        head = head->next;
    }
    return head;
}

int GetMinrun(int n)
{
    int flag = 0;
    while (n >= 64) {
        flag |= n & 1;
        n >>= 1;
    }
    return n + flag;
}
void Insertion_sort(double& start, double& end) {
    double* p = nullptr, * index = &start;
    while (index != &end) {
        p = index;
        while ((*p < *(p - 1)) && (p != &start)) {
            swap(*p, *(p - 1));
            p--;
        }
        index++;
    }

}
double* Subarray(int minrun, double& arr) {
    double* run = new double[minrun], * p = &arr;
    for (int i = 0; i < minrun; i++) {
        run[i] = *p;
        if (p > (p + 1)) {
            for (int j = i; j < minrun - i; j++) {
                run[j] = *p;
                p++;
            }
            break;
        }
        p++;
    }
    Insertion_sort(run[0], run[minrun]);
    return &run[0];
}
double* Galopping_func(int size, int& count_i, double* index1, double* index2, double& arr) {
    int j = 0, count = 0;
    double* p = &arr;
    while (count_i < size) {
        j++; count = pow(2, j);
        if (*index1 > *index2) break;
        else {
            while ((count > 0) || (count_i < size)) {
                *p = *index1;
                index1++;
                count--;
                count_i++;
            }
        }
    }
    return index1;
}
double* Merge_sort(int size1, int size2, double* index1, double* index2) {
    int size = size1 + size2;
    double* arr = new double[size];
    int i = 0, count_i1 = 0, count_i2 = 0, count_galop1 = 0, count_galop2 = 0;
    while (true) {
        if (*index2 < *index1) {
            arr[i] = *index2;
            index2++;
            count_i2++;
            //if (count_galop1 != 0) count_galop1 = 0;
            //count_galop2++;
            //if (count_galop1 == 5) {
            //    index2 = Galopping_func(size2, count_i2, index2, index1, arr[i]);
            //}
        }
        else{
            arr[i] = *index1;
            index1++;
            count_i1++;
            //if (count_galop2 != 0) count_galop2 = 0;
            //count_galop1++;
            //if (count_galop1 == 5) {
            //    index1 = Galopping_func(size1, count_i1, index1, index2, arr[i]);
            //}
        }
        i++;
        if ((count_i2 >= size2 - 1) || (count_i1 >= size1 - 1)) {
            break;
        }
    }
    if (count_i1 == size1 - 1) {
        for (int j = count_i2; j < size2; j++, i++) {
            arr[i] = *index2;
            index2++;
        }
    }
    else {
        if (count_i2 == size2 - 1) {
            for (int j = count_i1; j < size1; j++, i++) {
                arr[i] = *index1;
                index1++;
            }
        }
    }
    return &arr[0];
}
Stack* TimsortFunc(double& arr, double& end, int N, Stack* HeadStack) {
    Stack* EndStack = nullptr;
    int minrun = GetMinrun(N), size = 0;
    double* index = nullptr, * index_count = &arr;
    double* buff_index = nullptr;
    int buff_size = 0, count = 0;
    while (count + minrun <= N) {
        index = Subarray(minrun, *index_count);
        count += minrun;
        HeadStack = addElem(minrun,* index, HeadStack);
        if (LengthOfStack(HeadStack) > 1) {
            while(LengthOfStack(HeadStack) > 1) {
                EndStack = EndOfStack(HeadStack);
                if (EndStack->prev->size <= EndStack->size) {
                    buff_index = EndStack->root; EndStack = EndStack->prev;
                    HeadStack = delElem(buff_size, HeadStack);
                    index = EndStack->root;
                    buff_index = Merge_sort(EndStack->size, buff_size, index, buff_index);
                    EndStack->size += buff_size;
                    HeadStack = delElem(buff_size, HeadStack);
                    HeadStack = addElem(buff_size, *buff_index, HeadStack);
                }
                else {
                    break;
                }
            }
        }
        index_count += minrun;
    }
    if (count < N) {
        count = N - count - 1;
        index = Subarray(count, *index_count);
        HeadStack = addElem(count,* index, HeadStack);
    }
    while (LengthOfStack(HeadStack) > 1) {
        EndStack = EndOfStack(HeadStack);
        buff_index = EndStack->root; EndStack = EndStack->prev;
        HeadStack = delElem(buff_size, HeadStack);
        index = EndStack->root;
        buff_index = Merge_sort(EndStack->size, buff_size, index, buff_index);
        EndStack->size += buff_size;
        HeadStack = delElem(buff_size, HeadStack);
        HeadStack = addElem(buff_size, *buff_index, HeadStack);
    }
    return HeadStack;      
}
int menu() {
    int choice;
    cout << "Меню:" << endl;
    cout << "1) Создание массива, заполнение его случайными числами" << endl;
    cout << "2) Просмотр массива до сортировки" << endl;
    cout << "3) Сортировка массива Timsort сортировкой" << endl;
    cout << "4) Сортировка массива Quicksort сортировкой" << endl;
    cout << "5) Вывод отсортированного массива" << endl;
    cout << "0) Выход из программы" << endl;
    cout << "> ";
    cin >> choice;
    return choice;
}

//функции для quicksort
int partition(double arr[], int low, int high) {
    double pivot = arr[high];
    int i = low - 1; 

    for (int j = low; j < high; ++j) {
        
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void QuickSort(double arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        QuickSort(arr, low, pivotIndex - 1);
        QuickSort(arr, pivotIndex + 1, high);
    }
}

int main(){
    setlocale(0, "");
    int n;
    double* arr = nullptr;
    Stack* HeadStack = nullptr;
    double* p = nullptr;
    int choice;
    while (true) {
        choice = menu();
        switch (choice)
        {
        case 1:
            if (arr != nullptr) {
                delete[] arr;
                arr = nullptr;
            }
            cout << "Введите число элементов в массиве: ";
            cin >> n;
            arr = new double[n];
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 10000 - 5000;
            }
            break;
        case 2:
            cout << "Массив до сортировки:" << endl;
            for (int i = 0; i < n; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
            break;
        case 3:
            HeadStack = TimsortFunc(arr[0], arr[n - 1], n, HeadStack);
            break;
        case 4:
            QuickSort(arr, 0, n - 1);
            break;
        case 5:
            if (HeadStack != nullptr) {
                p = HeadStack->root;
                cout << "Отсортированный массив: " << endl;
                for (int i = 0; i < HeadStack->size; i++) {
                    cout << *p << " ";
                    p++;
                }
                cout << endl;
            }
            else {
                p = arr;
                cout << "Отсортированный массив: " << endl;
                for (int i = 0; i < n; i++) {
                    cout << *p << " ";
                    p++;
                }
                cout << endl;
            }
            break;
        case 0:
            return 0;
        default:
            cout << "Введено неправильное значение" << endl;
            break;
        }
    }
}