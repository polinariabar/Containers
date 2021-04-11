#pragma once

#include <limits>
#include <memory>
#include <iostream>
#include "list.hpp"

namespace ft
{
	template <typename T, typename Container = ft::list<T> >
	class stack
	{
	public:
		typedef T							value_type;
		typedef size_t						size_type;
		typedef Container					container_type;
		container_type						_container;

	public:
		explicit stack(const container_type & cntr = container_type()) : _container(cntr) {}
	 			 stack(const stack &other) : _container(other._container) {}
	 			~stack() {};

	 	stack<T, Container> &	operator=(const stack<T, Container> &other) {_container = other._container; return (*this);}
	 	bool					empty()	const								{return (_container.empty());}
		size_type				size()	const								{return (_container.size());}
		value_type &			top()										{return (_container.back());}
		const value_type &		top() const									{return (_container.back());}
		void					push(const value_type &value)				{_container.push_back(value);}
		void					pop()										{_container.pop_back();}
	};

/*
** ------------------------------------------------------------------------
**     						  Non member
** ------------------------------------------------------------------------
*/
	template <typename T, typename Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._container == rhs._container);
	}

	template <typename T, typename Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._container != rhs._container);
	}

	template <typename T, typename Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._container < rhs._container);
	}

	template <typename T, typename Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._container > rhs._container);
	}

	template <typename T, typename Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._container <= rhs._container);
	}

	template <typename T, typename Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._container >= rhs._container);
	}
}