#pragma once

#include "node.hpp"
#include "map_iterator.hpp"
#include <limits>
#include <memory>
#include <iostream>

namespace ft
{
	template <typename Key,												  // map::key_type
			  typename T,												  // map::mapped_type
			  typename Compare = std::less<Key>,						  // map::key_compare
			  typename Alloc = std::allocator<std::pair<const Key, T> > > // map::allocator_type>
	class Tree
	{
	public:
		typedef Key										key_type;
		typedef T										value_type;
		typedef std::pair<const key_type, value_type>	pair_type;
		typedef Alloc									allocator_type;
		typedef Compare									key_compare;
		typedef size_t									size_type;
		typedef __map_node<Key, T>						_node;
		typedef _node *									_node_pointer;
		typedef MapIterator<T, Key>						iterator;

		_node_pointer									_root;
		size_type										_size;
		_node_pointer									_end;
		_node_pointer									_begin;
		key_compare										comp;

	public:
		Tree()
		{
			_size = 0;
			_begin = new _node();
			_end = _begin;
			_end->is_empty = true;
			_root = _end;
			_begin->left = _end;
		}

		void set_first()
		{
			_node_pointer tmp = _root;

			while (tmp->left)
				tmp = tmp->left;
			_begin = tmp;
			_begin->left = _end;
		}

		void set_last()
		{
			_node_pointer tmp = _root;

			while (tmp->right)
				tmp = tmp->right;
			tmp->right = _end;
			_end->parent = tmp;
		}

		void insert_new_node(std::pair<const Key, T> new_pair)
		{
			_node_pointer new_node = new _node(new_pair);

			if (_end->parent)
				_end->parent->right = NULL;
			_begin->left = NULL;
			if (_root == _end)
				_root = new_node;
			else
			{
				_node_pointer tmp = _root;
				while (tmp)
				{
					if (comp(new_node->element.first, tmp->element.first)) 	// if value < root
					{
						if (tmp->left != NULL) 								// if there is a left (less) child
							tmp = tmp->left;
						else
						{
							tmp->left = new_node;
							break;
						}
					}
					else
					{
						if (tmp->right != NULL)
							tmp = tmp->right;
						else
						{
							tmp->right = new_node;
							break;
						}
					}
				}
				new_node->parent = tmp;
			}
			_size++;
			set_first();
			set_last();
		}
		
		bool equal(const key_type &val1, const key_type & val2)
		{
			if (!comp(val1, val2) && !comp(val2, val1))
				return true;
			return false;
		}

		_node_pointer find_place(const Key &value, _node_pointer curr)
		{
			if (!curr || curr == _end)
				return (NULL);
			if (equal(value, curr->element.first)) 						// if =
				return curr;
			if (comp(value, curr->element.first))						// if value < curr
				return (find_place(value, curr->left));
			return (find_place(value, curr->right));					// if value > curr
		}

		_node_pointer find_lower_bound(const Key & value)
		{
			_node_pointer tmp = _begin;

			while (tmp != _end)
			{
				if (equal(value, tmp->element.first))
					return tmp;
				if (comp(value, tmp->element.first))
					return tmp;
				tmp = next(tmp);
			}
			return (NULL);
		}

		void replace_node(_node_pointer curr, _node_pointer child)
		{
			child->parent = curr->parent;
			if (curr == curr->parent->left)
				curr->parent->left = child;
			else
				curr->parent->right = child;
		}

		int have_child(_node_pointer & curr)
		{
			if (curr->left && curr->right)
				return 2;
			if (curr->left || curr->right)
				return 1;
			return 0;
		}

		_node_pointer next(_node_pointer _node)
		{
			if (_node->right) // если у узла есть правый ребенок(большее значение)
			{
				_node = _node->right;	 // переходим в него
				while (_node->left)		 // пока у него есть левый ребенок
					_node = _node->left; // идем вниз влево (в меньшую сторону)
			}
			else // если у узла нет правого ребенка, мы должны шагать наверх
			{
				_node_pointer curr = _node;	// запоминаем текущий
				_node = _node->parent;		// переходим в родителя
				while (_node->left != curr) // пока не найдем следующий элемент, явщяющийся левым потомком
				{
					curr = _node;
					_node = _node->parent;
				}
			}
			return _node;
		}

		void erase(_node_pointer node)
		{
			if (_end->parent)
				_end->parent->right = nullptr;
			_begin->left = NULL;
			delete_node(node);
			set_first();
			set_last();
		}

		void delete_none_child(_node_pointer curr)
		{
			if (curr == _root)
			{
				_root = _end;
				_begin = _end;
			}
			else
				curr->parent->left == curr ? curr->parent->left = NULL : curr->parent->right = NULL;
		}

		void delete_one_child(_node_pointer curr)
		{
			if (curr->left)
			{
				if (curr == _root)
				{
					curr->left->parent = NULL;
					_root = curr->left;
				}
				else if (curr->parent)
					curr->parent->left == curr ? curr->parent->left = curr->left : curr->parent->right = curr->left;
				curr->left->parent = curr->parent;
				if (curr->left->color == RED_NODE)
					curr->left->color = BLACK_NODE;
			}
			else
			{
				if (curr == _root)
				{
					curr->right->parent = NULL;
					_root = curr->right;
				}
				else if (curr->parent)
					curr->parent->left == curr ? curr->parent->left = curr->right : curr->parent->right = curr->right;
				curr->right->parent = curr->parent;
				if (curr->right->color == RED_NODE)
					curr->right->color = BLACK_NODE;
			}
		}

		void delete_two_children(_node_pointer curr)
		{
			_node_pointer tmp = next(curr);
			if (have_child(tmp) == 1)
				delete_one_child(tmp);
			else
				delete_none_child(tmp);
			tmp->color = curr->color;
			tmp->parent = curr->parent;
			tmp->left = curr->left;
			tmp->right = curr->right;
			if (curr != _root)
				curr->parent->right == curr ? curr->parent->right = tmp : curr->parent->left = tmp;
			else
				_root = tmp;
			if (curr->left != tmp && curr->left)
				curr->left->parent = tmp;
			if (curr->right != tmp && curr->right)
				curr->right->parent = tmp;
		}

		void delete_node(_node_pointer curr)
		{
			if (have_child(curr) == 0)
			{
				delete_none_child(curr);
				delete curr;
			}
			else if (have_child(curr) == 1)
			{
				delete_one_child(curr);
				delete curr;
			}
			else
			{
				delete_two_children(curr);
				delete curr;
			}
		}
	};
}