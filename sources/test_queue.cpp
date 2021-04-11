#include <queue>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../includes/tests/QueueTest.hpp"

/*
** ----------------------------------------------
**				HELPER FUNCTIONS
** ----------------------------------------------
*/

template <typename T>
void _fill_queue(QueueTest<T> &tmp, const T &value1, const T &value2, const T &value3)
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
void _create_queues(QueueTest<T> &tmp, QueueTest<T> &tmp2, const T &value1, const T &value2, const T &value3)
{
	_fill_queue(tmp, value1, value2, value3);
	tmp2.push(value2);
}

/*
** ----------------------------------------------
**					TESTS
** ----------------------------------------------
*/

template <typename T>
void queue_constructor_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "constructors");
	std::cout << "Default:\n";
	QueueTest<T> tmp = QueueTest<T>();
	tmp.print_pop();
	std::cout << "Copy:\n";
	_fill_queue(tmp, value1, value2, value3);
	QueueTest<T> tmp2 = QueueTest<T>(tmp);
	std::cout << "output:\n";
	tmp.print_pop();
	tmp2.print_pop();
	Test<T>::print_result(tmp2.get_result() && tmp.get_result());
}

template <typename T>
void queue_push_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	QueueTest<T> tmp;

	Test<T>::print_test(i++, "push");
	std::cout << "push:\n";
	tmp.push_test(value1);
	std::cout << "back:\n";
	tmp.back_test();
	std::cout << "push:\n";
	tmp.push_test(value2);
	std::cout << "back:\n";
	tmp.back_test();
	std::cout << "push:\n";
	_fill_queue(tmp, value1, value2, value3);
	tmp.back_test();
	std::cout << "back:\n";
	tmp.back_test();
	std::cout << "output:\n";
	tmp.print_pop();
	tmp.print_result();
}

template <typename T>
void queue_pop_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	QueueTest<T> tmp;

	Test<T>::print_test(i++, "pop");
	std::cout << "pop:\n";
	tmp.push(value2);
	tmp.pop_test();
	std::cout << "pop:\n";
	_fill_queue(tmp, value1, value2, value3);
	tmp.pop_test();
	std::cout << "output:\n";
	tmp.print_pop();
	tmp.print_result();
}

template <typename T>
void queue_back_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	QueueTest<T> tmp;

	Test<T>::print_test(i++, "back");
	tmp.push(value2);
	tmp.back_test();
	_fill_queue(tmp, value1, value2, value3);
	tmp.back_test();
	tmp.print_result();
}

template <typename T>
void queue_front_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	QueueTest<T> tmp;

	Test<T>::print_test(i++, "front");
	tmp.push(value2);
	tmp.front_test();
	_fill_queue(tmp, value1, value2, value3);
	tmp.front_test();
	tmp.print_result();
}

template <typename T>
void queue_empty_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	QueueTest<T> tmp;
	Test<T>::print_test(i++, "empty");

	tmp.empty_test();
	tmp.push(value2);
	tmp.empty_test();
	tmp.pop();
	tmp.empty_test();
	_fill_queue(tmp, value1, value2, value3);
	tmp.empty_test();
	tmp.print_result();
}

template <typename T>
void queue_operators_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	QueueTest<T> tmp;
	QueueTest<T> tmp2;
	QueueTest<T> tmp3;
	_create_queues(tmp2, tmp3, value1, value2, value3);
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
void queue_test(const T &value1, const T &value2, const T &value3)
{
	int i = 1;
	queue_constructor_test_template<T>(i, value1, value2, value3);
	queue_push_test_template<T>(i, value1, value2, value3);
	queue_pop_test_template<T>(i, value1, value2, value3);
	queue_front_test_template<T>(i, value1, value2, value3);
	queue_back_test_template<T>(i, value1, value2, value3);
	queue_empty_test_template<T>(i, value1, value2, value3);
	queue_operators_test_template<T>(i, value1, value2, value3);
}

