#pragma once

#include "Tests.hpp"

#define CORRECT true
#define ERROR	false

template <typename T>
class QueueTest : public Test<T>::Test
{
public:
	std::queue<T>		_or_queue;
	ft::queue<T>		_my_queue;

private:
	std::string			_or_str;
	std::string			_my_str;

public:
	QueueTest();
	QueueTest(const QueueTest<T> & other);

	void				compare();
	void				print_pop();

	void				empty_test();
	void				front_test();
	void				back_test();
	void				push_test(const T & value);
	void				pop_test();
	void				operators_test(QueueTest<T> & other);

	void				pop();
	void				push(const T & value);
};

/*
** ------------------------------------------------------------
**         					Constructors
** ------------------------------------------------------------
*/

template <typename T>
QueueTest<T>::QueueTest()
{
	_or_queue = std::queue<T>();
	_my_queue = ft::queue<T>();
}

template <typename T>
QueueTest<T>::QueueTest(const QueueTest<T> & other)
{
	_or_queue = std::queue<T>(other._or_queue);
	_my_queue = ft::queue<T>(other._my_queue);
}

/*
** ------------------------------------------------------------
**        						Helpers
** ------------------------------------------------------------
*/

template <typename T>
void QueueTest<T>::compare()
{
	std::cout << "ft  |" << _my_queue.size() << "| " << _my_str << std::endl
			  << "std |" << _or_queue.size() << "| " << _or_str << std::endl;
	this->print_error(_my_queue.size() == _or_queue.size() && !_my_str.compare(_or_str));
}

template <typename T>
void QueueTest<T>::print_pop()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	size_t size = _or_queue.size();

	while (size--)
	{
		my_ss << _my_queue.back() << " ";
		or_ss << _or_queue.back() << " ";
		pop();
	}

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

/*
** ------------------------------------------------------------
**      					 Methods
** ------------------------------------------------------------
*/

template <typename T>
void QueueTest<T>::push(const T &value)
{
	_my_queue.push(value);
	_or_queue.push(value);
}

template <typename T>
void QueueTest<T>::pop()
{
	_my_queue.pop();
	_or_queue.pop();
}

/*
** ------------------------------------------------------------
**      	 				 Tests
** ------------------------------------------------------------
*/

template <typename T>
void QueueTest<T>::empty_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_queue.empty();
	or_ss << _or_queue.empty();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void QueueTest<T>::front_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_queue.front();
	or_ss << _or_queue.front();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void QueueTest<T>::back_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_queue.back();
	or_ss << _or_queue.back();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void QueueTest<T>::push_test(const T & value)
{
	push(value);
	compare();
}


template <typename T>
void QueueTest<T>::pop_test()
{
	pop();
	compare();
}

template <typename T>
void QueueTest<T>::operators_test(QueueTest<T> &other)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	or_ss << "  ==: " << (_or_queue == other._or_queue) << " swap " << (other._or_queue == _or_queue) << " | ";
	my_ss << "  ==: " << (_my_queue == other._my_queue) << " swap " << (other._my_queue == _my_queue) << " | ";

	or_ss << "!=: " << (_or_queue != other._or_queue) << " swap " << (other._or_queue != _or_queue) << " | ";
	my_ss << "!=: " << (_my_queue != other._my_queue) << " swap " << (other._my_queue != _my_queue) << " | ";

	or_ss << "<: " << (_or_queue < other._or_queue) << " swap " << (other._or_queue < _or_queue) << " | ";
	my_ss << "<: " << (_my_queue < other._my_queue) << " swap " << (other._my_queue < _my_queue) << " | ";

	or_ss << ">: " << (_or_queue > other._or_queue) << " swap " << (other._or_queue > _or_queue) << " | ";
	my_ss << ">: " << (_my_queue > other._my_queue) << " swap " << (other._my_queue > _my_queue) << " | ";

	or_ss << "<=: " << (_or_queue <= other._or_queue) << " swap " << (other._or_queue <= _or_queue) << " | ";
	my_ss << "<=: " << (_my_queue <= other._my_queue) << " swap " << (other._my_queue <= _my_queue) << " | ";

	or_ss << ">=: " << (_or_queue >= other._or_queue) << " swap " << (other._or_queue >= _or_queue) << " | ";
	my_ss << ">=: " << (_my_queue >= other._my_queue) << " swap " << (other._my_queue >= _my_queue) << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-----------------\n";
}