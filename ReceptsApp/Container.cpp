#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <list>

template <typename T>
class MyBidirectionalList
{
	//юзинги лучше в приват или паблик кидать? (странный вопрос, наверное)

private:
	//не лучше ли структуру написать вне класса? Хотя, тогда она, по сути, будет public, а этого нам не нужно?
	struct Node //элемент списка
	{
		T _value;
		Node* _next; //след элемент списка
		Node* _prev; //пред элемент списка
		Node(T value, Node* prev, Node* next) : _value(value), _prev(prev), _next(next) {};
	};
	Node* head;
	Node* tail;

public:
	class BilistIterator;
	class const_BilistIterator;

	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using iterator = BilistIterator;
	using const_iterator = const_BilistIterator;
	using difference_type = std::ptrdiff_t;
	using size_type = std::size_t;

public:
	//Дефолтный конструктор
	MyBidirectionalList() : head(nullptr), tail(nullptr) {}

	//Конструктор копирования
	MyBidirectionalList(const MyBidirectionalList& ctorCopy)
	{
		tail = head = nullptr;
		Node* cur = ctorCopy.head;
		while (cur) //пока cur не nullptr
		{
			push_back(cur->_value);
			cur = cur->_next;
		}
		delete cur; //нужно ли удалять cur, если он и так стал nullptr?
	}

	//Конструктор перемещения
	MyBidirectionalList(MyBidirectionalList&& ctorMove) : head(ctorMove.head), tail(ctorMove.tail)
	{
		ctorMove.tail = ctorMove.head = nullptr;
	} //есть вопрос по конструктуру перемещения

	//Деструктор
	~MyBidirectionalList()
	{
		while (head)
		{
			Node* cur = head;
			head = head->_next;
			delete cur;
		}
	}

	//Копирующий оператор присваивания
	MyBidirectionalList& operator =(const MyBidirectionalList& assignCopy)
	{
		if (this != &assignCopy) {
			this->~MyBidirectionalList();
			new (this) MyBidirectionalList(assignCopy); //нашел, где-то в нете такую реализацию оператора присваивания, но вот эффективно ли это хз
		}
		return *this;
	}

	//Перемещающий оператор присваивания
	MyBidirectionalList& operator =(MyBidirectionalList&& assignMove)
	{
		if (this != &assignMove) {
			this->~MyBidirectionalList();
			new (this) MyBidirectionalList(move(assignMove)); //почему без move вызывается конструктор копирования, а не конструктор перемещения, ведь assignMove по сути является rvalue-ссылкой?
			assignMove.tail = assignMove.head = nullptr;
		}
		return *this;
	}

	iterator begin() const  //сделал const, потому что в ином случае не работает operator==
	{
		return iterator(head);
	}
	iterator end() const
	{
		return tail == nullptr ? nullptr : iterator(tail->_next);
	}
	const_iterator cbegin() const
	{
		return const_iterator(head);
	}
	const_iterator cend() const
	{
		return tail == nullptr ? nullptr : const_iterator(tail->_next);
	}

	const bool operator==(const MyBidirectionalList& other) const
	{
		if (this->size() == other.size())
		{
			for (iterator first1 = this->begin(), first2 = other.begin(), last1 = end(); first1 != last1; ++first1, ++first2) {
				if (!(*first1 == *first2)) {
					return false;
				}
			}
			return true;
		}
		else return false;
	}
	const bool operator!=(const MyBidirectionalList& other) const { return !(operator ==(other)); }

	size_type size() const { return std::distance(this->begin(), this->end()); }
	size_type max_size() const { return (size_type)-1; }	//Я знаю, что это скорее всего неверно, но как подругому узнать max_size я не знаю.
															//Можно конечно в бесконечном цикле это проверить, пока программа не сломается, но это долго

	bool empty() const { return this->begin() == this->end(); }

	//Меняет местами контейнеры *this и other
	void swap(MyBidirectionalList& other)
	{
		MyBidirectionalList<T> temp = move(*this);
		*this = move(other);
		other = move(temp);
	}

	//Добавление элемента со значение value в конец
	void push_back(T value)
	{
		Node* newElem = new Node(value, nullptr, nullptr);
		if (tail)
		{
			tail->_next = newElem;
			newElem->_prev = tail;
			tail = newElem;
			tail->_next = new Node(NULL, tail, nullptr); //фиктивный элемент для end()
		}
		else
		{
			tail = head = newElem;
			tail->_next = new Node(NULL, tail, nullptr); //фиктивный элемент для end()
		}
	}

public:
	//итератор - public или private?
	class BilistIterator;
	class const_BilistIterator
	{
	private:
		//а нужно ли в private кидать указатель на ноду? В list (#include <list>) нода в паблике находится
		Node* _ptr;
		friend class BilistIterator;

	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
	public:
		const_BilistIterator() : _ptr(nullptr) {}
		const_BilistIterator(Node* ptr) : _ptr(ptr) {}
		const_BilistIterator(const const_BilistIterator& it) : _ptr(it._ptr) {}
		~const_BilistIterator() = default;
		const_BilistIterator& operator=(const const_BilistIterator& it)
		{
			_ptr = it._ptr;
			return *this;
		}

		reference operator*() const { return _ptr->_value; } //здесь разве не нужно какую-нибудь проверку устраивать на то, если _ptr == nullptr?
		pointer operator->() const { return &(_ptr->_value); }

		const_BilistIterator& operator++()
		{
			if (_ptr)
				_ptr = _ptr->_next;
			return *this;
		}
		const const_BilistIterator operator++(int)
		{
			const_BilistIterator it(_ptr);
			++* this;
			return it;
		}
		const_BilistIterator& operator--()
		{
			if (_ptr)
				_ptr = _ptr->_prev;
			return *this;
		}
		const const_BilistIterator operator--(int)
		{
			const_BilistIterator it(_ptr);
			--* this;
			return it;
		}

		const bool operator==(const const_BilistIterator& it) const { return _ptr == it._ptr; }
		const bool operator!=(const const_BilistIterator& it) const { return _ptr != it._ptr; }

		void swap(BilistIterator& other)
		{
			BilistIterator temp = move(*this);
			*this = move(other);
			other = move(temp);
		}
	};

	class BilistIterator : public const_BilistIterator
	{
	public:
		using const_BilistIterator::_ptr;  //имеет ли значение напишу я так, или через #define?

		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

	public:
		BilistIterator() : const_BilistIterator() {}
		BilistIterator(Node* ptr) : const_BilistIterator(ptr) {}
		BilistIterator(const BilistIterator& it) : const_BilistIterator(it) {}
		~BilistIterator() = default;
		BilistIterator& operator=(const BilistIterator& it)
		{
			_ptr = it._ptr;
			return *this;
		}
		reference operator*() const { return _ptr->_value; } //здесь разве не нужно какую-нибудь проверку устраивать на то, если _ptr == nullptr?
		pointer operator->() const { return &(_ptr->_value); }

		BilistIterator& operator++()
		{
			if (_ptr)
				_ptr = _ptr->_next;
			return *this;
		}
		const BilistIterator operator++(int)
		{
			BilistIterator it(_ptr);
			++* this;
			return it;
		}
		BilistIterator& operator--()
		{
			if (_ptr)
				_ptr = _ptr->_prev;
			return *this;
		}
		const BilistIterator operator--(int)
		{
			BilistIterator it(_ptr);
			++* this;
			return it;
		}

		const bool operator==(const BilistIterator& it) const { return _ptr == it._ptr; }
		const bool operator!=(const BilistIterator& it) const { return _ptr != it._ptr; }
	};
};