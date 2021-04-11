#pragma once

#include "Tests.hpp"

#define CORRECT true
#define ERROR	false


template <typename T>
class ListTest : public Test<T>::Test
{
public:
	typedef typename std::list<T>::iterator					or_iter;
	typedef typename std::list<T>::const_iterator			or_const_iter;
	typedef typename std::list<T>::reverse_iterator 		or_rev_iter;
	typedef typename std::list<T>::const_reverse_iterator	or_const_rev_iter;
	typedef typename ft::list<T>::iterator					my_iter;
	typedef typename ft::list<T>::const_iterator			my_const_iter;
	typedef typename ft::list<T>::reverse_iterator 			my_rev_iter;
	typedef typename ft::list<T>::const_reverse_iterator 	my_const_rev_iter;

	std::list<T>		_or_list;
	ft::list<T>			_my_list;

private:
	std::string			_or_str;
	std::string			_my_str;

public:
	ListTest();
	ListTest(size_t count, T value = T(), bool out = true);
	template <typename InputIt>
	ListTest(InputIt first, InputIt last, bool out = true);
	ListTest(const ListTest<T> & other, bool out = true);

	void 				test();
	void 				resize_test(int count, const T &value = T());
	void				front_back_test();
	void				pop_back_front_test();
	void				empty_test();
	void				size_test();
	void				iterator_test();
	void				const_iterator_test();
	template <typename InputIt>
	void				insert_test(InputIt first, InputIt last);
	void				insert_test(const T &value);
	void				insert_test(size_t count, const T &value);
	void				clear_test();
	void				erase_test();
	void				erase_test_first_last();
	void				swap_test(ListTest<T> & other);
	void				assign_test(size_t count, const T & value);
	template <typename InputIt>
	void				assign_test(InputIt first, InputIt last);
	void				sort_test();
	template <typename Compare>
	void				sort_test(Compare comp);
	void				reverse_test();
	void				splice_test(ListTest<T> & other);
	void				splice_test(ListTest<T> & other, bool type);
	void				remove_test(const T & value);
	template <class UnaryPredicate>
	void				remove_if_test(UnaryPredicate p);
	void				unique_test();
	template< class BinaryPredicate >
	void				unique_test(BinaryPredicate p);
	void				merge_test(ListTest<T> & other);
	template <typename Compare>
	void				merge_test(ListTest<T> & other, Compare comp);
	void				oper_equial_test(ListTest<T> & other);
	void				max_size_test();

	void				compare();
	void				to_string();
	void 				resize(int count, const T &value = T());
	void				push_back(const T & value = T());
	void				push_front(const T &value = T());
	void				pop_back();
	void				pop_front();
	void				insert(or_iter or_pos, my_iter my_pos, const T & value);
	void				insert(or_iter or_pos, my_iter my_pos, size_t count, const T & value);
	template <typename InputIt>
	void				insert(or_iter or_pos, my_iter my_pos, InputIt first, InputIt last);
	void				clear();
	void				erase(or_iter or_pos, my_iter my_pos);
	void				erase(or_iter or_first, or_iter or_last, my_iter my_first, my_iter my_last);
	void				assign(size_t count, const T & value);
	template <typename InputIt>
	void				assign(InputIt first, InputIt last);
	void				remove(const T & value);
	template <class UnaryPredicate>
	void				remove_if(UnaryPredicate p);
	void				unique();
	template< class BinaryPredicate >
	void				unique(BinaryPredicate p);
	void				merge(ListTest<T> & other);
	template <typename Compare>
	void				merge(ListTest<T> & other, Compare comp);
	void				sort();
};

/*
** ------------------------------
**         Constructors
** ------------------------------
*/

template <typename T>
ListTest<T>::ListTest()
{
	_or_list = std::list<T>();
	_my_list = ft::list<T>();
	//test();
}

template <typename T>
ListTest<T>::ListTest(size_t count, T value, bool out)
{
	if (value != T())
	{
		_or_list = std::list<T>(count, value);
		_my_list = ft::list<T>(count, value);
	}
	else
	{
		_or_list = std::list<T>(count);
		_my_list = ft::list<T>(count);
	}
	if (out)
		test();
}

template <typename T>
template <typename InputIt>
ListTest<T>::ListTest(InputIt first, InputIt last, bool out)
{
	_or_list = std::list<T>(first, last);
	_my_list = ft::list<T>(first, last);
	if (out)
		test();
}

template <typename T>
ListTest<T>::ListTest(const ListTest<T> &other, bool out)
{
	_or_list = std::list<T>(other._or_list);
	_my_list = ft::list<T>(other._my_list);
	if (out)
		test();
}

/*
** ------------------------------
**            Tests
** ------------------------------
*/

template <typename T>
void ListTest<T>::test()
{
	to_string();
	compare();
}

template <typename T>
void ListTest<T>::resize_test(int count, const T &value)
{
	resize(count, value);
	test();
}

template <typename T>
void ListTest<T>::front_back_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << "|" << _my_list.front() << "| |" << _my_list.back() << "|";
	or_ss << "|" << _or_list.front() << "| |" << _or_list.back() << "|";

	_or_str.clear();
	_my_str.clear();
	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
	std::cout << "----------------\n";
}

template <typename T>
void ListTest<T>::pop_back_front_test()
{
	std::cout << "before:\n";
	test();
	std::cout << "after:\n";
	if (_my_list.size() && _or_list.size())
		pop_back();
	test();
	if (_my_list.size() && _or_list.size())
		pop_front();
	test();
	std::cout << "----------------------------------\n";
}

template <typename T>
void ListTest<T>::empty_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_list.empty();
	or_ss << _or_list.empty();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void ListTest<T>::clear_test()
{
	test();
	clear();
	test();
	std::cout << "------------------------\n";
}

template <typename T>
void ListTest<T>::size_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_list.size();
	or_ss << _or_list.size();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void ListTest<T>::max_size_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_list.max_size();
	or_ss << _or_list.max_size();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void ListTest<T>::iterator_test()
{
	std::cout << "iterator:\n";
	test();
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_rev_iter or_it = _or_list.rbegin();
	my_rev_iter my_it = _my_list.rbegin();

	std::cout << "reverse iterator:\n";
	while (or_it != _or_list.rend())
		or_ss << *(or_it++) << " ";
	while (my_it != _my_list.rend())
		my_ss << *(my_it++) << " ";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-------------------------\n";
}

template <typename T>
void ListTest<T>::const_iterator_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	std::cout << "const_iterator:\n";
	or_const_iter or_it = _or_list.begin();
	my_const_iter my_it = _my_list.begin();

	while (or_it != _or_list.end())
		or_ss << *(or_it++) << " ";
	while (my_it != _my_list.end())
		my_ss << *(my_it++) << " ";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "const_reverse_iterator:\n";
	or_const_rev_iter or_rev_it = _or_list.rbegin();
	my_const_rev_iter my_rev_it = _my_list.rbegin();
	or_ss.str("");
	my_ss.str("");
	while (or_rev_it != _or_list.rend())
		or_ss << *(or_rev_it++) << " ";
	while (my_rev_it != _my_list.rend())
		my_ss << *(my_rev_it++) << " ";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-------------------------\n";
}

template <typename T>
void ListTest<T>::insert_test(const T &value)
{
	or_iter or_temp = _or_list.begin();
	my_iter my_temp = _my_list.begin();

	std::cout << "---before---\n";
	test();
	std::cout << "---\n";
	insert(or_temp, my_temp, value);
	compare();
	test();
	std::cout << "---\n";

	or_temp++;
	my_temp++;
	insert(or_temp, my_temp, value);
	compare();
	test();
	std::cout << "---\n";

	or_temp++;
	my_temp++;
	or_temp++;
	my_temp++;
	insert(or_temp, my_temp, value);
	compare();
	test();
	std::cout << "---\n";

	insert(_or_list.end(), _my_list.end(), value);
	compare();
	test();
	std::cout << "------------------\n";
}

template <typename T>
void ListTest<T>::insert_test(size_t count, const T &value)
{
	or_iter or_temp = _or_list.begin();
	my_iter my_temp = _my_list.begin();

	std::cout << "---before---\n";
	test();
	std::cout << "---\n";
	insert(or_temp, my_temp, count, value);
	test();
	std::cout << "---\n";

	or_temp++;
	my_temp++;
	insert(or_temp, my_temp, count, value);
	test();
	std::cout << "---\n";

	or_temp++;
	my_temp++;
	or_temp++;
	my_temp++;
	insert(or_temp, my_temp, count, value);
	test();
	std::cout << "---\n";

	insert(_or_list.end(), _my_list.end(), count, value);
	test();
	std::cout << "------------------\n";
}

template <typename T>
template <typename InputIt>
void ListTest<T>::insert_test(InputIt first, InputIt last)
{
	or_iter or_temp = _or_list.begin();
	my_iter my_temp = _my_list.begin();

	std::cout << "---before---\n";
	test();
	std::cout << "---\n";
	insert(or_temp, my_temp, first, last);
	compare();
	test();
	std::cout << "---\n";

	or_temp++;
	my_temp++;
	insert(or_temp, my_temp, first, last);
	compare();
	test();
	std::cout << "---\n";
	
	or_temp++;
	my_temp++;
	or_temp++;
	my_temp++;
	insert(or_temp, my_temp, first, last);
	compare();
	test();
	std::cout << "---\n";

	insert(_or_list.end(), _my_list.end(), first, last);
	compare();
	test();
	std::cout << "------------------\n";
}

template <typename T>
void ListTest<T>::erase_test()
{
	or_iter or_temp = _or_list.begin();
	my_iter my_temp = _my_list.begin();

	std::cout << "first elem\n";
	test();
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "second elem\n";
	or_temp = _or_list.begin();
	my_temp = _my_list.begin();
	or_temp++;
	my_temp++;
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "third elem\n";
	or_temp = _or_list.begin();
	my_temp = _my_list.begin();
	or_temp++;
	my_temp++;
	or_temp++;
	my_temp++;
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "last elem\n";
	or_temp = _or_list.end();
	my_temp = _my_list.end();
	or_temp--;
	my_temp--;
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "------------------\n";
}

template <typename T>
void ListTest<T>::erase_test_first_last()
{
	or_iter or_temp = _or_list.begin();
	or_iter or_temp2 = _or_list.begin();
	my_iter my_temp = _my_list.begin();
	my_iter my_temp2 = _my_list.begin();

	std::cout << "same elem\n";
	test();
	erase(or_temp, or_temp, my_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "near elem\n";
	test();
	erase(or_temp, ++or_temp2, my_temp, ++my_temp2);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "two elems\n";
	test();
	or_temp = ++_or_list.begin();
	my_temp = ++_my_list.begin();
	or_temp2 = or_temp;
	my_temp2 = my_temp;
	my_temp2++; my_temp2++; or_temp2++; or_temp2++;
	erase(or_temp, or_temp2, my_temp, my_temp2);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "all elems\n";
	test();
	erase(_or_list.begin(), _or_list.end(), _my_list.begin(), _my_list.end());
	compare();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::swap_test(ListTest<T> &other)
{
	std::cout << "Before swap:\n";
	other.test();
	test();
	std::cout << "After swap:\n";
	_or_list.swap(other._or_list);
	_my_list.swap(other._my_list);
	other.test();
	test();
	std::cout << "After swap: (non member)\n";
	swap(_or_list, other._or_list);
	swap(_my_list, other._my_list);
	other.test();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::assign_test(size_t count, const T & value)
{
	std::cout << "Before assignment:\n";
	test();
	std::cout << "After assignment:\n";
	assign(count, value);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
template <typename InputIt>
void ListTest<T>::assign_test(InputIt first, InputIt last)
{
	std::cout << "Before assignment:\n";
	test();
	std::cout << "After assignment:\n";
	assign(first, last);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::sort_test()
{
	std::cout << "Before sorting:\n";
	test();
	std::cout << "After assignment:\n";
	_or_list.sort();
	_my_list.sort();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
template <typename Compare>
void ListTest<T>::sort_test(Compare comp)
{
	std::cout << "Before sorting:\n";
	test();
	std::cout << "After assignment:\n";
	_or_list.sort(comp);
	_my_list.sort(comp);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::reverse_test()
{
	std::cout << "Before reverse:\n";
	test();
	std::cout << "After reverse:\n";
	_or_list.reverse();
	_my_list.reverse();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::splice_test(ListTest<T> &other)
{
	ListTest<T> tmp1(other, false);
	std::cout << "Before splice:\n";
	test();
	other.test();
	std::cout << "After splice: (in the beginning)\n";
	_or_list.splice(_or_list.begin(), other._or_list);
	_my_list.splice(_my_list.begin(), other._my_list);
	test();
	other.test();
	std::cout << "After splice: (in the end)\n";
	_or_list.splice(_or_list.end(), tmp1._or_list);
	_my_list.splice(_my_list.end(), tmp1._my_list);
	test();
	tmp1.test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::splice_test(ListTest<T> &other, bool type)
{
	//ListTest<T> tmp1(other, false);
	std::cout << "Before splice:\n";
	test();
	other.test();
	if (type)
	{
		std::cout << "After splice: (first in the beginning)\n";
		_or_list.splice(_or_list.begin(), other._or_list, other._or_list.begin());
		_my_list.splice(_my_list.begin(), other._my_list, other._my_list.begin());
		test();
		other.test();
		std::cout << "After splice: (last in the end)\n";
		_or_list.splice(_or_list.end(), other._or_list, --other._or_list.end());
		_my_list.splice(_my_list.end(), other._my_list, --other._my_list.end());
		test();
		other.test();
		std::cout << "After splice: (middle in the middle)\n";
		_or_list.splice((_or_list.begin()++)++, other._or_list, --(--other._or_list.end()));
		_my_list.splice((_my_list.begin()++)++, other._my_list, --(--other._my_list.end()));
		test();
		other.test();
		std::cout << "-----------------\n";
		return;
	}
	std::cout << "After splice: (in the beginning)\n";
	my_const_iter my = other._my_list.begin();
	or_const_iter ori = other._or_list.begin();
	my_const_iter my_tmp = other._my_list.begin();
	or_const_iter ori_tmp = other._or_list.begin();
	my++;
	my++;
	ori++;
	ori++;
	_or_list.splice(_or_list.begin(), other._or_list, other._or_list.begin(), ori);
	_my_list.splice(_my_list.begin(), other._my_list, other._my_list.begin(), my);
	std::cout << *(++ori) << " " << *(++my) << " " << *ori_tmp << " "<< *my_tmp << std::endl;
	test();
	other.test();
	std::cout << "After splice: (in the beginning)\n";
	_or_list.splice(_or_list.begin(), other._or_list, other._or_list.begin(), other._or_list.begin());
	_my_list.splice(_my_list.begin(), other._my_list, other._my_list.begin(), other._my_list.begin());
	test();
	other.test();
	std::cout << "After splice: (in the end)\n";
	_or_list.splice(_or_list.begin(), other._or_list, other._or_list.begin(), other._or_list.end());
	_my_list.splice(_my_list.begin(), other._my_list, other._my_list.begin(), other._my_list.end());
	test();
	other.test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::remove_test(const T & value)
{
	std::cout << "Before:\n";
	test();
	std::cout << "After:\n";
	remove(value);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
template <class UnaryPredicate>
void ListTest<T>::remove_if_test(UnaryPredicate p)
{
	std::cout << "Before:\n";
	test();
	std::cout << "After:\n";
	remove_if(p);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::unique_test()
{
	std::cout << "Before:\n";
	test();
	std::cout << "After:\n";
	unique();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
template< class BinaryPredicate >
void ListTest<T>::unique_test(BinaryPredicate p)
{
	std::cout << "Before:\n";
	test();
	std::cout << "After:\n";
	unique(p);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::merge_test(ListTest<T> &other)
{
	std::cout << "Before:\n";
	test();
	other.test();
	std::cout << "After:\n";
	merge(other);
	test();
	other.test();
	std::cout << "-----------------\n";
}

template <typename T>
template <typename Compare>
void ListTest<T>::merge_test(ListTest<T> & other, Compare comp)
{
	std::cout << "Before:\n";
	test();
	other.test();
	std::cout << "After:\n";
	merge(other, comp);
	test();
	other.test();
	std::cout << "-----------------\n";
}

template <typename T>
void ListTest<T>::oper_equial_test(ListTest<T> &other)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	test();
	other.test();
	std::cout << std::endl;

	or_ss << "  ==: " << (_or_list == other._or_list) << " swap " << (other._or_list == _or_list) << " | ";
	my_ss << "  ==: " << (_my_list == other._my_list) << " swap " << (other._my_list == _my_list) << " | ";

	or_ss << "!=: " << (_or_list != other._or_list) << " swap " << (other._or_list != _or_list) << " | ";
	my_ss << "!=: " << (_my_list != other._my_list) << " swap " << (other._my_list != _my_list) << " | ";

	or_ss << "<: " << (_or_list < other._or_list) << " swap " << (other._or_list < _or_list) << " | ";
	my_ss << "<: " << (_my_list < other._my_list) << " swap " << (other._my_list < _my_list) << " | ";

	or_ss << ">: " << (_or_list > other._or_list) << " swap " << (other._or_list > _or_list) << " | ";
	my_ss << ">: " << (_my_list > other._my_list) << " swap " << (other._my_list > _my_list) << " | ";

	or_ss << "<=: " << (_or_list <= other._or_list) << " swap " << (other._or_list <= _or_list) << " | ";
	my_ss << "<=: " << (_my_list <= other._my_list) << " swap " << (other._my_list <= _my_list) << " | ";

	or_ss << ">=: " << (_or_list >= other._or_list) << " swap " << (other._or_list >= _or_list) << " | ";
	my_ss << ">=: " << (_my_list >= other._my_list) << " swap " << (other._my_list >= _my_list) << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-----------------\n";
}

/*
** ------------------------------
**            Methods
** ------------------------------
*/

template <typename T>
void ListTest<T>::compare()
{
	std::cout << "ft  |" << _my_list.size() << "| " << _my_str << std::endl
			  << "std |" << _or_list.size() << "| " << _or_str << std::endl;
	this->print_error(_my_list.size() == _or_list.size() && !_my_str.compare(_or_str));
}

template <typename T>
void ListTest<T>::to_string()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_iter or_it = _or_list.begin();
	my_iter my_it = _my_list.begin();

	while (or_it != _or_list.end())
		or_ss << *(or_it++) << " ";

	while (my_it != _my_list.end())
		my_ss << *(my_it++) << " ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void ListTest<T>::resize(int count, const T &value)
{
	if (value != T())
	{
		_or_list.resize(count, value);
		_my_list.resize(count, value);
	}
	else
	{
		_or_list.resize(count);
		_my_list.resize(count);
	}
}

template <typename T>
void ListTest<T>::push_back(const T &value)
{
	_my_list.push_back(value);
	_or_list.push_back(value);
}

template <typename T>
void ListTest<T>::push_front(const T &value)
{
	_my_list.push_front(value);
	_or_list.push_front(value);
}

template <typename T>
void ListTest<T>::pop_front()
{
	_my_list.pop_front();
	_or_list.pop_front();
}

template <typename T>
void ListTest<T>::pop_back()
{
	_my_list.pop_back();
	_or_list.pop_back();
}

template <typename T>
void ListTest<T>::insert(or_iter or_pos, my_iter my_pos, const T &value)
{
	or_iter or_temp;
	my_iter my_temp;
	std::stringstream or_ss;
	std::stringstream my_ss;

	or_temp = _or_list.insert(or_pos, value);
	my_temp = _my_list.insert(my_pos, value);

	or_ss << "|" << *(or_temp) << "|";
	my_ss << "|" << *(my_temp) << "|";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void ListTest<T>::insert(or_iter or_pos, my_iter my_pos, size_t count, const T &value)
{
	or_iter or_temp;
	my_iter my_temp;
	std::stringstream or_ss;
	std::stringstream my_ss;

	_or_list.insert(or_pos, count, value);
	_my_list.insert(my_pos, count, value);

	if (or_pos != _or_list.end() && my_pos != _my_list.end())
	{
		or_ss << "|" << *(or_pos) << "|";
		my_ss << "|" << *(my_pos) << "|";
	}

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
template <typename InputIt>
void ListTest<T>::insert(or_iter or_pos, my_iter my_pos, InputIt first, InputIt last)
{
	or_iter or_temp;
	my_iter my_temp;
	std::stringstream or_ss;
	std::stringstream my_ss;

	_or_list.insert(or_pos, first, last);
	_my_list.insert(my_pos, first, last);

	if (or_pos != _or_list.end() && my_pos != _my_list.end())
	{
		or_ss << "|" << *(or_pos) << "|";
		my_ss << "|" << *(my_pos) << "|";
	}

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void ListTest<T>::clear()
{
	_or_list.clear();
	_my_list.clear();
}

template <typename T>
void ListTest<T>::erase(or_iter or_pos, my_iter my_pos)
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_iter or_tmp;
	my_iter my_tmp;

	or_tmp = _or_list.erase(or_pos);
	my_tmp = _my_list.erase(my_pos);
	(void)my_pos;
	if (or_tmp != _or_list.end() && my_tmp != _my_list.end())
	{
		or_ss << "|" << *(or_tmp) << "|";
		my_ss << "|" << *(my_tmp) << "|";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void ListTest<T>::erase(or_iter or_first, or_iter or_last, my_iter my_first, my_iter my_last)
{
	std::stringstream	or_ss;
	std::stringstream	my_ss;
	or_iter				or_tmp;
	my_iter				my_tmp;

	or_tmp = _or_list.erase(or_first, or_last);
	my_tmp = _my_list.erase(my_first, my_last);
	if (or_tmp != _or_list.end() && my_tmp != _my_list.end())
	{
		or_ss << "|" << *(or_tmp) << "|";
		my_ss << "|" << *(my_tmp) << "|";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void ListTest<T>::assign(size_t count, const T & value)
{
	_or_list.assign(count, value);
	_my_list.assign(count, value);
}

template <typename T>
template <typename InputIt>
void ListTest<T>::assign(InputIt first, InputIt last)
{
	_or_list.assign(first, last);
	_my_list.assign(first, last);
}

template <typename T>
void ListTest<T>::remove(const T & value)
{
	_my_list.remove(value);
	_or_list.remove(value);
}

template <typename T>
template <class UnaryPredicate>
void ListTest<T>::remove_if(UnaryPredicate p)
{
	_my_list.remove_if(p);
	_or_list.remove_if(p);
}

template <typename T>
void ListTest<T>::unique()
{
	_my_list.unique();
	_or_list.unique();
}

template <typename T>
template< class BinaryPredicate >
void ListTest<T>::unique(BinaryPredicate p)
{
	_my_list.unique(p);
	_or_list.unique(p);
}

template <typename T>
void ListTest<T>::merge(ListTest<T> &other)
{
	_my_list.merge(other._my_list);
	_or_list.merge(other._or_list);
}

template <typename T>
void ListTest<T>::sort()
{
	_my_list.sort();
	_or_list.sort();
}

template <typename T>
template <typename Compare>
void ListTest<T>::merge(ListTest<T> & other, Compare comp)
{
	_my_list.merge(other._my_list, comp);
	_or_list.merge(other._or_list, comp);
}
