#include <iostream> 
#include <iomanip>
#include <string>
#include <time.h>
using namespace std;
#define RAND(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); }~LC() { cin.get(); cin.get(); } } _;

// Списки
// Односвязанный список
// Создайте шаблонный класс односвязного списка.
// Интерфейс класса List<> и вспомогательной структуры Element<> находятся в файле
// "1-Работа в классе-TList1.txt"
// Необходимо заполнить класс методами, которые описаны в интерфейсе класса List<>

// Шаблон структуры одного узла списка
template <class T>
struct Element
{
    Element* pNext;   // указатель на следующий элемент
    T         Data;    // полезные данные
    // Методы узла
    Element() : pNext(), Data() {}
    Element(T data, Element* next = nullptr) : Data(data), pNext(next) {}

    Element* GetNext() { return pNext; }
    void     SetNext(Element* next) { pNext = next; }

    T    GetData() { return Data; }
    void SetData(T val) { Data = val; }
};

// std::list<>
// Шаблон класса односвязного списка
template <class T>
class List
{
private:
    Element<T>* pHead, * pTail; // указатели на головной и хвостой элементы списка
    int Cnt; // текущее количество узлов в списке
public:
    List() : pHead(), pTail(), Cnt() {} // пустой список
    List(const T& val) : List() { AddHead(val); } // иниц-ция одним элементом
    // иниц-ция массивом
    List(const T* mas, int size) : List()
    {
        for (int i = 0; i < size; i++)
        {
            AddTail(mas[i]);
        }
    }
    // конструктор копирования
    List(const List& obj) : List() { *this = obj; }

    // оператор копирования, присваивания копированием
    List& operator = (const List& obj)
    {
        if (this != &obj)
        {
            for (int i = 0; i < obj.GetCnt(); i++)
            {
                this->Insert(obj.Get(i), i);
            }
            this->Cnt = obj.GetCnt();
        }
        return *this;
    }

    /// Деструктор - удалени всех элементов списка
    ~List() { Clear(); }

    // Очистка узла - удалени всех элементов списка
    void Clear()
    {
        while (Cnt)
        {
            DeleteHead();
        }
    }

    // Добавить новый элемент в начало списка
    //  Аналог метода list<T>::push_front();
    void AddHead(const T& val)
    {
        Element<T>* newElm = new Element<T>(val);
        if (!Cnt)
        {
            pHead = pTail = newElm;
        }
        else
        {
            newElm->pNext = pHead;
            pHead = newElm;
        }
        Cnt++;
    }

    // Добавить новый элемент в конец списка
    //  Аналог метода list<T>::push_back();
    void AddTail(const T& val)
    {
        Element<T>* newElm = new Element<T>(val);
        if (!Cnt)
        {
            pHead = pTail = newElm;
        }
        else
        {
            pTail->pNext = newElm;
            pTail = newElm;
        }
        Cnt++;
    }

    // Удалить головной элемент
    //  Аналог метода list<T>::pop_front();
    void DeleteHead()
    {
        if (Cnt)
        {
            Element<T>* temp = pHead->pNext;
            delete pHead;
            pHead = temp;
            if (!--Cnt) { pTail = nullptr; }
        }
        else
        {
            cout << "Error: the list is empty\n";
        }
    }

    // Удалить хвостовой элемент
    //  Аналог метода list<T>::pop_back();
    void DeleteTail()
    {
        if (Cnt)
        {
            Element<T>* temp = pHead;
            for (int i = 0; i < Cnt - 2; i++)
            { 
                temp = temp->pNext; 
            }
            delete pTail;
            pTail = temp;
            if (!--Cnt) { pHead = pTail = nullptr; }
            else { pTail->pNext = nullptr; }
        }
        else { cout << "Error: the list is empty\n"; }
    }

    // Вставить элемент в список в указанную позицию index
    void Insert(const T& val, int index)
    {
        if (index == 0) { AddHead(val); }
        else if (index == Cnt) { AddTail(val); }
        else if (index > 0 && index < Cnt)
        {
            Element<T>* newEl = new Element<T>(val);
            Element<T>* count = pHead;
            Element<T>* next = nullptr;
            for (int i = 0; i < index - 1; i++)
            {
                count = pHead->pNext;
            }
            next = count->pNext;
            count->pNext = newEl;
            newEl->pNext = next;
            Cnt++;
        }
        else {
            cout << "Error: Out of range!\n";
        }
    }

    // Получить текущее кол-во узлов в списке
    int GetCnt() const { return Cnt; }

    // Получить значение узла по указанной позиции
    // cout << A.Get(i) << endl;
    T Get(int index = 0) const
    {
        if (index > -1 && index < Cnt) 
        {
            Element<T>* othr = pHead;
            for (int i = 0; i < index; i++)
            {
                othr = othr->pNext;
            }
            return othr->Data;
        }
        throw 1;
    }

    // перегруженные операторы индексации []
    // int a = list[i];
    T operator[](int index) const
    { // для чтения
        return Get(index);
    }

    // list[i] = 123;
    T& operator[](int index)
    { // для записи (изменения)
        return Get(index);
    }
    
    // Поиск узла с заданным значением
    // Возвращает индекс найденного узла или -1 в противном случае
    int Search(const T& val)
    {
        Element<T>* temp = pHead;
        for (int i = 0; i < Cnt; i++)
        {
            if (temp->Data == val) { return i; }
            temp = temp->pNext;
        }
        return -1;
    }

    // полный прототип перегруженного оператора вывода в поток
    template <class T>
    friend ostream& operator << (ostream& os, const List<T>& obj);

}; // class List<>;

// сам перегруженный оператор вывода в поток
template <class T>
ostream& operator<<(ostream& os, const List<T>& obj)
{
    os << "Size = " << obj.GetCnt() << endl;
    for (int i = 0; i < obj.GetCnt(); i++)
    {
        os << i + 1 << ") " << obj.Get(i) << endl;
    }
    return os;
}


int main()
{
    List< string > A("First value");
    string s = "Second value";
    A.AddHead(s);
    s = "Third value";
    A.AddTail(s);
    s = "Fourth value";
    A.Insert(s, 1);
    cout << A << endl;
    cout << endl;
    for (int i = 0; i < A.GetCnt(); i++) {
        cout << i + 1 << ") " << A.Get(i) << endl;
        //cout << i+1 << ") " << A[i] << endl;
    }
}