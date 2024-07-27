//doubly linked list (двухсвязный список)
#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------\n"

class Element //Описывает структуру элемента
{
	int Data;          //Значение элемента
	Element* pNext;    //Pointer to Next - указатель на следующий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList //односвязный список
{
	Element* Head; //Голова списка, указывает на начальный элемент списка
	unsigned int size; //Размер списка
public:
	int get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//Конструктор по умолчанию который создаёт пустой список
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(unsigned int size) : ForwardList() //explicit запрещает не явное преобразование типов
	{
		while (size--)push_front(0);
		/*for (int i = 0; i < size; i++)
		{
			push_front(rand() % 100);
		}*/
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; //Повторно используем код CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) : ForwardList()
	{
		*this = std::move(other); //Функция std::move() принудительно вызывает MoveAssignment для класса
		cout << "MoveConstructor:" << this << endl; //Конструктор перемещения
	}
	//Когда функция возвращает значение по значению
	//на месте вызова создаётся временный константный безымянный объект 
	//Когда существующий или создаваемый объект
	//инициализируется возвращаемым значением какой-то функции,
	//тогда неявно вызывается MoveAssignment, MoveConstructor
	~ForwardList()
	{
		while (Head)pop_front(); //Пока Head указывает на какой-то элемент (всё что не ноль true) цикл работает, на ноль - false конец. 
		/*for (int i = 0; i = size; i++)
		{
			pop_front();
		}*/
		cout << "LDestructor:\t" << this << endl;
	}

	//                 Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		//while (Head)pop_front();
		this->~ForwardList();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
	}

	const int& operator[](int index)const //Когда возврвщаем значение по значению
		//то на месте вызова создаётся временный безымянный объект, 
		//а временный безымянный объект по умолчанию константный, 
		//поэтому возвращаем по ссылке чтобы небыло ошибки C2106, E0137
		//Error	E0137 expression must be a modifiable lvalue	
		//Error	C2106	'=': left operand must be l - value	
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
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

	//               Removing elements:

	void pop_front()
	{
		if (Head == nullptr)return; //если возвращаемое значение void, то return просто прерывает работу функции и возвращает управление на место вызова
		//1)Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2)Исключаем удаляемый элемент из списка:
		Head = Erased->pNext;
		//3)Удаляем элемент из памяти:
		delete Erased;
		size--;
		/*new - создаёт объект в динамической памяти
		new[] - создаёт массив объектов в динамической памяти
		
		delete - удаляет один объект в динамической памяти
		delete[] - удаляет массив объектов из динамической памяти*/
	}

	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head; // В односвязный список можно зайти только через голову
		while (Temp->pNext->pNext)//В условии обращаемся к указателю pNext
			//элемента Temp, который указывает на pNext следующего элемента.
			//Если указатель pNext следующего элемента равен ноль,
			//то такого элемента нет, условие не выполняется.
			//pNext (указатель), pNext-> (элемент)
		{
			Temp = Temp->pNext; //Проходим по элементам списка
		}
		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		//3) Обнуляем указатель на последний элемент:
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int Data, int index) //Вставляет элемент по индексу
	{
		if (index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return push_front(Data);
		//if (index > size)return;
		Element* New = new Element(Data); //Выделяем память под новый элемент
		Element* Temp = Head; //Создаём итератор который будет указывать на текущий элемент в списке
		for (int i = 0; i < index - 1; i++) //идём по списку до элемента перед добавляемым
		{
			if (Temp->pNext == nullptr)break;
				Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext; //записываем в добавляемый элемент адрес следующего элемента
		Temp->pNext = New; //в текущий записываем добавляемый
		size++;
	}
	void erase(int index)
	{
		if (index > size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (index == 0)return pop_front();
		Element* Temp = Head;//Создаём итератор и начинаем идти по элементам с головы списка
		for (int i = 0; i < index - 1; i++)//Идём до нужного элемента
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext; // Сохраняем удаляемый элемент
		Temp->pNext = Temp->pNext->pNext; // убираем элемент из списка
		delete Erased;// удаляем элемент из памяти
		size--;
	}

	//                  Methods:
	void print()const
	{
		//Element* Temp = Head;   //Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.  
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //Переход на следующий элемент.
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer;
	for (int i = 0; i < left.get_size(); i++)buffer.push_back(left[i]);
	for (int i = 0; i < right.get_size(); i++)buffer.push_back(right[i]);
	return buffer;
}

//#define BASE_CHECK 
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	/*int n;
cout << "Введите количество элементов списка: "; cin >> n;
for (int i = 0; i < n; i++)
{
	list.push_front(rand() % 100);
}*/
	ForwardList list(7);
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
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(7);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	/*ForwardList list3 = list1 + list2;
	list3.print();
	list2 = list1 + list2;
	list3.print();*/
}