//doubly linked list (двухсвязный список)
#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n------------------------------\n"

class Element //Описывает структуру элемента
{
	int Data;          //Значение элемента
	Element* pNext;    //Pointer to Next - указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList //односвязный список
{
	Element* Head; //Голова списка, указывает на начальный элемент списка
	unsigned int size; //Размер списка
public:
	ForwardList()
	{
		//Конструктор по умолчанию который создаёт пустой список
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size):ForwardList()
	{
		for (int i = 0; i < size; i++)
		{
			push_front(rand() % 100);
		}
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//            Adding elements (добавление элемента): 
	void push_front(int Data)
	{
		//1) Создаём новый элемент:
		Element* New = new Element(Data); //оператор new вызывает конструктор класса

		//2) Пристыковываем новый элемент к началу списка:
		New->pNext = Head;

		//3) Голову перенаправляем на новый элемент:
		Head = New;

		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data); //если список пустой, добавляем элемент вначало списка
		Element* New = new Element(Data); //Создаём новый элемент
		Element* Temp = Head; //Создаём указатель на текущий элемент
		while (Temp->pNext)//Пока текущий элемент не указывает на ноль переходим на следующий элемент списка
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;// После того как мы оказались в конце списка, можно добавлять новый элемент
		size++;
	}

	void pop_front()
	{
		if (Head == nullptr)return;
		Element* buffer = Head;
		Head = buffer->pNext;
		delete buffer;
		size--;
	}

	void pop_back()
	{
		if (Head == nullptr)return;
		Element* Temp = Head;
		while (Temp->pNext->pNext)//В условии обращаемся к указателю pNext
	    //элемента Temp, который указывает на pNext следующего элемента.
	    //Если указатель pNext следующего элемента равен ноль,
		//то такого элемента нет, условие не выполняется.
		{
			Temp = Temp->pNext; //Проходим по элементам списка
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int Data, int index) //Вставляет элемент по индексу
	{
		if (index > size)return;
		Element* New = new Element(Data); //Выделяем память под новый элемент
		Element* Temp = Head; //Создаём итератор который будет указывать на текущий элемент в списке
		for (int i = 0; i < index - 1; i++) // идём по списку до элемента перед добавляемым
		{
			Temp = Temp->pNext; 
		}
		New->pNext = Temp->pNext; // записываем в добавляемый элемент адрес следующего элемента
		Temp->pNext = New; // в текущий записываем добавляем
		size++;
	}

	//                  Methods:
	void print()const
	{
		Element* Temp = Head;   //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.  
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	/*int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}*/
	ForwardList list(5);
	list.print();
	list.push_front(5);
	list.push_back(8);
	list.print();
	list.pop_front();
	list.pop_back();
	list.print();
	cout << endl;
	list.insert(123,1);
	list.print();
}