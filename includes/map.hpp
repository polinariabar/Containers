#pragma once

#include "map_tree.hpp"
#include <limits>
#include <memory>
#include <iostream>

namespace ft
{
	template <typename Key,												  // map::key_type
			  typename T,												  // map::mapped_type
			  typename Compare = std::less<Key>,						  // map::key_compare
			  typename Alloc = std::allocator<std::pair<const Key, T> > > // map::allocator_type>
	class map
	{
	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef std::pair<const key_type,mapped_type>	value_type;
		typedef Alloc									allocator_type;
		typedef Compare									key_compare;
		typedef size_t									size_type;
		typedef value_type &							reference;
		typedef const value_type &						const_reference;
		typedef value_type *							pointer;
		typedef const value_type *						const_pointer;
		typedef Tree<Key, T, key_compare> 				tree_type;

		typedef MapIterator<T, Key>						iterator;
		typedef ConstMapIterator<T, Key> 				const_iterator;
		typedef RevMapIterator<T, Key> 					reverse_iterator;
		typedef ConstRevMapIterator<T, Key> 			const_reverse_iterator;

		class value_compare
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c = key_compare()) : comp(c){};

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		private : 
		typedef __map_node<Key, T>		_node;
		typedef _node *					_node_pointer;
		allocator_type					_alloc;
		key_compare						_comp;
		value_compare					_value_comp;
		tree_type						_tree;

	public:
	/*
	** --------------------------------------------------------------------------------
	**                               Constructors & other
	** --------------------------------------------------------------------------------
	*/
		explicit
		map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp) {}//, _value_comp(comp) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_alloc = alloc;
			_comp = comp;
			_value_comp = _comp;
			insert(first, last);
		}
		map(const map &x)
		{
			_alloc = x._alloc;
			_comp = x._comp;
			_value_comp = x._value_comp;
			insert(x.begin(), x.end());
		}
		~map()
		{
			clear();
			delete _tree._end;
		}
		map &operator=(const map &x)
		{
			clear();
			insert(x.begin(), x.end());
			return (*this);
		}

		/*
	** --------------------------------------------------------------------------------
	**                                  Capacity
	** --------------------------------------------------------------------------------
	*/
		bool					empty() const		{return (_tree._size == 0);}
		size_type				size() const		{return (_tree._size);}
		size_type				max_size() const
		{
			return (std::numeric_limits<size_type>::max() / (sizeof(__map_node<Key, T>)));
		}

	/*
	** --------------------------------------------------------------------------------
	**                                Iterators
	** --------------------------------------------------------------------------------
	*/
		iterator				begin() 			{return (iterator(_tree._begin));}
		const_iterator			begin() const 		{return (const_iterator(_tree._begin));}
		iterator				end() 				{return (iterator(_tree._end));}
		const_iterator			end() const 		{return (const_iterator(_tree._end));}
		reverse_iterator		rbegin() 			{return (reverse_iterator(_tree._end->parent ? _tree._end->parent : _tree._end));}
		const_reverse_iterator	rbegin() const 		{return (const_reverse_iterator(_tree._end->parent ? _tree._end->parent : _tree._end));}
		reverse_iterator		rend() 				{return (reverse_iterator(_tree._end));}
		const_reverse_iterator	rend()const  		{return (const_reverse_iterator(_tree._end));}

	/*
	** --------------------------------------------------------------------------------
	**                               Element access
	** --------------------------------------------------------------------------------
	*/
		mapped_type &			 operator[](const key_type &k)
		{
			_node_pointer curr = _tree.find_place(k, _tree._root);
			if (!curr)
			{
				insert(std::make_pair(k, mapped_type()));
				curr = _tree.find_place(k, _tree._root);
			}
			return (curr->element.second);
		}

	/*
	** --------------------------------------------------------------------------------
	**                                  Modifiers
	** --------------------------------------------------------------------------------
	*/
		// INSERT
		std::pair<iterator,bool> insert (const value_type& val)
		{
			_node_pointer tmp = _tree.find_place(val.first, _tree._root);
			if (tmp == NULL)
			{
				_tree.insert_new_node(val);
				return (std::make_pair(iterator(_tree.find_place(val.first, _tree._root)), true));
			}
			return (std::make_pair(iterator(tmp), false));
		}
		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			_node_pointer tmp = _tree.find_place(val.first, _tree._root);
			if (tmp == NULL)
			{
				_tree.insert_new_node(val);
				return (iterator(_tree.find_place(val.first, _tree._root)));
			}
			return (iterator(tmp));
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		// ERASE
		void erase(iterator position)
		{
			_node_pointer tmp = _tree.find_place((*position).first, _tree._root);
			if (tmp == NULL)
				return;
			_tree.erase(tmp);
			_tree._size--;
		}
		size_type erase(const key_type &k)
		{
			_node_pointer tmp = _tree.find_place(k, _tree._root);
			if (tmp == NULL)
				return 0;
			_tree.erase(tmp);
			_tree._size--;
			return 1;
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		// CLEAR
		void clear()
		{
			iterator it = begin();
			while (it != end())
				erase(it++);
		}

		// SWAP
		void swap (map& x)
		{
			_node_pointer	tmp_root	= _tree._root;
			_node_pointer	tmp_end		= _tree._end;
			_node_pointer	tmp_begin 	= _tree._begin;
			size_type	 	tmp_size	= _tree._size;
			allocator_type	tmp_alloc	= _alloc;
			key_compare		tmp_k_comp	= _comp;
			value_compare	tmp_v_comp	= _value_comp;

			_tree._root  = x._tree._root;
			_tree._end	 = x._tree._end;
			_tree._begin = x._tree._begin;
			_tree._size	 = x._tree._size;
			_alloc		 = x._alloc;
			_comp		 = x._comp;
			_value_comp  = x._value_comp;

			x._tree._root  = tmp_root;
			x._tree._end   = tmp_end;
			x._tree._begin = tmp_begin;
			x._tree._size  = tmp_size;
			x._alloc 	   = tmp_alloc;
			x._comp		   = tmp_k_comp;
			x._value_comp  = tmp_v_comp;
		}

	/*
	** --------------------------------------------------------------------------------
	**                                  Operations
	** --------------------------------------------------------------------------------
	*/
		iterator find(const key_type &k)
		{
			_node_pointer tmp = _tree.find_place(k, _tree._root);
			return (tmp == NULL ? end() : iterator(tmp));
		}

		const_iterator find(const key_type &k) const
		{
			_node_pointer tmp = _tree.find_place(k, _tree._root);
			return (tmp == NULL ? end() : const_iterator(tmp));
		}

		iterator lower_bound(const key_type &k)
		{
			_node_pointer tmp = _tree.find_lower_bound(k);
			return (tmp == NULL ? end() : iterator(tmp));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			_node_pointer tmp = _tree.find_lower_bound(k);
			return (tmp == NULL ? end() : const_iterator(tmp));
		}

		iterator upper_bound(const key_type &k)
		{
			_node_pointer tmp = _tree.find_lower_bound(k);
			if (tmp)
			{
				_node_pointer equal = _tree.find_place(k, _tree._root);
				if (equal)
					return (++(iterator(equal)));
				return (iterator(tmp));
			}
			return (end());
		}

		const_iterator upper_bound(const key_type &k) const
		{
			_node_pointer tmp = _tree.find_lower_bound(k);
			if (tmp)
			{
				_node_pointer equal = _tree.find_place(k, _tree._root);
				if (equal)
					return (++(const_iterator(equal)));
				return (const_iterator(tmp));
			}
			return (end());
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (std::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		std::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (std::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

		size_type count(const key_type &k) const
		{
			_node_pointer tmp = _tree.find_lower_bound(k);
			return (tmp == NULL ? 0 : 1);
		}

	/*
	** --------------------------------------------------------------------------------
	**                                  Observers
	** --------------------------------------------------------------------------------
	*/
		key_compare key_comp() const
		{
			return (_comp);
		}

		value_compare value_comp() const
		{
			return _value_comp;
		}
	};
}