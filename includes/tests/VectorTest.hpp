#pragma once

#include "Tests.hpp"

#define CORRECT true
#define ERROR	false


template <typename T>
class VectorTest : public Test<T>::Test
{
public:
	typedef typename std::vector<T>::iterator				or_iter;
	typedef typename std::vector<T>::const_iterator			or_const_iter;
	typedef typename std::vector<T>::reverse_iterator 		or_rev_iter;
	typedef typename std::vector<T>::const_reverse_iterator	or_const_rev_iter;
	typedef typename ft::vector<T>::iterator				my_iter;
	typedef typename ft::vector<T>::const_iterator			my_const_iter;
	typedef typename ft::vector<T>::reverse_iterator 		my_rev_iter;
	typedef typename ft::vector<T>::const_reverse_iterator 	my_const_rev_iter;

	std::vector<T>		_or_vector;
	ft::vector<T>		_my_vector;

private:
	std::string			_or_str;
	std::string			_my_str;

public:
	VectorTest();
	VectorTest(size_t count, T value = T(), bool out = true);
	template <typename InputIt>
	VectorTest(InputIt first, InputIt last, bool out = true);
	VectorTest(const VectorTest<T> & other, bool out = true);

	void 				test();
	void 				resize_test(int count, const T &value = T());
	void 				reserve_test(int count);
	void				front_back_test();
	void				pop_back_test();
	void				empty_test();
	void				size_test();
	void				iterator_test();
	void				const_iterator_test();
	void				clear_test();
	void				assign_test(size_t count, const T & value);
	template <typename InputIt>
	void				assign_test(InputIt first, InputIt last);
	void				operator_skoba_test();
	void				at_test();
	void				insert_test(size_t count, const T &value);
	void				insert_test(const T &value);
	template <typename InputIt>
	void				insert_test(InputIt first, InputIt last);
	void				erase_test();
	void				erase_test_first_last();
	void				max_size_test();
	void				swap_test(VectorTest & other);
	void				oper_equial_test(VectorTest<T> & other);

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
};

/*
** ------------------------------
**         Constructors
** ------------------------------
*/

template <typename T>
VectorTest<T>::VectorTest()
{
	_or_vector = std::vector<T>();
	_my_vector = ft::vector<T>();
	//test();
}

template <typename T>
VectorTest<T>::VectorTest(size_t count, T value, bool out)
{
	if (value != T())
	{
		_or_vector = std::vector<T>(count, value);
		_my_vector = ft::vector<T>(count, value);
	}
	else
	{
		_or_vector = std::vector<T>(count);
		_my_vector = ft::vector<T>(count);
	}
	if (out)
		test();
}

template <typename T>
template <typename InputIt>
VectorTest<T>::VectorTest(InputIt first, InputIt last, bool out)
{
	_or_vector = std::vector<T>(first, last);
	_my_vector = ft::vector<T>(first, last);
	if (out)
		test();
}

template <typename T>
VectorTest<T>::VectorTest(const VectorTest<T> &other, bool out)
{
	_or_vector = std::vector<T>(other._or_vector);
	_my_vector = ft::vector<T>(other._my_vector);
	if (out)
		test();
}

/*
** ------------------------------
**            Tests
** ------------------------------
*/

template <typename T>
void VectorTest<T>::test()
{
	to_string();
	compare();
}

template <typename T>
void VectorTest<T>::resize_test(int count, const T &value)
{
	resize(count, value);
	test();
}

template <typename T>
void VectorTest<T>::reserve_test(int count)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	_or_vector.reserve(count);
	_my_vector.reserve(count);

	or_ss << "|" << _or_vector.capacity() << "|";
	my_ss << "|" << _my_vector.capacity() << "|";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
}

template <typename T>
void VectorTest<T>::front_back_test()
{
	test();

	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << "|" << _my_vector.front() << "| |" << _my_vector.back() << "|";
	or_ss << "|" << _or_vector.front() << "| |" << _or_vector.back() << "|";

	_or_str.clear();
	_my_str.clear();
	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
	std::cout << "----------------\n";
}

template <typename T>
void VectorTest<T>::pop_back_test()
{
	std::cout << "before:\n";
	test();
	std::cout << "after:\n";
	if (_my_vector.size() && _or_vector.size())
		pop_back();
	test();
	std::cout << "----------------------------------\n";
}

template <typename T>
void VectorTest<T>::empty_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_vector.empty();
	or_ss << _or_vector.empty();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void VectorTest<T>::clear_test()
{
	test();
	clear();
	test();
	std::cout << "------------------------\n";
}

template <typename T>
void VectorTest<T>::size_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_vector.size();
	or_ss << _or_vector.size();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void VectorTest<T>::max_size_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	my_ss << _my_vector.max_size();
	or_ss << _or_vector.max_size();

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
void VectorTest<T>::iterator_test()
{
	std::cout << "iterator:\n";
	test();
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_rev_iter or_it = _or_vector.rbegin();
	my_rev_iter my_it = _my_vector.rbegin();

	(void)my_it;
	std::cout << "reverse iterator:\n";
	while (or_it != _or_vector.rend())
		or_ss << *(or_it++) << " ";
	while (my_it != _my_vector.rend())
	 	my_ss << *(my_it++) << " ";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-------------------------\n";
}

template <typename T>
void VectorTest<T>::const_iterator_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	std::cout << "const_iterator:\n";
	or_const_iter or_it = _or_vector.begin();
	my_const_iter my_it = _my_vector.begin();

	while (or_it != _or_vector.end())
		or_ss << *(or_it++) << " ";
	while (my_it != _my_vector.end())
		my_ss << *(my_it++) << " ";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "const_reverse_iterator:\n";
	or_const_rev_iter or_rev_it = _or_vector.rbegin();
	my_const_rev_iter my_rev_it = _my_vector.rbegin();
	or_ss.str("");
	my_ss.str("");
	while (or_rev_it != _or_vector.rend())
		or_ss << *(or_rev_it++) << " ";
	while (my_rev_it != _my_vector.rend())
		my_ss << *(my_rev_it++) << " ";
	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-------------------------\n";
}

template <typename T>
void VectorTest<T>::operator_skoba_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	for (size_t i = 0; i < _or_vector.size(); i++)
		or_ss << _or_vector[i] << " ";
	for (size_t i = 0; i < _my_vector.size(); i++)
		my_ss << _my_vector[i] << " ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-------------------------\n";
}

template <typename T>
void VectorTest<T>::at_test()
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	for (size_t i = 0; i < _or_vector.size(); i++)
		or_ss << _or_vector.at(i) << " ";
	for (size_t i = 0; i < _my_vector.size(); i++)
		my_ss << _my_vector.at(i) << " ";

	try
	{
		_or_vector.at(_or_vector.size());
	}
	catch(const std::exception& e)
	{
		or_ss << e.what();
	}

	try
	{
		_my_vector.at(_my_vector.size());
	}
	catch (const std::exception &e)
	{
		my_ss << e.what();
	}

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-------------------------\n";
}

template <typename T>
void VectorTest<T>::insert_test(const T &value)
{
	or_iter or_temp = _or_vector.begin();
	my_iter my_temp = _my_vector.begin();

	std::cout << "---before---\n";
	test();
	std::cout << "---\n";

	insert(or_temp, my_temp, value);
	test();
	std::cout << "---\n";

	or_temp = _or_vector.begin();
	my_temp = _my_vector.begin();
	or_temp++;
	my_temp++;
	if (_or_vector.size())
	{
		insert(or_temp, my_temp, value);
		test();
		std::cout << "---\n";
	}

	insert(_or_vector.end(), _my_vector.end(), value);
	test();
	std::cout << "------------------\n";
}

template <typename T>
void VectorTest<T>::insert_test(size_t count, const T &value)
{
	or_iter or_temp = _or_vector.begin();
	my_iter my_temp = _my_vector.begin();

	std::cout << "---before---\n";
	test();
	std::cout << "---\n";

	insert(or_temp, my_temp, count, value);
	test();
	std::cout << "---\n";

	or_temp = _or_vector.begin();
	my_temp = _my_vector.begin();
	or_temp++;
	my_temp++;
	if (_or_vector.size())
	{
		insert(or_temp, my_temp, count, value);
		test();
		std::cout << "---\n";
	}

	insert(_or_vector.end(), _my_vector.end(), count, value);
	test();
	std::cout << "------------------\n";
}

template <typename T>
template <typename InputIt>
void VectorTest<T>::insert_test(InputIt first, InputIt last)
{
	or_iter or_temp = _or_vector.begin();
	my_iter my_temp = _my_vector.begin();

	std::cout << "---before---\n";
	test();
	std::cout << "---\n";

	insert(or_temp, my_temp, first, last);
	test();
	std::cout << "---\n";

	or_temp = _or_vector.begin();
	my_temp = _my_vector.begin();
	or_temp++;
	my_temp++;
	if (_or_vector.size())
	{
		insert(or_temp, my_temp, first, last);
		test();
		std::cout << "---\n";
	}

	insert(_or_vector.end(), _my_vector.end(), first, last);
	test();
	std::cout << "------------------\n";
}

template <typename T>
void VectorTest<T>::erase_test()
{
	or_iter or_temp = _or_vector.begin();
	my_iter my_temp = _my_vector.begin();

	std::cout << "before:\n";
	test();
	std::cout << "---\n";
	std::cout << "first elem\n";
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "second elem\n";
	or_temp = _or_vector.begin();
	my_temp = _my_vector.begin();
	or_temp++;
	my_temp++;
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "third elem\n";
	or_temp = _or_vector.begin();
	my_temp = _my_vector.begin();
	or_temp++;
	my_temp++;
	or_temp++;
	my_temp++;
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "last elem\n";
	or_temp = _or_vector.end();
	my_temp = _my_vector.end();
	or_temp--;
	my_temp--;
	erase(or_temp, my_temp);
	compare();
	test();
	std::cout << "------------------\n";
}

template <typename T>
void VectorTest<T>::erase_test_first_last()
{
	or_iter or_temp = _or_vector.begin();
	or_iter or_temp2 = _or_vector.begin();
	my_iter my_temp = _my_vector.begin();
	my_iter my_temp2 = _my_vector.begin();

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
	or_temp = ++_or_vector.begin();
	my_temp = ++_my_vector.begin();
	or_temp2 = or_temp;
	my_temp2 = my_temp;
	my_temp2++; my_temp2++; or_temp2++; or_temp2++;
	erase(or_temp, or_temp2, my_temp, my_temp2);
	compare();
	test();
	std::cout << "---\n";

	std::cout << "all elems\n";
	test();
	erase(_or_vector.begin(), _or_vector.end(), _my_vector.begin(), _my_vector.end());
	compare();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void VectorTest<T>::swap_test(VectorTest<T> &other)
{
	std::cout << "Before swap:\n";
	other.test();
	test();
	std::cout << "After swap:\n";
	_or_vector.swap(other._or_vector);
	_my_vector.swap(other._my_vector);
	other.test();
	test();
	std::cout << "After swap: (non member)\n";
	swap(_or_vector, other._or_vector);
	swap(_my_vector, other._my_vector);
	other.test();
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void VectorTest<T>::assign_test(size_t count, const T & value)
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
void VectorTest<T>::assign_test(InputIt first, InputIt last)
{
	std::cout << "Before assignment:\n";
	test();
	std::cout << "After assignment:\n";
	assign(first, last);
	test();
	std::cout << "-----------------\n";
}

template <typename T>
void VectorTest<T>::oper_equial_test(VectorTest<T> &other)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	test();
	other.test();
	std::cout << std::endl;

	or_ss << "  ==: " << (_or_vector == other._or_vector) << " swap " << (other._or_vector == _or_vector) << " | ";
	my_ss << "  ==: " << (_my_vector == other._my_vector) << " swap " << (other._my_vector == _my_vector) << " | ";

	or_ss << "!=: " << (_or_vector != other._or_vector) << " swap " << (other._or_vector != _or_vector) << " | ";
	my_ss << "!=: " << (_my_vector != other._my_vector) << " swap " << (other._my_vector != _my_vector) << " | ";

	or_ss << "<: " << (_or_vector < other._or_vector) << " swap " << (other._or_vector < _or_vector) << " | ";
	my_ss << "<: " << (_my_vector < other._my_vector) << " swap " << (other._my_vector < _my_vector) << " | ";

	or_ss << ">: " << (_or_vector > other._or_vector) << " swap " << (other._or_vector > _or_vector) << " | ";
	my_ss << ">: " << (_my_vector > other._my_vector) << " swap " << (other._my_vector > _my_vector) << " | ";

	or_ss << "<=: " << (_or_vector <= other._or_vector) << " swap " << (other._or_vector <= _or_vector) << " | ";
	my_ss << "<=: " << (_my_vector <= other._my_vector) << " swap " << (other._my_vector <= _my_vector) << " | ";

	or_ss << ">=: " << (_or_vector >= other._or_vector) << " swap " << (other._or_vector >= _or_vector) << " | ";
	my_ss << ">=: " << (_my_vector >= other._my_vector) << " swap " << (other._my_vector >= _my_vector) << " | ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
	compare();
	std::cout << "-----------------\n";
}

// /*
// ** ------------------------------
// **            Methods
// ** ------------------------------
// */

template <typename T>
void VectorTest<T>::compare()
{
	std::cout << "ft  |" << _my_vector.size() << "| " << _my_str << std::endl
			  << "std |" << _or_vector.size() << "| " << _or_str << std::endl;
	this->print_error(_my_vector.size() == _or_vector.size() && !_my_str.compare(_or_str));
}

template <typename T>
void VectorTest<T>::to_string()
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_iter or_it = _or_vector.begin();
	my_iter my_it = _my_vector.begin();

	while (or_it != _or_vector.end())
		or_ss << *(or_it++) << " ";

	while (my_it != _my_vector.end())
		my_ss << *(my_it++) << " ";

	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void VectorTest<T>::resize(int count, const T &value)
{
	if (value != T())
	{
		_or_vector.resize(count, value);
		_my_vector.resize(count, value);
	}
	else
	{
		_or_vector.resize(count);
		_my_vector.resize(count);
	}
}

template <typename T>
void VectorTest<T>::push_back(const T &value)
{
	_my_vector.push_back(value);
	_or_vector.push_back(value);
}

template <typename T>
void VectorTest<T>::pop_back()
{
	_my_vector.pop_back();
	_or_vector.pop_back();
}

template <typename T>
void VectorTest<T>::insert(or_iter or_pos, my_iter my_pos, size_t count, const T &value)
{
	_or_vector.insert(or_pos, count, value);
	_my_vector.insert(my_pos, count, value);
}

template <typename T>
void VectorTest<T>::insert(or_iter or_pos, my_iter my_pos, const T &value)
{
	std::stringstream or_ss;
	std::stringstream my_ss;

	or_ss << *(_or_vector.insert(or_pos, value));
	my_ss << *(_my_vector.insert(my_pos, value));

	_or_str = or_ss.str();
	_my_str = my_ss.str();

	compare();
}

template <typename T>
template <typename InputIt>
void VectorTest<T>::insert(or_iter or_pos, my_iter my_pos, InputIt first, InputIt last)
{
	_or_vector.insert(or_pos, first, last);
	_my_vector.insert(my_pos, first, last);
}

template <typename T>
void VectorTest<T>::clear()
{
	_or_vector.clear();
	_my_vector.clear();
}

template <typename T>
void VectorTest<T>::erase(or_iter or_pos, my_iter my_pos)
{
	std::stringstream or_ss;
	std::stringstream my_ss;
	or_iter or_tmp;
	my_iter my_tmp;

	or_tmp = _or_vector.erase(or_pos);
	my_tmp = _my_vector.erase(my_pos);
	if (or_tmp != _or_vector.end() && my_tmp != _my_vector.end())
	{
		or_ss << "|" << *(or_tmp) << "|";
		my_ss << "|" << *(my_tmp) << "|";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void VectorTest<T>::erase(or_iter or_first, or_iter or_last, my_iter my_first, my_iter my_last)
{
	std::stringstream	or_ss;
	std::stringstream	my_ss;
	or_iter				or_tmp;
	my_iter				my_tmp;

	or_tmp = _or_vector.erase(or_first, or_last);
	my_tmp = _my_vector.erase(my_first, my_last);
	if (or_tmp != _or_vector.end() && my_tmp != _my_vector.end())
	{
		or_ss << "|" << *(or_tmp) << "|";
		my_ss << "|" << *(my_tmp) << "|";
	}
	_or_str = or_ss.str();
	_my_str = my_ss.str();
}

template <typename T>
void VectorTest<T>::assign(size_t count, const T & value)
{
	_or_vector.assign(count, value);
	_my_vector.assign(count, value);
}

template <typename T>
template <typename InputIt>
void VectorTest<T>::assign(InputIt first, InputIt last)
{
	_or_vector.assign(first, last);
	_my_vector.assign(first, last);
}
