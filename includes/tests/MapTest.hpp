#pragma once

#include "Tests.hpp"

#define CORRECT true
#define ERROR	false


template <typename Key,	typename T>
class MapTest : public Test<T>::Test
{
public:
	typedef Key													key_type;
	typedef T													mapped_type;
	typedef std::pair<const key_type,mapped_type>				value_type;
	typedef typename std::map<Key, T>::iterator					or_iter;
	typedef typename std::map<Key, T>::const_iterator			or_const_iter;
	typedef typename std::map<Key, T>::reverse_iterator 		or_rev_iter;
	typedef typename std::map<Key, T>::const_reverse_iterator	or_const_rev_iter;
	typedef typename ft::map<Key, T>::iterator					my_iter;
	typedef typename ft::map<Key, T>::const_iterator			my_const_iter;
	typedef typename ft::map<Key, T>::reverse_iterator 			my_rev_iter;
	typedef typename ft::map<Key, T>::const_reverse_iterator 	my_const_rev_iter;

	std::map<Key, T>	_or_map;
	ft::map<Key, T>		_my_map;

private:
	std::string			_or_str;
	std::string			_my_str;

public:
	MapTest();
	template <typename InputIt>
	MapTest(InputIt first, InputIt last, bool out = true);
	MapTest(const MapTest<Key, T> & other, bool out = true);

/*
** tests
*/
	void		test();
	void		compare();
	void		to_str();
	void		to_str_const();
	void		to_str_rev();
	void		to_str_rev_const();

	void		empty_test();
	void		size_test();
	void		max_size_test();

	void		iterator_test();
	void		const_iterator_test();
	void		rev_iterator_test();
	void		const_rev_iterator_test();

	void		operator_skoba_test();
	void		operator_equal(MapTest<Key, T> & tmp);

	void		insert_val_test(const Key k[30], const T val[30]);
	void		insert_pos_val_test(const Key k[30], const T val[30]);
	template <class InputIterator>
	void		insert_first_last_test(InputIterator first, InputIterator last);
	void		erase_k_test(const Key k[30]);
	void		erase_pos_test();
	void		erase_first_last_test();
	void		clear_test();
	void		swap_test(MapTest<Key, T> & tmp);

	void		find_test(const Key k[30]);
	void		lower_test(const Key k[30]);
	void		upper_test(const Key k[30]);
	void		equal_test(const Key k[30]);
	void		count_test(const Key k[30]);

	void		key_comp_test(const Key k);
	void		value_comp_test();

/*
** functions
*/
	void		insert_val(const value_type& val);
	void		insert_pos_val(my_iter my_pos, or_iter or_pos, const value_type &val);
	void		erase(const key_type &k);
	void		erase(or_iter or_pos, my_iter my_pos);
	void		erase(or_iter or_first, or_iter or_last, my_iter my_first, my_iter my_last);
	void		clear();
	void		swap(MapTest<Key, T> & tmp);

};

/*
** ------------------------------
**         Constructors
** ------------------------------
*/

template <typename Key,	typename T>
MapTest<Key, T>::MapTest()
{
	_or_map = std::map<Key, T>();
	_my_map = ft::map<Key, T>();
}

template <typename Key,	typename T>
template <typename InputIt>
MapTest<Key, T>::MapTest(InputIt first, InputIt last, bool out)
{
	_or_map = std::map<Key, T>(first, last);
	_my_map = ft::map<Key, T>(first, last);
	if (out)
		test();
}

template <typename Key,	typename T>
MapTest<Key, T>::MapTest(const MapTest<Key, T> &other, bool out)
{
	_or_map = std::map<Key, T>(other._or_map);
	_my_map = ft::map<Key, T>(other._my_map);
	if (out)
		test();
}

/*
** ------------------------------
**            HELP
** ------------------------------
*/

template <typename Key,	typename T>
void MapTest<Key, T>::test()
{
	to_str();
	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::compare()
{
	std::cout << "ft  ||size:" << _my_map.size() << "|| " << _my_str << std::endl
			  << "std ||size:" << _or_map.size() << "|| " << _or_str << std::endl;
	this->print_error(_my_map.size() == _or_map.size() && !_my_str.compare(_or_str));
}

template <typename Key, typename T>
void MapTest<Key, T>::to_str()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_iter or_it = _or_map.begin();
	my_iter my_it = _my_map.begin();

	while (or_it != _or_map.end())
		or_ss << (*(or_it)).first << "-" << (*(or_it++)).second << " | ";

	while (my_it != _my_map.end())
		my_ss << (*(my_it)).first << "-" << (*(my_it++)).second << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename Key, typename T>
void MapTest<Key, T>::to_str_rev()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_rev_iter or_it = _or_map.rbegin();
	my_rev_iter my_it = _my_map.rbegin();

	while (or_it != _or_map.rend())
		or_ss << (*(or_it)).first << "-" << (*(or_it++)).second << " | ";

	while (my_it != _my_map.rend())
		my_ss << (*(my_it)).first << "-" << (*(my_it++)).second << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename Key, typename T>
void MapTest<Key, T>::to_str_rev_const()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_const_rev_iter or_it = _or_map.rbegin();
	my_const_rev_iter my_it = _my_map.rbegin();

	while (or_it != _or_map.rend())
		or_ss << (*(or_it)).first << "-" << (*(or_it++)).second << " | ";

	while (my_it != _my_map.rend())
		my_ss << (*(my_it)).first << "-" << (*(my_it++)).second << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename Key, typename T>
void MapTest<Key, T>::to_str_const()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_const_iter or_it = _or_map.begin();
	my_const_iter my_it = _my_map.begin();

	while (or_it != _or_map.end())
		or_ss << (*(or_it)).first << "-" << (*(or_it++)).second << " | ";

	while (my_it != _my_map.end())
		my_ss << (*(my_it)).first << "-" << (*(my_it++)).second << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

/*
** ------------------------------
**            Tests
** ------------------------------
*/

template <typename Key, typename T>
void MapTest<Key, T>::empty_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	or_ss << _or_map.empty();
	my_ss << _my_map.empty();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::iterator_test()
{
	test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::const_iterator_test()
{
	to_str_const();
	compare();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::rev_iterator_test()
{
	to_str_rev();
	compare();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::const_rev_iterator_test()
{
	to_str_rev_const();
	compare();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::operator_skoba_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_const_iter or_it = _or_map.begin();
	my_const_iter my_it = _my_map.begin();

	while (or_it != _or_map.end())
		or_ss << (*(or_it)).first << "-" << _or_map[(*(or_it++)).first] << " | ";

	while (my_it != _my_map.end())
		my_ss << (*(my_it)).first << "-" << _my_map[(*(my_it++)).first] << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::operator_equal(MapTest<Key, T> &tmp)
{
	std::cout << "before:\n";
	test();
	tmp.test();
	std::cout << "after:\n";
	_my_map = tmp._my_map;
	_or_map = tmp._or_map;
	test();
	tmp.test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::insert_val_test(const Key k[30], const T val[30])
{
	size_t el;
	for (size_t i = 0; i < 10; i++)
	{
		el = rand() % 30;
		insert_val(std::make_pair<Key, T>(k[el], val[el]));
		compare();
	}
	test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::insert_pos_val_test(const Key k[30], const T val[30])
{
	size_t el;
	for (size_t i = 0; i < 10; i++)
	{
		el = rand() % 30;
		insert_pos_val(_my_map.begin(), _or_map.begin(), std::make_pair<Key, T>(k[el], val[el]));
		compare();
	}
	test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
template <class InputIterator>
void MapTest<Key, T>::insert_first_last_test(InputIterator first, InputIterator last)
{
	_my_map.insert(first, last);
	_or_map.insert(first, last);

	to_str();
	test();
}

template <typename Key, typename T>
void MapTest<Key, T>::erase_k_test(const Key k[30])
{
	size_t el;
	test();
	for (size_t i = 0; i < 10; i++)
	{
		el = rand() % 30;
		erase(k[el]);
		compare();
	}
	test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::erase_pos_test()
{
	or_iter orit = _or_map.begin();
	my_iter myit = _my_map.begin();
	size_t size = _or_map.size();
	size_t i = 0;

	test();
	while (size-- > 0 && i++ < 4)
		erase(orit++, myit++);
	test();
}

template <typename Key, typename T>
void MapTest<Key, T>::erase_first_last_test()
{
	or_iter orit = _or_map.begin();
	my_iter myit = _my_map.begin();

	test();
	std::cout << "near:\n";
	erase(orit++, orit, myit++, myit);
	test();

	std::cout << "couple:\n";
	orit = _or_map.begin();
	myit = _my_map.begin();
	erase(orit++, ++orit, myit++, ++myit);
	test();

	std::cout << "from the middle:\n";
	orit = ++_or_map.begin();
	myit = ++_my_map.begin();
	orit++;
	myit++;
	erase(orit++, ++orit, myit++, ++myit);
	test();

	std::cout << "last:\n";
	orit = --_or_map.end();
	myit = --_my_map.end();
	erase(orit, ++orit, myit, ++myit);
	test();

	std::cout << "all:\n";
	erase(_or_map.begin(), _or_map.end(), _my_map.begin(), _my_map.end());
	test();

	std::cout << "empty:\n";
	erase(_or_map.begin(), _or_map.end(), _my_map.begin(), _my_map.end());
	test();

	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::clear_test()
{
	std::cout << "before:\n";
	test();
	std::cout << "after:\n";
	clear();
	test();
	std::cout << "clear empty:\n";
	clear();
	test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::swap_test(MapTest<Key, T> & tmp)
{
	(void)tmp;
	std::cout << "before:\n";
	test();
	tmp.test();
	std::cout << "after:\n";
	swap(tmp);
	test();
	tmp.test();
	std::cout << "again:\n";
	swap(tmp);
	test();
	tmp.test();
	std::cout << "----------\n";
}

template <typename Key, typename T>
void MapTest<Key, T>::find_test(const Key k[30])
{
	size_t j;
	std::stringstream or_ss;
	std::stringstream my_ss;
	my_iter myit = _my_map.begin();
	or_iter orit = _or_map.begin();

	for (size_t i = 0; i < 10; i++)
	{
		j = rand() % 30;
		myit = _my_map.find(k[j]);
		if (myit != _my_map.end())
			my_ss << (*myit).first << "-" << (*myit).second << " | ";
		else
			my_ss << "end | ";
		orit = _or_map.find(k[j]);
		if (orit != _or_map.end())
			or_ss << (*orit).first << "-" << (*orit).second << " | ";
		else
			or_ss << "end | ";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::lower_test(const Key k[30])
{
	size_t j;
	std::stringstream or_ss;
	std::stringstream my_ss;
	my_iter myit;
	or_iter orit;

	for (size_t i = 0; i < 10; i++)
	{
		j = rand() % 30;
		myit = _my_map.lower_bound(k[j]);
		if (myit != _my_map.end())
			my_ss << (*myit).first << "-" << (*myit).second << " | ";
		else
			my_ss << "end | ";
		orit = _or_map.lower_bound(k[j]);
		if (orit != _or_map.end())
			or_ss << (*orit).first << "-" << (*orit).second << " | ";
		else
			or_ss << "end | ";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::upper_test(const Key k[30])
{
	size_t j;
	std::stringstream or_ss;
	std::stringstream my_ss;
	my_iter myit;
	or_iter orit;

	for (size_t i = 0; i < 10; i++)
	{
		j = rand() % 30;
		myit = _my_map.upper_bound(k[j]);
		if (myit != _my_map.end())
			my_ss << (*myit).first << "-" << (*myit).second << " | ";
		else
			my_ss << "end | ";
		orit = _or_map.upper_bound(k[j]);
		if (orit != _or_map.end())
			or_ss << (*orit).first << "-" << (*orit).second << " | ";
		else
			or_ss << "end | ";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::equal_test(const Key k[30])
{
	size_t j;
	std::stringstream or_ss;
	std::stringstream my_ss;
	std::pair<my_iter, my_iter> my_pair;
	std::pair<or_iter, or_iter> or_pair;
	my_iter myit;
	or_iter orit;

	for (size_t i = 0; i < 10; i++)
	{
		j = rand() % 30;
		my_pair = _my_map.equal_range(k[j]);
		myit = my_pair.first;
		if (myit != _my_map.end())
			my_ss << (*myit).first << "-" << (*myit).second << " | ";
		else
			my_ss << "end | ";
		myit = my_pair.second;
		if (myit != _my_map.end())
			my_ss << (*myit).first << "-" << (*myit).second << " | ";
		else
			my_ss << "end | ";

		
		or_pair = _or_map.equal_range(k[j]);
		orit = or_pair.first;
		if (orit != _or_map.end())
			or_ss << (*orit).first << "-" << (*orit).second << " | ";
		else
			or_ss << "end | ";
		orit = or_pair.second;
		if (orit != _or_map.end())
			or_ss << (*orit).first << "-" << (*orit).second << " | ";
		else
			or_ss << "end | ";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::key_comp_test(const Key k)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	typename std::map<Key, T>::key_compare or_comp = _or_map.key_comp();
	typename ft::map<Key, T>::key_compare my_comp = _my_map.key_comp();

	or_iter or_it = _or_map.begin();
	my_iter my_it = _my_map.begin();

	while (or_it != _or_map.end())
		or_ss << or_comp(k, (*or_it++).first) << " ";
	while (my_it != _my_map.end())
		my_ss << my_comp(k, (*my_it++).first) << " ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

template <typename Key, typename T>
void MapTest<Key, T>::value_comp_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	size_t i = 0;

	or_iter or_it = _or_map.begin();
	my_iter my_it = _my_map.begin();
	std::pair<Key, T> pair;

	while (or_it != _or_map.end() && i < _or_map.size() / 2)
	{
		or_it++;
		i++;
	}
	pair = *or_it;
	or_it = _or_map.begin();

	while (or_it != _or_map.end())
		or_ss << _or_map.value_comp() (pair, (*or_it++)) << " ";
	while (my_it != _my_map.end())
		my_ss <<_my_map.value_comp() (pair, (*my_it++)) << " ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

/*
** ------------------------------------------------------------------------------------------
**            							Functions
** ------------------------------------------------------------------------------------------
*/

template <typename Key, typename T>
void MapTest<Key, T>::insert_val(const value_type &val)
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	std::pair<or_iter, bool> or_pair;
	std::pair<my_iter, bool> my_pair;

	my_pair = _my_map.insert(val);
	or_pair = _or_map.insert(val);

	or_ss << (*(or_pair.first)).first << "-" << (*(or_pair.first)).second << " " << or_pair.second;
	my_ss << (*(my_pair.first)).first << "-" << (*(my_pair.first)).second << " " << my_pair.second;

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename Key, typename T>
void MapTest<Key, T>::insert_pos_val(my_iter my_pos, or_iter or_pos, const value_type &val)
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_iter or_it;
	my_iter my_it;

	my_it = _my_map.insert(my_pos, val);
	or_it = _or_map.insert(or_pos, val);

	or_ss << (*(or_it)).first << "-" << (*(or_it)).second;
	my_ss << (*(my_it)).first << "-" << (*(my_it)).second;

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename Key, typename T>
void MapTest<Key, T>::erase(const Key &k)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_map.erase(k);
	or_ss << _or_map.erase(k);

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename Key, typename T>
void MapTest<Key, T>::erase(or_iter or_it, my_iter my_it)
{
	_my_map.erase(my_it);
	_or_map.erase(or_it);
}

template <typename Key, typename T>
void MapTest<Key, T>::erase(or_iter or_first, or_iter or_last, my_iter my_first, my_iter my_last)
{
	_my_map.erase(my_first, my_last);
	_or_map.erase(or_first, or_last);
}

template <typename Key, typename T>
void MapTest<Key, T>::clear()
{
	_my_map.clear();
	_or_map.clear();
}

template <typename Key, typename T>
void MapTest<Key, T>::swap(MapTest<Key, T> & tmp)
{
	_my_map.swap(tmp._my_map);
	_or_map.swap(tmp._or_map);
}

