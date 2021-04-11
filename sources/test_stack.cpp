#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../includes/tests/StackTest.hpp"

/*
** ----------------------------------------------
**				HELPER FUNCTIONS
** ----------------------------------------------
*/

template <typename T>
void _fill_stack(StackTest<T> &tmp, const T &value1, const T &value2, const T &value3)
{
	tmp.push(value1);
	tmp.push(value1);
	tmp.push(value2);
	tmp.push(value3);
	tmp.push(value3);
	tmp.push(value1);
	tmp.push(value1);
	tmp.push(value3);
	tmp.push(value3);
	tmp.push(value2);
}

template <typename T>
void _create_stacks(StackTest<T> &tmp, StackTest<T> &tmp2, const T &value1, const T &value2, const T &value3)
{
	_fill_stack(tmp, value1, value2, value3);
	tmp2.push(value2);
}

/*
** ----------------------------------------------
**					TESTS
** ----------------------------------------------
*/

template <typename T>
void stack_constructor_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "constructors");
	std::cout << "Default:\n";
	StackTest<T> tmp = StackTest<T>();
	tmp.print_pop();
	std::cout << "Copy:\n";
	_fill_stack(tmp, value1, value2, value3);
	StackTest<T> tmp2 = StackTest<T>(tmp);
	std::cout << "output:\n";
	tmp.print_pop();
	tmp2.print_pop();
	Test<T>::print_result(tmp2.get_result() && tmp.get_result());
}

template <typename T>
void stack_push_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	StackTest<T> tmp;

	Test<T>::print_test(i++, "push");
	std::cout << "push:\n";
	tmp.push_test(value1);
	std::cout << "top:\n";
	tmp.top_test();
	std::cout << "push:\n";
	tmp.push_test(value2);
	std::cout << "top:\n";
	tmp.top_test();
	std::cout << "push:\n";
	_fill_stack(tmp, value1, value2, value3);
	tmp.top_test();
	std::cout << "top:\n";
	tmp.top_test();
	std::cout << "output:\n";
	tmp.print_pop();
	tmp.print_result();
}

template <typename T>
void stack_pop_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	StackTest<T> tmp;

	Test<T>::print_test(i++, "pop");
	std::cout << "pop:\n";
	tmp.push(value2);
	tmp.pop_test();
	std::cout << "pop:\n";
	_fill_stack(tmp, value1, value2, value3);
	tmp.pop_test();
	std::cout << "output:\n";
	tmp.print_pop();
	tmp.print_result();
}

template <typename T>
void stack_top_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	StackTest<T> tmp;

	Test<T>::print_test(i++, "top");
	tmp.push(value2);
	tmp.top_test();
	_fill_stack(tmp, value1, value2, value3);
	tmp.top_test();
	tmp.print_result();
}

template <typename T>
void stack_empty_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	StackTest<T> tmp;
	Test<T>::print_test(i++, "empty");

	tmp.empty_test();
	tmp.push(value2);
	tmp.empty_test();
	tmp.pop();
	tmp.empty_test();
	_fill_stack(tmp, value1, value2, value3);
	tmp.empty_test();
	tmp.print_result();
}

template <typename T>
void stack_operators_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	StackTest<T> tmp;
	StackTest<T> tmp2;
	StackTest<T> tmp3;
	_create_stacks(tmp2, tmp3, value1, value2, value3);
	Test<T>::print_test(i++, "operators");

	std::cout << "output:\n";
	tmp.print_pop();
	tmp2.print_pop();
	tmp3.print_pop();

	std::cout << "results:\n";
	tmp.operators_test(tmp2);
	tmp.operators_test(tmp3);
	tmp2.operators_test(tmp3);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}


/*
** ----------------------------------------------
**				CALLER functions
** ----------------------------------------------
*/

template <typename T>
void stack_test(const T &value1, const T &value2, const T &value3)
{
	int i = 1;
	stack_constructor_test_template<T>(i, value1, value2, value3);
	stack_push_test_template<T>(i, value1, value2, value3);
	stack_pop_test_template<T>(i, value1, value2, value3);
	stack_top_test_template<T>(i, value1, value2, value3);
	stack_empty_test_template<T>(i, value1, value2, value3);
	stack_operators_test_template<T>(i, value1, value2, value3);
}

