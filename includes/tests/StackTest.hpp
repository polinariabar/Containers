#pragma once

#include "Tests.hpp"

#define CORRECT true
#define ERROR	false

template <typename T>
class StackTest : public Test<T>::Test
{
public:
	std::stack<T>		_or_stack;
	ft::stack<T>		_my_stack;

private:
	std::string			_or_str;
	std::string			_my_str;

public:
	StackTest();
	StackTest(const StackTest<T> & other);

	void				compare();
	void				print_pop();

	void				empty_test();
	void				top_test();
	void				push_test(const T & value);
	void				pop_test();
	void				operators_test(StackTest<T> & other);

	void				pop();
	void				push(const T & value);
};

/*
** ------------------------------------------------------------
**         					Constructors
** ------------------------------------------------------------
*/

template <typename T>
StackTest<T>::StackTest()
{
	_or_stack = std::stack<T>();
	_my_stack = ft::stack<T>();
}

template <typename T>
StackTest<T>::StackTest(const StackTest<T> & other)
{
	_or_stack = std::stack<T>(other._or_stack);
	_my_stack = ft::stack<T>(other._my_stack);
}

/*
** ------------------------------------------------------------
**        						Helpers
** ------------------------------------------------------------
*/

template <typename T>
void StackTest<T>::compare()
{
	std::cout << "ft  |" << _my_stack.size() << "| " << _my_str << std::endl
			  << "std |" << _or_stack.size() << "| " << _or_str << std::endl;
	this->print_error(_my_stack.size() == _or_stack.size() && !_my_str.compare(_or_str));
}

template <typename T>
void StackTest<T>::print_pop()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	size_t size = _or_stack.size();

	while (size--)
	{
		my_ss << _my_stack.top() << " ";
		or_ss << _or_stack.top() << " ";
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
void StackTest<T>::push(const T &value)
{
	_my_stack.push(value);
	_or_stack.push(value);
}

template <typename T>
void StackTest<T>::pop()
{
	_my_stack.pop();
	_or_stack.pop();
}

/*
** ------------------------------------------------------------
**      	 				 Tests
** ------------------------------------------------------------
*/

template <typename T>
void StackTest<T>::empty_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_stack.empty();
	or_ss << _or_stack.empty();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void StackTest<T>::top_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_stack.top();
	or_ss << _or_stack.top();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void StackTest<T>::push_test(const T & value)
{
	push(value);
	compare();
}


template <typename T>
void StackTest<T>::pop_test()
{
	pop();
	compare();
}

template <typename T>
void StackTest<T>::operators_test(StackTest<T> &other)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	or_ss << "  ==: " << (_or_stack == other._or_stack) << " swap " << (other._or_stack == _or_stack) << " | ";
	my_ss << "  ==: " << (_my_stack == other._my_stack) << " swap " << (other._my_stack == _my_stack) << " | ";

	or_ss << "!=: " << (_or_stack != other._or_stack) << " swap " << (other._or_stack != _or_stack) << " | ";
	my_ss << "!=: " << (_my_stack != other._my_stack) << " swap " << (other._my_stack != _my_stack) << " | ";

	or_ss << "<: " << (_or_stack < other._or_stack) << " swap " << (other._or_stack < _or_stack) << " | ";
	my_ss << "<: " << (_my_stack < other._my_stack) << " swap " << (other._my_stack < _my_stack) << " | ";

	or_ss << ">: " << (_or_stack > other._or_stack) << " swap " << (other._or_stack > _or_stack) << " | ";
	my_ss << ">: " << (_my_stack > other._my_stack) << " swap " << (other._my_stack > _my_stack) << " | ";

	or_ss << "<=: " << (_or_stack <= other._or_stack) << " swap " << (other._or_stack <= _or_stack) << " | ";
	my_ss << "<=: " << (_my_stack <= other._my_stack) << " swap " << (other._my_stack <= _my_stack) << " | ";

	or_ss << ">=: " << (_or_stack >= other._or_stack) << " swap " << (other._or_stack >= _or_stack) << " | ";
	my_ss << ">=: " << (_my_stack >= other._my_stack) << " swap " << (other._my_stack >= _my_stack) << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-----------------\n";
}