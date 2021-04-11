#pragma once

#include "list.hpp"
#include <iostream>
class list;

namespace ft
{
	template <typename _T>
	class ListIterator
	{
	public:
		typedef _T						value_type;
		typedef _T&						reference;
		typedef _T*						pointer;
		typedef __list_node<_T> *		node_pointer;
		node_pointer					_node;

	public:
		ListIterator() 					: _node(nullptr) {}
		ListIterator(node_pointer p) 	: _node(p) {}

		ListIterator &	operator=(const ListIterator &src)	{ _node = src._node; return (*this); }
		reference &		operator*() const					{ return (_node->element); }
		ListIterator &	operator++()						{ _node = _node->next; return (*this); }
		ListIterator &	operator--()						{ _node = _node->prev; return (*this); }
		ListIterator	operator++(int)		
															{ 
																ListIterator curr = *this;
																_node = _node->next;
																return (curr);
															}
		ListIterator	operator--(int)
															{
																ListIterator curr = *this;
																_node = _node->prev;
																return (curr);
															}
		bool			operator==(const ListIterator & second) const
															{ return (_node == second._node); }
		bool			operator!=(const ListIterator & second) const
															{ return (_node != second._node); }
	};

	template <typename _T>
	class ConstListIterator
	{
	public:
		typedef const _T								value_type;
		typedef const _T&								reference;
		typedef const _T*								pointer;
		typedef __list_node<_T> *						node_pointer;
		node_pointer									_node;

	public:
		ConstListIterator() 				: _node(nullptr) {}
		ConstListIterator(node_pointer p) 	: _node(p) {}
		ConstListIterator(const ListIterator<_T> &src) : _node(src._node) {}

		ConstListIterator &	operator=(const ConstListIterator &src)	{ _node = src._node; return (*this); }
		ConstListIterator &	operator=(const ListIterator<_T> &src)	{ _node = src._node; return (*this); }
		reference &			operator*() const					{ return (_node->element); }
		ConstListIterator &	operator++()						{ _node = _node->next; return (*this); }
		ConstListIterator &	operator--()						{ _node = _node->prev; return (*this); }
		ConstListIterator	operator++(int)		
																{ 
																	ConstListIterator curr = *this;
																	_node = _node->next;
																	return (curr);
																}
		ConstListIterator	operator--(int)
																{
																	ConstListIterator curr = *this;
																	_node = _node->prev;
																	return (curr);
																}
		bool			operator==(const ConstListIterator & second) const
																{ return (_node == second._node); }
		bool			operator!=(const ConstListIterator & second) const
																{ return (_node != second._node); }
	};

	template <typename _T>
	class ListRevIterator
	{
	public:
		typedef _T						value_type;
		typedef _T&						reference;
		typedef _T*						pointer;
		typedef __list_node<_T> *		node_pointer;
		node_pointer					_node;

	public:
		ListRevIterator() 								  : _node(NULL) {}
		ListRevIterator(node_pointer p) 				  : _node(p) {}
		
		ListRevIterator &	operator=(const ListRevIterator &src)	{ _node = src._node; return (*this); }
		reference &			operator*() const				{ return (_node->element); }
		ListRevIterator &	operator++()					{ _node = _node->prev; return (*this); }
		ListRevIterator &	operator--()					{ _node = _node->next; return (*this); }
		ListRevIterator		operator++(int)		
															{
																ListRevIterator curr = *this;
																_node = _node->prev;
																return (curr);
															}
		ListRevIterator		operator--(int)
															{
																ListRevIterator curr = *this;
																_node = _node->next;
																return (curr);
															}
		bool				operator==(const ListRevIterator & second) const
															{ return (_node == second._node); }
		bool				operator!=(const ListRevIterator & second) const
															{ return (_node != second._node); }
	};

	template <typename _T>
	class ConstListRevIterator
	{
	public:
		typedef const _T						value_type;
		typedef const _T&						reference;
		typedef const _T*						pointer;
		typedef __list_node<_T> *				node_pointer;
		node_pointer							_node;

	public:
		ConstListRevIterator() 								  : _node(NULL) {}
		ConstListRevIterator(node_pointer p) 				  : _node(p) {}
		ConstListRevIterator(const ListRevIterator<_T> &src)  : _node(src._node) {}

		ConstListRevIterator &	operator=(const ConstListRevIterator &src)	{ _node = src._node; return (*this); }
		ConstListRevIterator &	operator=(const ListRevIterator<_T> &src)	{ _node = src._node; return (*this); }
		reference &				operator*() const							{ return (_node->element); }
		ConstListRevIterator &	operator++()								{ _node = _node->prev; return (*this); }
		ConstListRevIterator &	operator--()								{ _node = _node->next; return (*this); }
		ConstListRevIterator	operator++(int)		
																			{
																				ConstListRevIterator curr = *this;
																				_node = _node->prev;
																				return (curr);
																			}
		ConstListRevIterator		operator--(int)
																			{
																				ConstListRevIterator curr = *this;
																				_node = _node->next;
																				return (curr);
																			}
		bool				operator==(const ConstListRevIterator & second) const
																			{ return (_node == second._node); }
		bool				operator!=(const ConstListRevIterator & second) const
																			{ return (_node != second._node); }
	};
}