#pragma once

#include "node.hpp"
#include "iterator.hpp"
#include "is_integer.hpp"
#include <limits>
#include <memory>
#include <iostream>

namespace ft
{	
	template <typename _T, typename Alloc = std::allocator<_T> >
	class list
	{
	public:
		typedef _T							value_type;
		typedef Alloc						allocator_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef value_type*					pointer;
		typedef const value_type*			const_pointer;
		typedef size_t						size_type;

		typedef ListIterator<_T>			iterator;
		typedef ConstListIterator<_T>		const_iterator;
		typedef ListRevIterator<_T>			reverse_iterator;
		typedef ConstListRevIterator<_T> 	const_reverse_iterator;

	private:
		typedef __list_node<_T>				_node;
		typedef _node *						_node_pointer;

		_node_pointer						_end;
		size_type							_size;
		allocator_type						_alloc;

		void								init(const Alloc &alloc = Alloc());
		template <typename T1>
		void								_insert(iterator pos, int count, T1 value, ft::is_int);
		template <typename InputIt>
		void								_insert(iterator pos, InputIt first, InputIt last, ft::not_int);
		void								_assign(size_type count, const _T &value, ft::is_int);
		template <typename InputIt>
		void								_assign(InputIt first, InputIt last, ft::not_int);

	public:
		explicit list(const Alloc & alloc = Alloc());
	 	explicit list(size_type count, const value_type &value = value_type(), const Alloc & alloc = Alloc());
	 			 list(const list &other);
	 	template <typename InputIt>
	 			 list(InputIt first, InputIt last);
	 			~list();

	 	list<_T, Alloc> &		operator=(const list<_T, Alloc> &other);
	 	void					assign(size_type count, const _T &value);
	 	template <typename InputIt>
	 	void					assign(InputIt first, InputIt last);
	//  get_allocator

	// element access
	 	reference				front() 		{return (_end->next->element);}
	 	const_reference 		front()	const 	{return (_end->next->element);}
	 	reference				back() 			{return (_end->prev->element);}
	 	const_reference			back()	const 	{return (_end->prev->element);}

	// iterators
	 	iterator				begin()			{return (iterator(_end->next));}
		const_iterator			begin() const	{return (const_iterator(_end->next));}
		iterator				end()			{return (iterator(_end));}
	 	const_iterator			end() 	const	{return (const_iterator(_end));}
	 	reverse_iterator		rbegin()		{return (reverse_iterator(_end->prev));}
	 	const_reverse_iterator	rbegin()const	{return (const_reverse_iterator(_end->prev));}
	 	reverse_iterator		rend()			{return (reverse_iterator(_end));}
	 	const_reverse_iterator	rend()	const	{return (const_reverse_iterator(_end));}
	
	// capacity
	 	bool					empty()	const	{return (_size == 0);}
		size_type				size()	const	{return (_size);}
	 	size_type				max_size() const{return (std::numeric_limits<size_type>::max() / sizeof(_node));}

	// modifiers
	 	void					clear();
	 	iterator				insert(iterator pos, const _T& value);
	 	void					insert(iterator pos, size_type count, const _T &value);
	 	template <typename InputIt>
	 	void					insert(iterator pos, InputIt first, InputIt last);
		iterator				erase(iterator pos);
		iterator				erase(iterator first, iterator last);
		void					push_back(const value_type &value);
		void					push_front(const value_type &value);
		void					pop_back();
		void					pop_front();
		void					resize(size_type count, value_type value = value_type());
		void					swap(list & other);

	// оperations
		void					merge(list &x);
		template <class Compare>
  		void					merge (list& x, Compare comp);
		void					splice(const_iterator pos, list &other);
		void					splice(const_iterator pos, list &other, const_iterator it);
		void					splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
		void					remove(const value_type &value);
		template <class UnaryPredicate>
		void					remove_if(UnaryPredicate p);
		void					reverse();
		void					unique();
		template<class BinaryPredicate>
		void					unique(BinaryPredicate p);
		void					sort();
		template <typename Compare>
		void					sort(Compare comp);
	};

/*
** ------------------------------------------------------------------------
**                              Constructors
** ------------------------------------------------------------------------
*/

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::init(const Alloc &alloc)
	{
		_size = 0;
		_end = new __list_node<value_type>();
		_end->next = _end;
		_end->prev = _end;
		_alloc = alloc;
	}

	template <typename _T, typename Alloc>
	list<_T, Alloc>::list(const Alloc &alloc)
	{
		init(alloc);
	}

	template <typename _T, typename Alloc>
	list<_T, Alloc>::list(size_t count, const value_type &value, const Alloc &alloc) 
	{
		init(alloc);
		while (_size < count)
			push_back(value);
	}

	template <typename _T, typename Alloc>
	list<_T, Alloc>::list(const list & other)
	{
		init(other._alloc);
		_node_pointer cur = other._end->next;
		while (cur != other._end)
		{
			push_back(cur->element);
			cur = cur->next;
		}
	}

	template <typename _T, typename Alloc>
	template <typename InputIt>
	list<_T, Alloc>::list(InputIt first, InputIt last)
	{
		init();
		insert(begin(), first, last);
	}

	template <typename _T, typename Alloc>
	list<_T, Alloc>::~list()
	{
		clear();
		delete _end;
	}

	template <typename _T, typename Alloc>
	list<_T, Alloc> &list<_T, Alloc>::operator=(const list<_T, Alloc> &other)
	{
		clear();
		_node_pointer cur = other._end->next;
		while (cur != other._end)
		{
			push_back(cur->element);
			cur = cur->next;
		}
		return (*this);
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::assign(size_type count, const _T &value)
	{
		clear();
		while (_size < count)
			push_back(value);
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::_assign(size_type count, const _T &value, ft::is_int)
	{
		clear();
		while (_size < count)
			push_back(value);
	}

	template <typename _T, typename Alloc>
	template <typename InputIt>
	void list<_T, Alloc>::_assign(InputIt first, InputIt last, ft::not_int)
	{
		clear();
		while (first != last)
		{
			push_back(*first);
			first++;
		}
	}

	template <typename _T, typename Alloc>
	template <typename InputIt>
	void list<_T, Alloc>::assign(InputIt first, InputIt last)
	{
		typedef typename ft::is_integer<InputIt>::type res;
		_assign(first, last, res());
	}

/*
** ------------------------------------------------------------------------
**     						  Modifiers
** ------------------------------------------------------------------------
*/

	/*
	** -----------------------
	** Clear - clears all list
	** -----------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::clear()
	{
		while (_size)
			pop_back();
	}

	/*
	** ---------------------------
	** Insert - inserts element(s)
	** ---------------------------
	*/
	template <typename _T, typename Alloc>
	typename list<_T, Alloc>::iterator list<_T, Alloc>::insert(iterator pos, const _T &value)
	{
		_node_pointer curr = new _node(value);
		_size++;
		curr->next = pos._node;
		curr->prev = pos._node->prev;
		curr->prev->next = curr;
		curr->next->prev = curr;
		return (iterator(curr));
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::insert(iterator pos, size_type count, const _T &value)
	{
		while (count-- > 0)
			pos = insert(pos, value);
	}

	template <typename _T, typename Alloc>
	template <typename T1>
	void list<_T, Alloc>::_insert(iterator pos, int count, T1 value, ft::is_int)
	{
		while (count-- > 0)
			pos = insert(pos, value);
	}

	template <typename _T, typename Alloc>
	template <typename InputIt>
	void list<_T, Alloc>::_insert(iterator pos, InputIt first, InputIt last, ft::not_int)
	{
		while (first != last)
		{
			pos = insert(pos, *(first++));
			pos++;
		}
	}

	template <typename _T, typename Alloc>
	template <typename InputIt>
	void list<_T, Alloc>::insert(iterator pos, InputIt first, InputIt last)
	{
		typedef typename is_integer<InputIt>::type res;
		_insert(pos, first, last, res());
	}

	/*
	** ---------------------------
	** Erase - delete element(s)
	** ---------------------------
	*/
	template <typename _T, typename Alloc>
	typename list<_T, Alloc>::iterator list<_T, Alloc>::erase(iterator pos)
	{
		iterator curr_it = pos;
		_size--;
		_node_pointer curr = pos._node;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete curr;
		return(++curr_it);
	}

	template <typename _T, typename Alloc>
	typename list<_T, Alloc>::iterator list<_T, Alloc>::erase(iterator first, iterator last)
	{
		iterator curr_it = first;
		while (curr_it != last && curr_it != end())
			curr_it = erase(curr_it);
		return (curr_it);
	}

	/*
	** ---------------------------
	** Push - back and front
	** ---------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::push_back(const value_type &value)
	{
		_size++;
		_node_pointer curr 	= new __list_node<value_type>(value);
		curr->next 			= _end;
		curr->prev 			= _end->prev;
		_end->prev->next 	= curr;
		_end->prev 			= curr;
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::push_front(const value_type &value)
	{
		_size++;
		_node_pointer curr 	= new __list_node<value_type>(value);
		curr->prev 			= _end;
		curr->next 			= _end->next;
		_end->next->prev 	= curr;
		_end->next 			= curr;
	}

	/*
	** ---------------------------
	** Pop - back and front
	** ---------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::pop_back()
	{
		_size--;
		_node_pointer curr = _end->prev;
		curr->prev->next = _end;
		_end->prev = curr->prev;
		delete curr;
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::pop_front()
	{
		_size--;
		_node_pointer curr = _end->next;
		_end->next = curr->next;
		curr->next->prev = _end;
		delete curr;
	}

	/*
	** ---------------------------
	** Resize - resizes list
	** ---------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::resize(size_type count, value_type value)
	{
		while (count < _size)
			pop_back();
		while (count > _size)
			push_back(value);
	}

	/*
	** ---------------------------
	** Swap
	** ---------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::swap(list & other)
	{
		list<_T, Alloc> copy = *this;
		*this = other;
		other = copy;
		copy.clear();
	}

/*
** ------------------------------------------------------------------------
**     						  Modifiers
** ------------------------------------------------------------------------
*/
	/*
	** ---------------------------------
	** Sort - sorting in ascending order
	** ---------------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::sort()
	{
		iterator 	curr 	= begin();
		iterator 	next	= begin();
		iterator 	end_it	= end();
		value_type	data;

		if (_size <= 0)
			return ;
		while (++next != end_it)
		{
			if ((*next) < (*curr))
			{
				data = *next;
				*next = *curr;
				*curr = data;
				next = begin();
				curr = begin();
			}
			else
				curr++;
		}
	}

	template <typename _T, typename Alloc>
	template <typename Compare>
	void list<_T, Alloc>::sort(Compare comp)
	{
		iterator 	curr 	= begin();
		iterator 	next	= begin();
		iterator 	end_it	= end();
		value_type	data;

		if (_size <= 1)
			return ;
		while (++next != end_it)
		{
			if (comp(*next, *curr))
			{
				data  = *next;
				*next = *curr;
				*curr = data;
				next  = begin();
				curr  = begin();
			}
			else
				curr++;
		}
	}

	/*
	** ---------------------------------
	** Reverse - reverting order
	** ---------------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::reverse()
	{
		iterator 	first = begin();
		iterator 	last  = --end();
		value_type	data;
		size_t		i = 0;

		if (_size <= 1)
			return ;
		while (i < _size/2)
		{
			data 	= *first;
			*first 	= *last;
			*last	= data;
			first++;
			last--;
			i++;
		}
	}

	/*
	** ---------------------------------
	** Splice - adds elements from one to another
	** ---------------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::splice(const_iterator pos, list &other)
	{
		if (*this == other)
			return;

		_node_pointer next			= pos._node;
		_node_pointer prev			= (--pos)._node;
		_node_pointer firstnode		= other.begin()._node;
		_node_pointer lastnode		= (--other.end())._node;

		prev->next = firstnode;
		next->prev = lastnode;
		other.end()._node->next = other.end()._node;
		other.end()._node->prev = other.end()._node;
		firstnode->prev = prev;
		lastnode->next = next;
		
		 _size += other.size();
		other._size = 0;
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::splice(const_iterator pos, list &other, const_iterator it)
	{
		if (*this == other)
			return;

		_node_pointer next			= pos._node;
		--pos;
		_node_pointer prev			= pos._node;
		_node_pointer other_node	= it._node;

		other_node->prev->next 	= other_node->next;
		other_node->next->prev 	= other_node->prev;
		prev->next 				= other_node;
		other_node->prev		= prev;
		next->prev 				= other_node;
		other_node->next 		= next;

		_size++;
		other._size--;
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::splice(const_iterator pos, list &other, const_iterator first, const_iterator last)
	{
		if (*this == other)
			return;

		_node_pointer next			= pos._node;
		_node_pointer prev			= (--pos)._node;
		_node_pointer firstnode		= first._node;
		_node_pointer lastnode		= (--last)._node;
		size_t		  count			= 0;

		last++;
		if (first == last)
			return;
		while (first++ != last)
			count++;

		prev->next = firstnode;
		next->prev = lastnode;
		firstnode->prev->next = lastnode->next;
		lastnode->next->prev = firstnode->prev;
		firstnode->prev = prev;
		lastnode->next = next;

		_size += count;
		other._size -= count;
	}


	/*
	** ---------------------------------
	** Remove - removes elements
	** ---------------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::remove(const value_type &value)
	{
		_node_pointer curr = _end->next;
		_node_pointer tmp;

		while (curr != _end)
		{
			if (curr->element == value)
			{
				tmp = curr->next;
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				delete curr;
				curr = tmp;
				_size--;
			}
			else
				curr = curr->next;
		}
	}

	template <typename _T, typename Alloc>
	template <class UnaryPredicate>
	void list<_T, Alloc>::remove_if(UnaryPredicate p)
	{
		_node_pointer curr = _end->next;
		_node_pointer tmp;

		while (curr != _end)
		{
			if (p(curr->element))
			{
				tmp = curr->next;
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				delete curr;
				curr = tmp;
				_size--;
			}
			else
				curr = curr->next;
		}
	}

	/*
	** ---------------------------------
	** Unique - removes duplicate elements
	** ---------------------------------
	*/
	template <typename _T, typename Alloc>
	void list<_T, Alloc>::unique()
	{
		iterator curr = begin();
		iterator next = ++begin();

		while (next != end())
		{
			if (curr._node->element == next._node->element)
				next = erase(next);
			else
			{
				next++;
				curr++;
			}
		}
	}

	template <typename _T, typename Alloc>
	template< class BinaryPredicate >
	void list<_T, Alloc>::unique(BinaryPredicate p)
	{
		iterator curr = begin();
		iterator next = ++begin();

		while (next != end())
		{
			if (p(curr._node->element, next._node->element))
				next = erase(next);
			else
			{
				next++;
				curr++;
			}
		}
	}

	template <typename _T, typename Alloc>
	void list<_T, Alloc>::merge(list &x)
	{
		const_iterator next = begin();
		const_iterator x_curr = x.begin();
		const_iterator tmp;

		while (x_curr != x.end())
		{
			while(next._node->element < x_curr._node->element && next != end())
				next++;
			tmp = ++x_curr;
			splice(next, x, --x_curr);
			x_curr = tmp;
		}
	}

	template <typename _T, typename Alloc>
	template <class Compare>
  	void list<_T, Alloc>::merge (list& x, Compare comp)
	{
		const_iterator next		= begin();
		const_iterator x_curr	= x.begin();
		const_iterator tmp;

		if (size() == 0)
			splice(next, x, x.begin(), x.end());

		while (next != end())
		{
			while(comp(x_curr._node->element, next._node->element) 
				  && x_curr != x.end())
			{
				tmp = ++x_curr;
				splice(next, x, --x_curr);
				x_curr = tmp;
			}
			next++;
		}
		while(x.size() && x_curr != x.end())
		{
			tmp = ++x_curr;
			splice(next, x, --x_curr);
			x_curr = tmp;
		}
	}

/*
** ------------------------------------------------------------------------
**     						  Non member
** ------------------------------------------------------------------------
*/
	template <typename _T, typename Alloc>
	bool operator==(const list<_T,Alloc>& lhs, const list<_T,Alloc>& rhs)
	{
		typename ft::list<_T, Alloc>::const_iterator lit = lhs.begin();
		typename ft::list<_T, Alloc>::const_iterator rit = rhs.begin();

		if (lhs.size() != rhs.size())
			return false;
		while (lit != lhs.end() && rit != rhs.end())
		{
			if (*lit != *rit)
				return false;
			rit++;
			lit++;
		}
		return true;
	}

	template <typename _T, typename Alloc>
	bool operator!=(const list<_T,Alloc>& lhs, const list<_T,Alloc>& rhs)
	{
		typename ft::list<_T, Alloc>::const_iterator lit = lhs.begin();
		typename ft::list<_T, Alloc>::const_iterator rit = rhs.begin();

		if (lhs.size() != rhs.size())
			return true;
		while (lit != lhs.end() && rit != rhs.end())
		{
			if (*lit != *rit)
				return true;
			rit++;
			lit++;
		}
		return false;
	}

	template <typename _T, typename Alloc>
	bool operator<(const list<_T,Alloc>& lhs, const list<_T,Alloc>& rhs)
	{
		typename ft::list<_T, Alloc>::const_iterator lit = lhs.begin();
		typename ft::list<_T, Alloc>::const_iterator rit = rhs.begin();

		while (lit != lhs.end() && rit != rhs.end())
		{
			if (*lit < *rit)
				return true;
			else if (*lit > *rit)
				return false;
			rit++;
			lit++;
		}
		if (lhs.size() < rhs.size())
			return (true);
		return false;
	}

	template <typename _T, typename Alloc>
	bool operator>(const list<_T,Alloc>& lhs, const list<_T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <typename _T, typename Alloc>
	bool operator<=(const list<_T,Alloc>& lhs, const list<_T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename _T, typename Alloc>
	bool operator>=(const list<_T,Alloc>& lhs, const list<_T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
	template <typename _T, typename Alloc>
	void swap (list<_T,Alloc>& x, list<_T,Alloc>& y)
	{
		x.swap(y);
	}
}