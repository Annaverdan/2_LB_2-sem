#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

struct List {
    int data;
    List* head;
    List* tail;

    List(int newData) {
        data = newData;
        tail = head = nullptr;
    }
};

// создание списка
List* creating_list(int len) {
    List* curr = 0, *next = 0;
    for (int i = 1; i <= len; i++) {
        curr = new List(rand() % 100);
        curr -> tail = next;
        if (next)
            next -> head = curr;
        next = curr;
    }
    curr -> head = nullptr;
    return curr;
}

// вставка в конец списка
List* insert_at_end(List* begin, int newData) {
    List* newElem = new List(newData);
    if (begin == nullptr) {
        begin = newElem;
    }
    else {
        List* curr = begin;
        while (curr -> tail != nullptr)
            curr = curr -> tail;
        curr -> tail = newElem;
        newElem -> head = curr;
    }
    return begin;
}

void print_list(List* next) {
    List* temp = next;
    cout << "Текущий список выглядит следующим образом: " << endl;
    while (temp != nullptr) {
        cout << temp -> data << " ";
        temp = temp -> tail;
    }
    cout << endl;
}

int find_size(List* curr) {
    int size = 0;
    while (curr != nullptr) {
        size++;
        curr = curr -> tail;
    }
    return size;
}

// вставить после элемента
void insert_after_element(List* begin, int afterElem, int newData) {
    List* curr = begin;
    while (curr != nullptr && curr -> data != afterElem) {
        curr = curr->tail;
    }
    if (curr != nullptr) {
        List* temp = new List(newData);
        List* nextElem = curr -> tail;
        curr -> tail = temp;
        temp -> head = curr;
        temp -> tail = nextElem;
        if (nextElem != nullptr) {
            nextElem -> head = temp;
        }
    }
    else {
        cout << "В списке нет такого элемента. " << endl;
    }
}

// обмен элементов 
void swap_elements(List* begin, int firstElem, int secondElem) {
    if (firstElem == secondElem) {
        cout << "Введите два разных элемента: " << endl;
        return;
    }
    List* prevFirst = nullptr,
        * currFirst = begin;
    while (currFirst && currFirst -> data != firstElem) {
        prevFirst = currFirst;
        currFirst = currFirst -> tail;
    }
    List* prevSecond = nullptr,
        * currSecond = begin;
    while (currSecond && currSecond -> data != secondElem) {
        prevSecond = currSecond;
        currSecond = currSecond -> tail;
    }
    if (currSecond == nullptr || currFirst == nullptr) {
        cout << "В списке таких элементов нет." << endl;
        return;
    }
    if (prevFirst != nullptr)
        prevFirst -> tail = currSecond;
    else
        begin = currSecond;
    if (prevSecond != nullptr)
        prevSecond -> tail = currFirst;
    else
        begin = currFirst;
    List* temp = currSecond -> tail;
    currSecond -> tail = currFirst -> tail;
    currFirst -> tail = temp;
}

// поиск элемента в списке
void search_element(List* begin, int value) {
    List* curr = begin;
    int index = 1;
    while (curr != nullptr && curr -> data != value) {
        curr = curr -> tail;
        index++;
    }
    if (curr != nullptr) {
        cout << "Элемент имеет " << index << " в списке " << endl;;
    }
    else {
        cout << "В списке нет такого элемента." << endl;
    }
}

// поиск по индексу
void search_Index(List* begin, int index) {
    List* curr = begin;
    int tempIndex = 1;
    while (curr != nullptr && tempIndex != index) {
        curr = curr -> tail;
        tempIndex++;
    }
    if (curr != nullptr) {
        cout << "Элементом с таким индексом является: " << curr -> data << endl;;
    }
    else {
        cout << "В списке нет такого элемента." << endl;
    }
}

// удвление по элементу
void delete_element(List* begin, int del) {
    List* curr = begin;
    while (curr != nullptr && curr -> data != del) {
        curr = curr -> tail;
    }
    if (begin == nullptr || curr == nullptr) {
        cout << "Ваш список пуст или в нем нет такого элемента. Элемент не удалось удалить. " << endl;
        return;
    }
    if (begin == curr)
        begin = curr -> tail;
    if (curr -> tail != nullptr) {
        curr -> tail -> head = curr -> head;
    }
    if (curr -> head != nullptr) {
        curr -> head -> tail = curr -> tail;
    }
    free(curr);
}

// удаление по индексу
void delete_Index(List* begin, int index) {
    List* curr = begin;
    int tempIndex = 1;
    while (curr != nullptr && tempIndex != index) {
        curr = curr -> tail;
        tempIndex++;
    }
    if (begin == nullptr || curr == nullptr) {
        cout << "Ваш список пуст или в нем нет такого элемента. Элемент не удалось удалить. " << endl;
        return;
    }
    if (begin == curr)
        begin = curr -> tail;
    if (curr -> tail != nullptr) {
        curr -> tail -> head = curr -> head;
    }
    if (curr -> head != nullptr) {
        curr -> head -> tail = curr -> tail;
    }
    free(curr);
}

List* bubbleSort(List* begin) {
    if (begin == nullptr)
        return begin;
    bool swapped;
    List* curr;
    List* last = nullptr;
    do {
        swapped = false;
        curr = begin;
        while (curr -> tail != last) {
            if (curr -> data > curr -> tail -> data) {
                int swapData = curr -> data;
                curr -> data = curr -> tail -> data;
                curr -> tail -> data = swapData;
                swapped = true;
            }
            curr = curr->tail;
        }
        last = curr;
    } while (swapped);
    return begin;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    List* begin = nullptr;
    cout << "Выберите, что вы хотите делать. " << endl;
    while (true) {
        cout << "1. Создать список и определить время, необходимое для его создания." << endl 
             << "2. Изменить список и определить, сколько времени займет внесение определенных изменений. " << endl 
             << "3. ИДЗ" << endl;
        int answer;
        cin >> answer;
        if (answer == 1) {
            cout << "1. Создать список с определенным количеством элементов. " << endl 
                 << "2. Создать список с определенными элементами. " << endl;
            int answerListType;
            cin >> answerListType;
            cout << endl;
            if (answerListType == 1) {
                int amountOfElements;
                cout << "Введите количество элементов, которые есть в списке. " << endl;
                cin >> amountOfElements;
                auto start = chrono::steady_clock::now();
                begin = creating_list(amountOfElements);
                auto stop = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                print_list(begin);
                cout << "Время, затраченное на создание списка, составляет: " << duration.count() << " нс. " << endl;
            }
            if (answerListType == 2) {
                int answerInsert, size;
                int durationTime = 0;
                do {
                    cout << "Введите элемент, который вы хотите добавить в текущий список: " << endl;
                    int element;
                    cin >> element;
                    auto start = chrono::steady_clock::now();
                    begin = insert_at_end(begin, element);
                    auto stop = chrono::steady_clock::now();
                    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                    durationTime += duration.count();
                    cout << "Вы хотите добавить еще один элемент? (1 - да, 0 - нет) " << endl;
                    cin >> answerInsert;
                } while (answerInsert);
                print_list(begin);
                size = find_size(begin);
                cout << "Размер списка составляет: " << size << endl;
                cout << "Время, затраченное на создание списка, составляет: " << durationTime << " нс. " << endl;
            }
        }
        if (answer == 2) {
            cout << "1. Вставить элемент после определенного элемента в списке.  " << endl 
                 << "2. Удалить элемент " << endl 
                 << "3. Чтобы поменять местами два элемента " << endl 
                 << "4. Чтобы получить определенный элемент из списка." << endl;
            int answerModificaton;
            cin >> answerModificaton;
            if (answerModificaton == 1) {
                cout << "Введите элемент, после которого вы хотите вставить другой элемент: " << endl;
                int keyElement;
                cin >> keyElement;
                cout << endl;
                cout << "Введите элемент, который вы хотите вставить: " << endl;
                int insertElement;
                cin >> insertElement;
                cout << endl;
                auto start = chrono::steady_clock::now();
                insert_after_element(begin, keyElement, insertElement);
                auto stop = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                print_list(begin);
                cout << "Количество времени, затраченного на вставку элемента, равно: " << duration.count() << " нс." << endl;
            }
            if (answerModificaton == 2) {
                cout << "Как вы хотите удалить элемент? " << endl;
                cout << "1. Удалить определенный элемент. " << endl << "2. Удалить элемент с определенным индексом. " << endl;
                int answerDelete;
                cin >> answerDelete;
                if (answerDelete == 1) {
                    cout << "Какой элемент из списка вы хотите удалить?" << endl;
                    int elementToDelete;
                    cin >> elementToDelete;
                    auto start = chrono::steady_clock::now();
                    delete_element(begin, elementToDelete);
                    auto stop = chrono::steady_clock::now();
                    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                    cout << "Элемент был успешно удален. " << endl;
                    print_list(begin);
                    cout << "Время, затраченное на удаление элемента в списке, равно: " << duration.count() << " нс. " << endl;
                }
                if (answerDelete == 2) {
                    cout << "Введите индекс элемента, который вы хотите удалить: " << endl;
                    int indexDelete;
                    cin >> indexDelete;
                    int listSize = find_size(begin);
                    if (indexDelete > listSize) {
                        cout << "В вашем списке нет элемента с таким индексом из-за его размера. " << endl;
                    }
                    auto start = chrono::steady_clock::now();
                    delete_Index(begin, indexDelete);
                    auto stop = chrono::steady_clock::now();
                    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                    cout << "The element with your index has been successfully deleted. " << endl;
                    print_list(begin);
                    cout << "Время, затраченное на удаление элемента в списке, равно " << duration.count() << " нс. " << std::endl;
                }
            }
            if (answerModificaton == 3) {
                cout << "Введите два разных элемента из списка, которые вы хотите поменять местами: " << std::endl;
                int firstElement, secondElement;
                cin >> firstElement;
                cout << endl;
                cin >> secondElement;
                cout << endl;
                swap_elements(begin, firstElement, secondElement);
                print_list(begin);
            }
            if (answerModificaton == 4) {
                cout << "1. Определенный элемент. " << endl << "2. Элемент с особым индексом. " << endl;
                int answerGet;
                cin >> answerGet;
                if (answerGet == 1) {
                    print_list(begin);
                    cout << "Какой элемент вы хотите получить? " << endl;
                    int answerGetElement;
                    cin >> answerGetElement;
                    auto start = chrono::steady_clock::now();
                    search_element(begin, answerGetElement);
                    auto stop = chrono::steady_clock::now();
                    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                    cout << "Время, затраченное на поиск элемента в списке, равно:" << duration.count() << " нс. " << endl;
                }
                if (answerGet == 2) {
                    cout << "Введите индекс элемента, который вы хотите найти" << endl;
                    int answerIndex;
                    cin >> answerIndex;
                    int listSize = find_size(begin);
                    if (answerIndex > listSize) {
                        cout << "В вашем списке нет элемента с таким индексом из-за его размера. " << endl;
                    }
                    else {
                        auto start = chrono::steady_clock::now();
                        search_Index(begin, answerIndex);
                        auto stop = chrono::steady_clock::now();
                        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
                        cout << "Время, затраченное на поиск элемента в списке, равно:" << duration.count() << " нс. " << endl;
                    }
                }
            }
        }
        if (answer == 3) {
            List* head = bubbleSort(begin);
            auto start = chrono::steady_clock::now();
            print_list(head);
            auto stop = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            cout << "Время, затраченное на сортировку списка с помощью пузырьковой сортировки, составляет " << duration.count() << " нс. " << endl;
        }
    }
}
