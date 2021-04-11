#pragma once

#include <limits>
#include <memory>
#include <iostream>
#include "list.hpp"

namespace ft
{
	template <typename T, typename Container = ft::list<T> >
	class queue
	{
	public:
		typedef T							value_type;
		typedef value_type &				reference;
		typedef const value_type &			const_reference;
		typedef size_t						size_type;
		typedef Container					container_type;
		container_type						_container;

	public:
		explicit queue(const container_type & cntr = container_type()) : _container(cntr) {}
	 			 queue(const queue &other) : _container(other._container) {}
	 			~queue() {};

	 	queue<T, Container> &	operator=(const queue<T, Container> &other) {_container = other._container; return (*this);}
	 	bool					empty()	const								{return (_container.empty());}
		size_type				size()	const								{return (_container.size());}
		reference				front()										{return (_container.front());}
		const_reference			front() const								{return (_container.front());}
		reference				back()										{return (_container.back());}
		const_reference			back() const								{return (_container.back());}
		void					push(const value_type &value)				{_container.push_back(value);}
		void					pop()										{_container.pop_front();}
	};

/*
** ------------------------------------------------------------------------
**     						  Non member
** ------------------------------------------------------------------------
*/
	template <typename T, typename Container>
	bool operator==(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._container == rhs._container);
	}

	template <typename T, typename Container>
	bool operator!=(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._container != rhs._container);
	}

	template <typename T, typename Container>
	bool operator<(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._container < rhs._container);
	}

	template <typename T, typename Container>
	bool operator>(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._container > rhs._container);
	}

	template <typename T, typename Container>
	bool operator<=(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._container <= rhs._container);
	}

	template <typename T, typename Container>
	bool operator>=(const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (lhs._container >= rhs._container);
	}
}