#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../includes/tests/ListTest.hpp"

template <typename T>
bool	compare(const T & a, const T & b) {return (a < b);}

template <typename T>
bool	compare_m(const T & a, const T & b) {return (a + 20 < b);}

template <typename T>
bool	to_remove(const T a) { return (a < '9'); }

template <typename T>
bool	compare_uni(const T & a, const T & b) {return (a == b);}


template <typename T>
void list_constructor_test_template(int m, const T &value1, const T &value2, const T &value3)
{
	typename std::list<T> tmp;
	typename std::list<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		tmp.push_back(value1);
		tmp.push_front(value2);
		tmp.push_back(value3);
	}
	tmp_it = tmp.begin();
	for (int i = 0; i < 10; i++)
		tmp_it++;

	Test<T>::print_test(m, "constructors");
	std::cout << "Default:\n";
	ListTest<T> tmp2 = ListTest<T>();
	tmp2.test();
	std::cout << "Count(23):\n";
	ListTest<T> tmp3 = ListTest<T>(23);
	std::cout << "Count(12) + value:\n";
	ListTest<T> test4 = ListTest<T>(12, value1);
	std::cout << "Count(0) + value:\n";
	ListTest<T> test5 = ListTest<T>(0, value1);
	std::cout << "Count(0):\n";
	ListTest<T> test6 = ListTest<T>(0);
	std::cout << "Count(1) + value:\n";
	ListTest<T> test7 = ListTest<T>(1, value3);
	std::cout << "InputIt first, InputIt last:\n";
	ListTest<T> test8 = ListTest<T>(++tmp.begin(), tmp_it);
	std::cout << "Copy:\n";
	ListTest<T> test9 = ListTest<T>(test8);
	Test<T>::print_result(tmp2.get_result() && tmp3.get_result() && test4.get_result() &&
						  test5.get_result() && test6.get_result() && test7.get_result() && 
						  test8.get_result() && test9.get_result());
}

template <typename T>
void list_resize_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "resize");
	std::cout << "Before resize:\n";
	ListTest<T> tmp;
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

template<typename T>
void list_push_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "push back and front");
	std::cout << "Before:\n";
	ListTest<T> tmp;
	tmp.test();
	std::cout << "After pushes back and front:\n";
	tmp.push_back(value1);
	tmp.push_front(value1);
	tmp.push_front(value2);
	tmp.push_back(value3);
	tmp.push_front(value3);
	tmp.push_front(value3);
	tmp.push_back(value2);
	tmp.test();
	std::cout << "Pushing front to empty:\n";
	tmp.clear();
	tmp.test();
	tmp.push_front(value2);
	tmp.test();
	tmp.clear();
	std::cout << "Pushing back and front to empty:\n";
	tmp.test();
	tmp.push_back(value1);
	tmp.push_front(value1);
	tmp.push_front(value2);
	tmp.push_back(value3);
	tmp.push_front(value3);
	tmp.test();
	tmp.print_result();
}

template<typename T>
void _fill_list(ListTest<T> &tmp, const T &value1, const T &value2, const T &value3)
{
	tmp.push_back(value1);
	tmp.push_front(value1);
	tmp.push_front(value2);
	tmp.push_back(value3);
	tmp.push_front(value3);
	tmp.push_back(value1);
	tmp.push_front(value1);
	tmp.push_front(value3);
	tmp.push_back(value3);
	tmp.push_front(value2);
}

template<typename T>
void list_pop_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp2, value1, value2, value3);
	tmp3.push_front(value1);

	Test<T>::print_test(i++, "pop back and front");
	tmp.pop_back_front_test();
	tmp2.pop_back_front_test();
	tmp3.pop_back_front_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template<typename T>
void list_front_back_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp2, value1, value2, value3);
	tmp3.push_front(value1);

	Test<T>::print_test(i++, "front and back");
	tmp.test();
	tmp.front_back_test();
	tmp2.test();
	tmp2.front_back_test();
	tmp3.test();
	tmp3.front_back_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template<typename T>
void list_empty_test_template(int i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp2, value1, value2, value3);
	tmp3.push_front(value1);

	Test<T>::print_test(i++, "empty");
	tmp.empty_test();
	tmp2.empty_test();
	tmp3.empty_test();
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template<typename T>
void list_iterator_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp2, value1, value2, value3);
	tmp3.push_front(value1);

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
void list_insert_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	typename std::list<T> test;
	typename std::list<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		test.push_back(value1);
		test.push_front(value2);
		test.push_back(value3);
	}
	tmp_it = test.begin();
	for (int i = 0; i < 10; i++)
		tmp_it++;

	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp2, value1, value2, value3);
	tmp3.push_front(value1);

	Test<T>::print_test(i++, "insert (value)");
	tmp.insert_test(value1);
	tmp2.insert_test(value2);
	tmp3.insert_test(value3);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());

	Test<T>::print_test(i++, "insert (count, vaue)");
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

template<typename T>
void list_erase_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	typename std::list<T> tmp;
	typename std::list<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		tmp.push_back(value1);
		tmp.push_front(value2);
		tmp.push_back(value3);
	}
	tmp_it = tmp.begin();
	for (int i = 0; i < 10; i++)
		tmp_it++;

	Test<T>::print_test(i++, "erase(pos)");
	ListTest<T> test9(++tmp.begin(), tmp_it);
	test9.erase_test();
	test9.print_result();

	Test<char>::print_test(i++, "erase(first, last)");
	test9.push_front(value1);
	test9.push_back(value3);
	test9.erase_test_first_last();
	test9.print_result();
}

template<typename T>
void list_clear_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	_fill_list(tmp, value1, value2, value3);

	Test<char>::print_test(i++, "clear");
	tmp.clear_test();
	tmp.clear_test();
	tmp.push_back(value1);
	tmp.clear_test();
	tmp.print_result();
}

template<typename T>
void list_swap_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp2, value1, value2, value3);
	tmp.push_front(value1);
	tmp.push_front(value2);
	tmp.push_front(value3);

	Test<T>::print_test(i++, "swap");
	tmp.swap_test(tmp2);
	tmp.swap_test(tmp3);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result() && tmp3.get_result());
}

template<typename T>
void list_assign_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp2;
	_fill_list(tmp2, value1, value2, value3);
	typename std::list<T> tmp;
	typename std::list<T>::iterator tmp_it;
	for (int i = 0; i < 5; i++)
	{
		tmp.push_back(value1);
		tmp.push_front(value2);
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

template<typename T>
void list_sort_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	_fill_list(tmp, value1, value2, value3);

	Test<char>::print_test(i++, "sort");
	tmp.sort_test();
	tmp.clear();
	tmp.sort_test();
	tmp.push_front(value1);
	tmp.sort_test();
	tmp.push_back(value2);
	tmp.sort_test();
	tmp.print_result();

	// 
	// 	Test<char>::print_test(i++, "sort (comparison function)");
	// 	_fill_list(tmp, value1, value2, value3);
	// 	tmp.sort_test(compare<char>);
	// 	tmp.clear();
	// 	tmp.sort_test(compare<char>);
	// 	tmp.push_front(value1);
	// 	tmp.sort_test(compare<char>);
	// 	tmp.push_front(value3);
	// 	tmp.sort_test(compare<char>);
	// 	tmp.print_result();
	// 
}

template<typename T>
void list_reverse_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	Test<char>::print_test(i++, "reverse");
	std::cout << "0 size:\n";
	tmp.reverse_test();
	std::cout << "1 size:\n";
	tmp.push_front(value1);
	tmp.reverse_test();
	std::cout << "2 size:\n";
	tmp.push_back(value2);
	tmp.reverse_test();
	std::cout << "even size:\n";
	_fill_list(tmp, value1, value2, value3);
	tmp.reverse_test();
	std::cout << "odd size:\n";
	tmp.push_front(value3);
	tmp.reverse_test();
	tmp.print_result();
}

template<typename T>
void list_splice_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	_fill_list(tmp, value1, value2, value3);
	_fill_list(tmp2, value1, value2, value2);

	Test<T>::print_test(i++, "splice (pos, list)");
	tmp.splice_test(tmp2);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result());

	Test<char>::print_test(i++, "splice (pos, list, it)");
	_fill_list(tmp, value2, value3, value3);
	_fill_list(tmp2, value2, value1, value1);
	tmp.splice_test(tmp2, true);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result());

	Test<T>::print_test(i++, "splice (pos, list, first, last)");
	tmp.splice_test(tmp2, false);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result());
}

template<typename T>
void list_remove_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	_fill_list(tmp, value1, value2, value3);
	_fill_list(tmp2, value3, value3, value3);

	Test<T>::print_test(i++, "remove");
	tmp.remove_test(value3);
	_fill_list(tmp, value1, value1, value1);
	tmp.remove_test(value1);
	tmp2.remove_test(value3);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result());

	// if (!std::is_same<T, std::string>::value)
	// {
	// 	Test<T>::print_test(i++, "remove_if");
	// 	_fill_list(tmp, value1, value2, value3);
	// 	tmp.remove_if_test(to_remove<T>);
	// 	tmp.remove_if_test(to_remove<T>);
	// 	tmp.print_result();
	// }
}

template<typename T>
void list_unique_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	_fill_list(tmp, value1, value2, value3);
	_fill_list(tmp2, value3, value3, value3);


	Test<char>::print_test(i++, "unique");
	tmp.unique_test();
	tmp.unique_test();
	tmp2.unique_test();
	Test<char>::print_result(tmp.get_result() && tmp2.get_result());

	// if (!std::is_same<T, std::string>::value)
	// {
	// 	Test<char>::print_test(i++, "unique (function)");
	// 	_fill_list(tmp, value3, value3, value3);
	// 	_fill_list(tmp2, value2, value2, value2);
	// 	tmp.unique_test(compare_uni<char>);
	// 	tmp.unique_test(compare_uni<char>);
	// 	tmp2.unique_test(compare_uni<char>);
	// 	Test<char>::print_result(tmp.get_result() && tmp2.get_result());
	// }
}

template<typename T>
void list_merge_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp, value1, value2, value3);
	_fill_list(tmp2, value3, value3, value3);
	_fill_list(tmp, value3, value2, value2);

	Test<char>::print_test(i++, "merge (other)");
	tmp.sort();
	tmp2.sort();
	tmp.merge_test(tmp2);
	tmp.merge_test(tmp2);
	tmp2.merge_test(tmp);
	tmp.merge_test(tmp3);
	Test<char>::print_result(tmp.get_result() && tmp2.get_result());

	// if (!std::is_same<T, std::string>::value)
	// {
	// 	Test<char>::print_test(i++, "merge (other, comp)");
	// 	tmp2.sort();
	// 	_fill_list(tmp2, value3, value3, value3);
	// 	_fill_list(tmp, value1, value2, value3);
	// 	tmp.sort();
	// 	tmp.merge_test(tmp2, compare_m<char>);
	// 	tmp.merge_test(tmp2, compare_m<char>);
	// 	tmp2.merge_test(tmp, compare_m<char>);
	// 	tmp.merge_test(tmp3, compare_m<char>);
	// 	Test<char>::print_result(tmp.get_result() && tmp2.get_result());
	// }
}

template<typename T>
void list_operators_test_template(int &i, const T &value1, const T &value2, const T &value3)
{
	Test<T>::print_test(i++, "operators");

	ListTest<T> tmp;
	ListTest<T> tmp2;
	ListTest<T> tmp3;
	_fill_list(tmp, value1, value2, value3);
	_fill_list(tmp2, value3, value3, value3);
	_fill_list(tmp, value3, value2, value2);

	tmp.oper_equial_test(tmp2);
	tmp.oper_equial_test(tmp);
	tmp2.clear();
	tmp.oper_equial_test(tmp2);
	tmp2.oper_equial_test(tmp);
	tmp2.oper_equial_test(tmp2);
	Test<T>::print_result(tmp.get_result() && tmp2.get_result());
}

template<typename T>
void list_max_size_test_template(int &i)
{
	Test<T>::print_test(i++, "max_size");
	ListTest<T> tmp;
	tmp.max_size_test();
	tmp.print_result();
}

template<typename T>
void list_test(const T & value1, const T & value2, const T & value3)
{
	int i = 1;
	list_constructor_test_template<T>(i++, value1, value2, value3);
	list_resize_test_template<T>(i++, value1, value2, value3);
	list_push_test_template<T>(i++, value1, value2, value3);
	list_pop_test_template<T>(i++, value1, value2, value3);
	list_front_back_test_template<T>(i++, value1, value2, value3);
	list_empty_test_template<T>(i, value1, value2, value3);
	list_iterator_test_template<T>(i, value1, value2, value3);
	list_insert_test_template<T>(i, value1, value2, value3);
	list_erase_test_template<T>(i, value1, value2, value3);
	list_clear_test_template<T>(i, value1, value2, value3);
	list_swap_test_template<T>(i, value1, value2, value3);
	list_assign_test_template<T>(i, value1, value2, value3);
	// // COMMENT for string
	list_sort_test_template<T>(i, value1, value2, value3);
	list_reverse_test_template<T>(i, value1, value2, value3);
	list_splice_test_template<T>(i, value1, value2, value3);
	// // COMMENT for string
	list_remove_test_template<T>(i, value1, value2, value3);
	// COMMENT for string
	list_unique_test_template<T>(i, value1, value2, value3);
	// COMMENT for string
	list_merge_test_template<T>(i, value1, value2, value3);
	list_operators_test_template<T>(i, value1, value2, value3);
	list_max_size_test_template<T>(i);
}