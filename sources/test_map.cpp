#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../includes/tests/MapTest.hpp"

template <typename Key,	typename T>
void fill_map(MapTest<Key, T> & curr, const Key k[30], const T val[30], size_t count = 10)
{
	std::map<Key, T> tmp = std::map<Key, T>();
	size_t j;
	for (size_t i = 0; i < count; i++)
	{
		j = rand() % 30;
		tmp.insert(std::make_pair<Key, T>(k[j], val[j]));
	}

	curr._my_map.insert(tmp.begin(), tmp.end());
	curr._or_map.insert(tmp.begin(), tmp.end());
}

/*
** ----------------------------------------------
**				TEST functions
** ----------------------------------------------
*/

template <typename Key,	typename T>
void map_constructor_test_template(int &m, const Key k[30], const T val[30])
{
	std::map<Key, T> tmp = std::map<Key, T>();
	for (int i = 0; i < 15; i++)
		tmp.insert(std::make_pair<Key, T>(k[i], val[i]));
	typename std::map<Key, T>::iterator it = tmp.begin();

	Test<T>::print_test(m++, "constructors");
	std::cout << "Default:\n";
	MapTest<Key, T> test1 = MapTest<Key, T>();
	test1.test();
	std::cout << "First-Last (full):\n";
	MapTest<Key, T> test2 = MapTest<Key, T>(it++, tmp.end());
	std::cout << "First-Last:\n";
	MapTest<Key, T> test3 = MapTest<Key, T>(++it, --tmp.end());
	std::cout << "First-Last (same):\n";
	MapTest<Key, T> test4 = MapTest<Key, T>(it,it);
	std::cout << "Copy full\n";
	MapTest<Key, T> test5 = MapTest<Key, T>(test2);
	std::cout << "Copy empty\n";
	MapTest<Key, T> test6 = MapTest<Key, T>(test1);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result() &&
								  test4.get_result() && test5.get_result() && test6.get_result());

	Test<T>::print_test(m++, "empty");
	test1.empty_test();
	test2.empty_test();
	test3.empty_test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());

	Test<T>::print_test(m++, "iterator");
	test1.iterator_test();
	test2.iterator_test();
	test3.iterator_test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());

	Test<T>::print_test(m++, "const iterator");
	test1.const_iterator_test();
	test2.const_iterator_test();
	test3.const_iterator_test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());

	Test<T>::print_test(m++, "reverse iterator");
	test1.rev_iterator_test();
	test2.rev_iterator_test();
	test3.rev_iterator_test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());

	Test<T>::print_test(m++, "const reverse iterator");
	test1.const_rev_iterator_test();
	test2.const_rev_iterator_test();
	test3.const_rev_iterator_test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());

	Test<T>::print_test(m++, "operator []");
	test1.operator_skoba_test();
	test2.operator_skoba_test();
	test3.operator_skoba_test();
	test1._my_map[k[20]] = val[20];
	test1._my_map[k[21]] = val[21];
	test1._or_map[k[20]] = val[20];
	test1._or_map[k[21]] = val[21];
	test1.test();
	test2._my_map[k[22]] = val[25];
	test2._my_map[k[23]] = val[26];
	test2._or_map[k[22]] = val[25];
	test2._or_map[k[23]] = val[26];
	test2.test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());
}

template <typename Key, typename T>
void map_equal_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	MapTest<Key, T> test2 = MapTest<Key, T>();
	MapTest<Key, T> test3 = MapTest<Key, T>();
	fill_map(test1, k, val, 13);
	fill_map(test2, k, val, 29);

	Test<T>::print_test(i++, "operator =");
	test1.operator_equal(test2);
	test1.operator_equal(test3);
	test3.operator_equal(test2);
	test3.clear();
	test2.clear();
	test3.operator_equal(test2);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result() && test3.get_result());
}

template <typename Key, typename T>
void map_insert_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	MapTest<Key, T> test2 = MapTest<Key, T>();

	Test<T>::print_test(i++, "Insert_val");
	test1.test();
	test1.insert_val_test(k, val);
	test1.print_result();

	Test<T>::print_test(i++, "Insert_pos_val");
	test1.test();
	test1.insert_pos_val_test(k, val);
	test1.print_result();

	Test<T>::print_test(i++, "Insert_first_last");
	test2.test();
	test2.insert_first_last_test(++test1._my_map.begin(), --test1._my_map.end());
	test2.insert_first_last_test(test1._my_map.begin(), test1._my_map.end());
	test2.print_result();
}

template <typename Key, typename T>
void map_erase_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	MapTest<Key, T> test2 = MapTest<Key, T>();
	fill_map(test1, k, val);

	Test<T>::print_test(i++, "erase key");
	test1.erase_k_test(k);
	test2.erase_k_test(k);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());

	Test<T>::print_test(i++, "erase pos");
	test1.erase_pos_test();
	test1.print_result();

	Test<T>::print_test(i++, "erase first last");
	fill_map(test1, k, val);
	test1.erase_first_last_test();
	test1.print_result();
}

template <typename Key, typename T>
void map_clear_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	fill_map(test1, k, val);

	Test<T>::print_test(i++, "clear");
	test1.clear_test();
	test1.print_result();
}

template <typename Key, typename T>
void map_swap_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	MapTest<Key, T> test2 = MapTest<Key, T>();
	fill_map(test1, k, val, 15);

	Test<T>::print_test(i++, "swap");
	test1.swap_test(test2);
	fill_map(test2, k, val, 3);
	test1.swap_test(test2);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());
}

template <typename Key, typename T>
void map_bounds_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	MapTest<Key, T> test2 = MapTest<Key, T>();
	fill_map(test1, k, val, 20);

	Test<T>::print_test(i++, "find");
	test1.find_test(k);
	test2.find_test(k);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());

	Test<T>::print_test(i++, "lower bound");
	test1.lower_test(k);
	test2.lower_test(k);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());

	Test<T>::print_test(i++, "upper bound");
	test1.upper_test(k);
	test2.upper_test(k);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());

	Test<T>::print_test(i++, "equal renge");
	test1.equal_test(k);
	test2.equal_test(k);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());
}

template <typename Key, typename T>
void map_comp_test_template(int &i, const Key k[30], const T val[30])
{
	MapTest<Key, T> test1 = MapTest<Key, T>();
	MapTest<Key, T> test2 = MapTest<Key, T>();
	fill_map(test1, k, val, 20);

	Test<T>::print_test(i++, "key compare");
	test1.key_comp_test(k[rand() % 30]);
	test1.key_comp_test(k[rand() % 30]);
	test2.key_comp_test(k[rand() % 30]);
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());

	Test<T>::print_test(i++, "value compare");
	test1.value_comp_test();
	test2.value_comp_test();
	MapTest<Key, T>::print_result(test1.get_result() && test2.get_result());
}

/*
** ----------------------------------------------
**				CALLER functions
** ----------------------------------------------
*/

	template <typename Key, typename T>
	void map_test(const Key k[30], const T val[30])
	{
		int i = 1;
		const Key *keys = k;
		const T *vals = val;
		map_constructor_test_template<Key, T>(i, keys, vals);
		map_equal_test_template<Key, T>(i, keys, vals);
		map_insert_test_template<Key, T>(i, keys, vals);
		map_erase_test_template<Key, T>(i, keys, vals);
		map_clear_test_template<Key, T>(i, keys, vals);
		map_swap_test_template<Key, T>(i, keys, vals);
		map_bounds_test_template<Key, T>(i, keys, vals);
		map_comp_test_template<Key, T>(i, keys, vals);
	}