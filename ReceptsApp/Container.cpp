#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <type_traits>
//#include "Container.h"



template <typename T>
class Container
{
	//юзинги лучше в приват или паблик кидать? (странный вопрос, наверное)
	//using iterator Iterator;
	/*using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using difference_type = std::ptrdiff_t;*/

private:
	//не лучше ли структуру написать вне класса?
	struct Elem //элемент списка
	{
		T _value;
		Elem* _next; //след элемент списка
		Elem* _prev; //пред элемент списка
		Elem() : _value(0), _next(nullptr), _prev(nullptr) {}
		Elem(T value, Elem* prev, Elem* next) : _value(value), _prev(prev), _next(next) {};
	};
	Elem* head;
	Elem* tail;

	////итератор - public или private?
	//class Iterator
	//{

	//};

public:
	Container() : head(nullptr), tail(nullptr) {};

	Container(const T& value)  //инициализация контейнера с одним элементом со значение value
	{
		head = new Elem(value, nullptr, nullptr);
		tail = head;
	}

	Container(const Container& contCopy) //конструктор копирования
	{
		tail = head = nullptr;
		Elem* cur = contCopy.head;
		while (cur)
		{
			push_back(cur->_value);
			cur = cur->_next;
		}
		delete cur; //есть ли смысл удалять, если cur и так уже nullptr?
	}

	~Container()
	{
		while (head)
		{
			Elem* cur = head;
			head = head->_next;
			delete cur;
		}
	}

	Container& operator =(const Container& contAssign)
	{
		if (this != &contAssign) {
			this->~Container();
			new (this) Container(contAssign);
			//head = contAssign.head;
			//tail = contAssign.tail;
		}
		return *this;
	}

	void push_back(T value)
	{
		Elem* newElem = new Elem(value, nullptr, nullptr);
		if (tail)
		{
			tail->_next = newElem;
			newElem->_prev = tail;
			tail = newElem;
		}
		else
		{
			tail = head = newElem;
		}
	}

};