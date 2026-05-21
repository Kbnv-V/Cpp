#include <iostream>
using namespace std;

//реализация односвязного списка

template <typename T>
class List
{
public:
    List();
    ~List();

    void pushBack(T data); //метод для добавления элемента к конец списка
    void popFront(); //метод для удаления первого элемента списка
    void clear(); //метод для очистки всего списка
    void pushFront(T data); //метод для добавления элемента в конец списка
    void insert(T data, int index); //метод для добавления в список по индексу
    void removeAt(int index); //метод для удаления элемента по интексу
    void popBack(); //метод для удаления последнего элемента списка
    
    //метод возвращает кол-во элементов в списке
    int GetSize()
    {
        return size;
    }

    T& operator[](const int index);

private:

    //класс Node тоже будет шаблонным, так как в объектах могут хранится различные данныеы
    template <typename T>
    class Node //это класс для элементов списка
    {
    public:
        Node* pAdressNextElement; //указатель на следующий элемент
        T data;
        
        Node(T data = T(), Node* nextAdress = nullptr) //T data = T() это так предотваращется передача пустого значения
        {
            this->data = data;
            this->pAdressNextElement = nextAdress;
        }
    };

    Node<T> *head;
    int size;
};

//у методов и конструкторов, которые выносятся за класс, надо писать тип данных через template
template<typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::pushBack(T data)
{
    if (head == nullptr)
    {
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* current = this->head;
        
        while (current->pAdressNextElement != nullptr)
        {
            current = current->pAdressNextElement;
        }

        current->pAdressNextElement = new Node<T>(data);
    }

    size++; //после добавления увеличиваем счетчик элементов
}


template <typename T>
void List<T>::popFront()
{
    Node<T>* temp = head;

    head = head->pAdressNextElement;

    delete temp;

    size--;

}

template <typename T>
void List<T>::clear()
{
    while (size)
    {
        popFront();//для удаления всех элементов можно просто вызывать функцию для удаления первого элемента
    }
}

template<typename T>
void List<T>::pushFront(T data)
{
    head = new Node<T>(data, head);
    size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
    if (index == 0)
    {
        pushFront(data);
    }
    else
    {
        Node<T>* current = this->head;

        for (int i = 0; i < index - 1; i++)
        {
            current = current->pAdressNextElement;
        }

        Node<T>* newNode = new Node<T>(data, current->pAdressNextElement);
        current->pAdressNextElement = newNode;

        size++;
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    if (index == 0)
    {
        popFront();
    }
    else
    {
        Node<T>* current = this->head;

        for (int i = 0; i < index - 1; i++)
        {
            current = current->pAdressNextElement;
        }

        Node<T>* toDelete = current->pAdressNextElement; //тут значение 2 индекса
        current->pAdressNextElement = toDelete->pAdressNextElement;

        delete toDelete;

        size--;
    }
}

template <typename T>
void List<T>::popBack()
{
    removeAt(size - 1);
}

template <typename T>
T& List<T>::operator[](const int index)
{
    Node<T>* current = this->head;
    int count = 0;

    while (current != nullptr)
    {
        if (count == index)
        {
            return current->data;
        }

        current = current->pAdressNextElement;
        
        count++;
    }
}


int main()
{
    setlocale(LC_ALL, "RU");

    List<int> list;

    list.pushBack(1);
    list.pushBack(11523);
    list.pushBack(12552);

    //cout << list.GetSize() << endl;

    //list.popFront();

    //list.clear();

    list.pushFront(105);

    list.insert(222, 2);

    list.removeAt(2);
    
    list.popBack();
    //cout << list[2] << endl;


}
