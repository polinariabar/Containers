#pragma once

#include <limits>
#include <memory>
#include <iostream>
#include <vector>
#include "vector_iterator.hpp"
#include "is_integer.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T							value_type;
		typedef Alloc						allocator_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef size_t						size_type;
		typedef std::ptrdiff_t				difference_type;

		typedef VectorIterator<T>			iterator;
		typedef ConstVectorIterator<T>		const_iterator;
		typedef RevVectorIterator<T>		reverse_iterator;
		typedef ConstRevVectorIterator<T> 	const_reverse_iterator;

	private:
		pointer								_ptr;
		size_type							_size;
		size_type							_capacity;
		allocator_type						_alloc;

		void					_assign(size_type count, const T &value, ft::is_int);
		template <typename InputIt>
		void					_assign(InputIt first, InputIt last, ft::not_int);
		void					_insert(iterator pos, size_type count, const T &value, ft::is_int);
	 	template <typename InputIt>
		void					_insert(iterator pos, InputIt first, InputIt last, ft::not_int);


	public:
		explicit vector(const Alloc &alloc = Alloc());
		explicit vector(size_type count, const value_type &value = value_type(), const Alloc & alloc = Alloc());
				 vector(const vector &other);
	 	template <typename InputIt>
	 			 vector(InputIt first, InputIt last);
	 			~vector();

	 	vector<T, Alloc> &		operator=(const vector<T, Alloc> &other);

	// element access
	 	reference				front() 				{return (_ptr[0]);}
	 	const_reference 		front()	const 			{return (_ptr[0]);}
	 	reference				back() 					{return (_ptr[_size - 1]);}
	 	const_reference			back()	const 			{return (_ptr[_size - 1]);}
		reference				operator[](size_type n) {return (_ptr[n]);}
		const_reference			operator[](size_type n) const
														{return (_ptr[n]);}
		reference 				at(size_type n);
		const_reference			at(size_type n) const;

	// iterators
	 	iterator				begin()					{return (iterator(_ptr));}
		const_iterator			begin() const			{return (const_iterator(_ptr));}
		iterator				end()					{return (iterator(&(_ptr[_size])));}
	 	const_iterator			end() 	const			{return (const_iterator(&(_ptr[_size])));}
	 	reverse_iterator		rbegin()				{return (reverse_iterator(&(_ptr[_size - 1])));}
	 	const_reverse_iterator	rbegin()const			{return (const_reverse_iterator(&(_ptr[_size - 1])));}
	 	reverse_iterator		rend()					{return (reverse_iterator(_ptr - 1));}
	 	const_reverse_iterator	rend()	const			{return (const_reverse_iterator(_ptr - 1));}
	
	// capacity
		bool					empty()	const			{return (_size == 0);}
		size_type				size()	const			{return (_size);}
		size_type				capacity()	const		{return (_capacity);}
	 	size_type				max_size() const;
		void					resize(size_type count, value_type value = value_type());
		void					reserve(size_type n);

		// modifiers
		void					clear();
		void					assign(size_type count, const T &value);
		template <typename InputIt>
		void					assign(InputIt first, InputIt last);
		void					push_back(const value_type &value);
		void					pop_back();
		iterator				insert(iterator pos, const T& value);
	 	void					insert(iterator pos, size_type count, const T &value);
	 	template <typename InputIt>
		void					insert(iterator pos, InputIt first, InputIt last);
		iterator				erase(iterator pos);
		iterator				erase(iterator first, iterator last);
		void					swap(vector & other);
	 	
	};

/*
** ------------------------------------------------------------------------
**                              Constructors
** ------------------------------------------------------------------------
*/

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(const Alloc &alloc)
	{
		_size		= 0;
		_capacity 	= 0;
		_ptr		= nullptr;
		_alloc		= alloc;
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(size_t count, const value_type &value, const Alloc &alloc) 
	{
		_alloc		= alloc;
		_size 		= count;
		_capacity 	= 0;
		_ptr		= nullptr;
		
		reserve(count);
		for (size_t i = 0; i != count; i++)
			new (&_ptr[i]) value_type(value);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::vector(const vector & other)
	{
		_alloc		= other._alloc;
		_size 		= other._size;
		_capacity 	= 0;
		_ptr		= nullptr;

		reserve(other._capacity);
		for (size_t i = 0; i != other._size; i++)
			new (&_ptr[i]) value_type(other._ptr[i]);
	}

	template <typename T, typename Alloc>
	template <typename InputIt>
	vector<T, Alloc>::vector(InputIt first, InputIt last)
	{
		_size 		= 0;
		_capacity 	= 0;
		_ptr		= nullptr;
		assign(first, last);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc>::~vector()
	{
		::operator delete(_ptr);
	}

	template <typename T, typename Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc> &other)
	{
		if (_ptr)
			::operator delete(_ptr);
		_alloc		= other._alloc;
		_size 		= other._size;
		_capacity 	= 0;
		_ptr		= nullptr;

		reserve(other._capacity);
		for (size_t i = 0; i != other._size; i++)
			new (&_ptr[i]) value_type(other._ptr[i]);

		return (*this);
	}

/*
** ------------------------------------------------------------------------
**     					     Element access
** ------------------------------------------------------------------------
*/
	template <typename T, typename Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return (_ptr[n]);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return (_ptr[n]);
	}

/*
** ------------------------------------------------------------------------
**     						  Modifiers
** ------------------------------------------------------------------------
*/

	template <typename T, typename Alloc>
	void vector<T, Alloc>::push_back(const value_type &value)
	{
		if (_capacity == _size)
			reserve(_capacity + 1);
	
		new(&_ptr[_size]) value_type(value);
		_size++;
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::pop_back()
	{
		if (!_size)
			return;
		_ptr[_size - 1].~value_type();
		_size--;
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::clear()
	{
		for (size_t i = 0; i < _size; i++)
			_ptr[i].~value_type();
		_size = 0;
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::assign(size_type count, const T &value)
	{
		clear();
		reserve(count);
		while (_size < count)
			push_back(value);
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::_assign(size_type count, const T &value, ft::is_int)
	{
		clear();
		reserve(count);
		while (_size < count)
			push_back(value);
	}

	template <typename T, typename Alloc>
	template <typename InputIt>
	void vector<T, Alloc>::_assign(InputIt first, InputIt last, ft::not_int)
	{
		clear();
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}

	template <typename T, typename Alloc>
	template <typename InputIt>
	void vector<T, Alloc>::assign(InputIt first, InputIt last)
	{
		typedef typename ft::is_integer<InputIt>::type res;
		_assign(first, last, res());
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::insert(iterator pos, size_type count, const T &value)
	{
		size_t i = 0;
		iterator it = begin();

		reserve(_size + count);

		while (it++ != pos)
			i++;

		for (size_t j = _size - 1; j != i - 1; j--)
		{
			if (j + count < _size)
				_ptr[j + count] = _ptr[j];
			else
				new(&_ptr[j + count]) value_type(_ptr[j]);
		}

		for (size_t j = 0; j < count; j++)
		{
			if (i < _size)
				_ptr[i++] = value;
			else
				new(&_ptr[i++]) value_type(value);
		}
		_size += count;
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator pos, const T &value)
	{
		size_t i = 0;
		for (iterator it = begin(); it != pos; it++)
			i++;
		insert(pos, 1, value);
		return (iterator(&(_ptr[i])));
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::_insert(iterator pos, size_type count, const T &value, ft::is_int)
	{
		size_t i = 0;
		iterator it = begin();

		reserve(_size + count);

		while (it++ != pos)
			i++;

		for (size_t j = _size - 1; j != i - 1; j--)
		{
			if (j + count < _size)
				_ptr[j + count] = _ptr[j];
			else
				new(&_ptr[j + count]) value_type(_ptr[j]);
		}

		for (size_t j = 0; j < count; j++)
		{
			if (i < _size)
				_ptr[i++] = value;
			else
				new(&_ptr[i++]) value_type(value);
		}
		_size += count;
	}

	template <typename T, typename Alloc>
	template <typename InputIt>
	void vector<T, Alloc>::_insert(iterator pos, InputIt first, InputIt last, ft::not_int)
	{
		size_t i = 0;
		size_t count = 0;
		iterator it = begin();
		InputIt tmp = first;

		while (it++ != pos)
			i++;
		while (tmp++ != last)
			count++;
		reserve(_size + count);

		for (size_t j = _size - 1; j != i - 1; j--)
		{
			if (j + count < _size)
				_ptr[j + count] = _ptr[j];
			else
				new(&_ptr[j + count]) value_type(_ptr[j]);
		}
		for (size_t j = 0; j < count; j++)
		{
			if (i < _size)
				_ptr[i++] = *first++;
			else
				new(&_ptr[i++]) value_type(*first++);
		}
		_size += count;
	}

	template <typename T, typename Alloc>
	template <typename InputIt>
	void vector<T, Alloc>::insert(iterator pos, InputIt first, InputIt last)
	{
		typedef typename ft::is_integer<InputIt>::type res;
		_insert(pos, first, last, res());
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator pos)
	{
		size_t		i	= 0;
		iterator	it = begin();

		while (it++ != pos)
			i++;

		for (size_t j = i; j != _size - 1; j++)
			_ptr[j] = _ptr[j + 1];

		pop_back();
		return (--it);
	}

	template <typename T, typename Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		size_t		count_first = 0;
		size_t		count		= 0;
		iterator	it 			= begin();

		while (it++ != first)
			count_first++;
		while (first++ != last)
			count++;

		if (count != 0)
		{
			for (size_t j = count_first; j + count < _size; j++)
				_ptr[j] = _ptr[j + count];
		}
		while (count--)
			pop_back();
		if (_size == 0)
			return (begin());
		return (--it);
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::swap(vector &other)
	{
		size_t old_size = _size;
		pointer tmp = static_cast<pointer>(::operator new(sizeof(value_type) * _size));
		if (_size)
			for (size_t i = 0; i < _size; i++)
				new (&tmp[i]) value_type(_ptr[i]);
		clear();
		for (size_t i = 0; i < other.size(); i++)
			push_back(other[i]);

		other.clear();
		for (size_t i = 0; i < old_size; i++)
			other.push_back(tmp[i]);

		::operator delete(tmp);
	}

/*
** ------------------------------------------------------------------------
**     					   	  Capacity
** ------------------------------------------------------------------------
*/

	template <typename T, typename Alloc>
	void vector<T, Alloc>::reserve(size_type n)
	{
		if (n <= _capacity)
			return;
		if (_capacity * 2 > n)
			n = _capacity * 2;
		if (n > max_size())
			n = max_size();
		pointer tmp = static_cast<pointer>(::operator new(sizeof(value_type) * n));
		if (_ptr)
		{
			for (size_t i = 0; i < _size; i++)
				new(&tmp[i]) value_type(_ptr[i]);
			::operator delete(_ptr);
			_ptr = nullptr;
		}
		_ptr = tmp;
		_capacity = n;
	}

	template <typename T, typename Alloc>
	void vector<T, Alloc>::resize(size_type count, value_type value)
	{
		while (_size < count)
			push_back(value);
		while (_size > count)
			pop_back();
	}

	template <typename T, typename Alloc>
	size_t vector<T, Alloc>::max_size() const
	{
		size_t diff_max;
		size_t size_max;

		diff_max = std::numeric_limits<difference_type>::max();
		size_max = std::numeric_limits<size_type>::max() / sizeof(value_type);
		return (diff_max < size_max ? diff_max : size_max);
	}

/*
** ------------------------------------------------------------------------
**     						  Non member
** ------------------------------------------------------------------------
*/
	template <typename T, typename Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

	template <typename _T, typename Alloc>
	bool operator==(const vector<_T, Alloc> &lhs, const vector<_T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template <typename _T, typename Alloc>
	bool operator!=(const vector<_T, Alloc> &lhs, const vector<_T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return true;
		return false;
	}

	template <typename _T, typename Alloc>
	bool operator<(const vector<_T, Alloc> &lhs, const vector<_T, Alloc> &rhs)
	{
		for (size_t i = 0; i < lhs.size() && i < rhs.size(); i++)
		{
			if (lhs[i] > rhs[i])
				return false;
			else if (lhs[i] < rhs[i])
				return true;
		}
		if (lhs.size() < rhs.size())
			return true;
		return false;
	}

	template <typename _T, typename Alloc>
	bool operator>(const vector<_T, Alloc> &lhs, const vector<_T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename _T, typename Alloc>
	bool operator<=(const vector<_T, Alloc> &lhs, const vector<_T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename _T, typename Alloc>
	bool operator>=(const vector<_T, Alloc> &lhs, const vector<_T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}