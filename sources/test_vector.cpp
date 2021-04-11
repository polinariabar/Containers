#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../includes/tests/VectorTest.hpp"

/*
** ----------------------------------------------
**				Help functions
** ----------------------------------------------
*/

template <typename T>
void _fill_vector(VectorTest<T> &tmp, const T &value1, const T &value2, const T &value3)
{
	tmp.push_back(value1);
	tmp.push_back(value1);
	tmp.push_back(value2);
	tmp.push_back(value3);
	tmp.push_back(value3);
	tmp.push_back(value1);
	tmp.push_back(value1);
	tmp.push_back(value3);
	tmp.push_back(value3);
	tmp.push_back(value2);
}

template <typename T>
void _create_vectors(VectorTest<T> &tmp, VectorTest<T> &tmp2, const T &value1, const T &value2, const T &value3)
{
	_fill_vector(tmp, value1, value2, value3);
	tmp2.push_back(value2);
}

/*
** ----------------------------------------------
**				TEST functions
** ----------------------------------------------
*/

template <typename T>
void vector_constructor_test_template(int m, const T &value1, const T &value2, const T &value3)
{
	typename std::vector<T> tmp;
	typename std::vector<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		tmp.push_back(value1);
		tmp.push_back(value2);
		tmp.push_back(value3);
	}
	tmp_it = tmp.begin();
	for (int i = 0; i < 10; i++)
		tmp_it++;

	Test<T>::print_test(m, "constructors");
	std::cout << "Default:\n";
	VectorTest<T> tmp2 = VectorTest<T>();
	tmp2.test();
	std::cout << "Count(23):\n";
	VectorTest<T> tmp3 = VectorTest<T>(23);
	std::cout << "Count(12) + value:\n";
	VectorTest<T> test4 = VectorTest<T>(12, value1);
	std::cout << "Count(0) + value:\n";
	VectorTest<T> test5 = VectorTest<T>(0, value1);
	std::cout << "Count(0):\n";
	VectorTest<T> test6 = VectorTest<T>(0);
	std::cout << "Count(1) + value:\n";
	VectorTest<T> test7 = VectorTest<T>(1, value3);
	std::cout << "InputIt first, InputIt last:\n";
	VectorTest<T> test8 = VectorTest<T>(++tmp.begin(), tmp_it);
	std::cout << "Copy:\n";
	VectorTest<T> test9 = VectorTest<T>(test8);
	Test<T>::print_result(tmp2.get_result() && tmp3.get_result() && test4.get_result() &&
						  test5.get_result() && test6.get_result() && test7.get_result() &&
						  test8.get_result() && test9.get_result());
}

template <typename T>
void vector_resize_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "resize");
	std::cout << "Before resize:\n";
	VectorTest<T> tmp;
	tmp.test();
	std::cout << "(5, " << value1 << "):\n";
	tmp.resize_test(5, value1);
	std::cout << "(0, " << value1 << "):\n";
	tmp.resize_test(0, value1);
	std::cout << "(10, " << value2 << "):\n";
	tmp.resize_test(10, value2);
	std::cout << "(4, " << value1 << "):\n";
	tmp.resize_test(4, value1);
	std::cout << "(10):\n";
	tmp.resize_test(10);
	std::cout << "(15, " << value3 << "):\n";
	tmp.resize_test(15, value3);
	std::cout << "(1):\n";
	tmp.resize_test(1);
	tmp.print_result();
}

template <typename T>
void vector_push_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "push back");
	std::cout << "Before:\n";
	VectorTest<T> tmp;
	tmp.test();
	std::cout << "After pushes back:\n";
	tmp.push_back(value1);
	tmp.push_back(value1);
	tmp.push_back(value2);
	tmp.push_back(value3);
	tmp.push_back(value3);
	tmp.push_back(value3);
	tmp.push_back(value2);
	tmp.test();
	std::cout << "Pushing front to empty:\n";
	tmp.clear();
	tmp.test();
	tmp.push_back(value2);
	tmp.test();
	tmp.clear();
	std::cout << "Pushing back to empty:\n";
	tmp.test();
	tmp.push_back(value1);
	tmp.push_back(value1);
	tmp.push_back(value2);
	tmp.push_back(value3);
	tmp.push_back(value3);
	tmp.test();
	tmp.print_result();
}

template <typename T>
void vector_pop_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "pop back");
	tmp.pop_back_test();
	tmp2.pop_back_test();
	tmp3.pop_back_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template <typename T>
void vector_front_back_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "front and back");
	tmp2.front_back_test();
	tmp3.front_back_test();
	Test<T>::print_result(tmp2.get_result() && tmp3.get_result());
}

template <typename T>
void vector_empty_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "empty");
	tmp.empty_test();
	tmp2.empty_test();
	tmp3.empty_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template <typename T>
void vector_iterator_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<char>::print_test(i++, "iterator");
	tmp.iterator_test();
	tmp2.iterator_test();
	tmp3.iterator_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());

	Test<char>::print_test(i++, "const iterator");
	tmp2.const_iterator_test();
	tmp2.print_result();
}

template<typename T>
void vector_clear_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	_fill_vector(tmp, value1, value2, value3);

	Test<char>::print_test(i++, "clear");
	tmp.clear_test();
	tmp.clear_test();
	tmp.push_back(value1);
	tmp.clear_test();
	tmp.print_result();
}

template<typename T>
void vector_assign_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp2;
	_fill_vector(tmp2, value1, value2, value3);
	typename std::vector<T> tmp;
	typename std::vector<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		tmp.push_back(value1);
		tmp.push_back(value2);
		tmp.push_back(value3);
	}
	tmp_it = tmp.begin();
	for (int i = 0; i < 10; i++)
		tmp_it++;

	Test<T>::print_test(i++, "assign (count, value)");
	tmp2.assign_test(10, value1);
	tmp2.clear();
	tmp2.assign_test(5, value3);
	tmp2.print_result();

	Test<T>::print_test(i++, "assign (first, last)");
	tmp2.assign_test(++tmp.begin(), tmp_it);
	tmp2.clear();
	tmp2.assign_test(++tmp.begin(), --tmp_it);
	tmp2.print_result();
}

template <typename T>
void vector_operator_skoba_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "operator[]");
	tmp.operator_skoba_test();
	tmp2.operator_skoba_test();
	tmp3.operator_skoba_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template <typename T>
void vector_at_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "at");
	tmp.at_test();
	tmp2.at_test();
	tmp3.at_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template <typename T>
void vector_insert_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	typename std::vector<T> test;
	typename std::vector<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		test.push_back(value1);
		test.push_back(value2);
		test.push_back(value3);
	}
	tmp_it = test.begin();
	for (int i = 0; i < 10; i++)
		tmp_it++;

	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "insert (value)");
	tmp.insert_test(value1);
	tmp2.insert_test(value2);
	tmp3.insert_test(value3);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());

	Test<T>::print_test(i++, "insert (count, value)");
	tmp.insert_test(5, value3);
	tmp3.insert_test(1, value2);
	tmp2.insert_test(12, value1);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());

	Test<T>::print_test(i++, "insert (first, last)");
	tmp.insert_test(++test.begin(), tmp_it--);
	tmp.clear();
	tmp.insert_test(++test.begin(), tmp_it);
	tmp.print_result();
}

template <typename T>
void vector_reserve_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "reserve");
	std::cout << "Before resize:\n";
	VectorTest<T> tmp;
	VectorTest<T> tmp3;
	_create_vectors(tmp, tmp3, value1, value2, value3);
	(void)tmp3;
	tmp.test();
	std::cout << "(5):\n";
	tmp.reserve_test(5);
	std::cout << "(0):\n";
	tmp.reserve_test(0);
	std::cout << "(10):\n";
	tmp.reserve_test(10);
	std::cout << "(4):\n";
	tmp.reserve_test(4);
	std::cout << "(10):\n";
	tmp.reserve_test(10);
	std::cout << "(15):\n";
	tmp.reserve_test(15);
	std::cout << "(200):\n";
	tmp.reserve_test(200);
	tmp.print_result();
}

template <typename T>
void vector_erase_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	_fill_vector(tmp, value1, value2, value3);

	Test<T>::print_test(i++, "erase (pos)");
	tmp.erase_test();
	tmp.print_result();

	Test<T>::print_test(i++, "erase (first, last)");
	_fill_vector(tmp, value1, value2, value3);
	tmp.erase_test_first_last();
	tmp.print_result();
}

template <typename T>
void vector_swap_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_create_vectors(tmp2, tmp3, value1, value2, value3);

	Test<T>::print_test(i++, "swap");
	tmp2.swap_test(tmp3);
	tmp2.swap_test(tmp);
	tmp2.swap_test(tmp2);
	Test<T>::print_result(tmp2.get_result() && tmp3.get_result() && tmp.get_result());
}

template <typename T>
void vector_operators_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "operators");

	VectorTest<T> tmp;
	VectorTest<T> tmp2;
	VectorTest<T> tmp3;
	_fill_vector(tmp, value1, value2, value3);
	_fill_vector(tmp2, value3, value3, value3);
	_fill_vector(tmp, value3, value2, value2);

	tmp.oper_equial_test(tmp2);
	tmp.oper_equial_test(tmp);
	tmp2.clear();
	tmp.oper_equial_test(tmp2);
	tmp2.oper_equial_test(tmp);
	tmp2.oper_equial_test(tmp2);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result());
}

template<typename T>
void vector_max_size_test_template(int &i)
{
	Test<T>::print_test(i++, "max_size");
	VectorTest<T> tmp;
	tmp.max_size_test();
	tmp.print_result();
}

/*
** ----------------------------------------------
**				CALLER functions
** ----------------------------------------------
*/

template <typename T>
void vector_test(const T &value1, const T &value2, const T &value3)
{
	int i = 1;
	vector_constructor_test_template<T>(i++, value1, value2, value3);
	vector_resize_test_template<T>(i++, value1, value2, value3);
	vector_push_test_template<T>(i++, value1, value2, value3);
	vector_pop_test_template<T>(i++, value1, value2, value3);
	vector_front_back_test_template<T>(i++, value1, value2, value3);
	vector_empty_test_template<T>(i, value1, value2, value3);
	vector_iterator_test_template<T>(i, value1, value2, value3);
	vector_clear_test_template<T>(i, value1, value2, value3);
	vector_assign_test_template<T>(i, value1, value2, value3);
	vector_operator_skoba_test_template<T>(i, value1, value2, value3);
	vector_at_test_template<T>(i, value1, value2, value3);
	vector_insert_test_template<T>(i, value1, value2, value3);
	vector_reserve_test_template<T>(i++, value1, value2, value3);
	vector_erase_test_template<T>(i, value1, value2, value3);
	vector_swap_test_template<T>(i, value1, value2, value3);
	vector_operators_test_template<T>(i, value1, value2, value3);
	vector_max_size_test_template<T>(i);
}
