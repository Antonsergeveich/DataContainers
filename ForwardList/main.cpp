#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n------------------------------\n"

class Element
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

class ForwardList
{
	Element* Head; //Голова списка, указывает на начальный элемент списка
public:
	ForwardList()
	{
		//Конструктор по умолчанию который создаёт пустой список
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
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
	}
};

void main()
{
	setlocale(LC_ALL, "");
	ForwardList List;
}