#pragma once

#include <iostream>

namespace ft
{
	template <typename T, typename Key>
	class MapIterator
	{
	public:
		typedef T						value_type;
		typedef const std::pair<const Key, T> pair_type;
		typedef pair_type *pointer;
		typedef pair_type &reference;
		typedef __map_node<Key, T>		node_type;
		typedef node_type *				node_pointer;
		node_pointer					_node;

	public:
		MapIterator() 					: _node(nullptr) {}
		MapIterator(node_pointer p) 	: _node(p) {}

		MapIterator &	operator=(const MapIterator &src)	{ _node = src._node; return (*this); }
		reference &		operator*() const					{ return (_node->element); }
		MapIterator &	operator++()						
															{
																if (_node->right)				// если у узла есть правый ребенок(большее значение)
																{
																	_node = _node->right;		// переходим в него
																	while (_node->left)			// пока у него есть левый ребенок
																		_node = _node->left;	// идем вниз влево (в меньшую сторону)
																}
																else							// если у узла нет правого ребенка, мы должны шагать наверх
																{
																	node_pointer curr = _node;	// запоминаем текущий
																	_node = _node->parent;		// переходим в родителя
																	while (_node->left != curr)	// пока не найдем следующий элемент, явщяющийся левым потомком
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (*this);
															}
		MapIterator &	operator--()						
															{
																if (_node->left)				// если есть меньший элемент (левый потомок)
																{
																	_node = _node->left;		// переходим в него
																	while (_node->right)		// пока есть правый потомок (больший элемент)
																		_node = _node->right;	// переходим в него
																}
																else
																	_node = _node->parent;		// иначе переходим в родителя
																return (*this);
															}
		MapIterator		operator++(int)		
															{
																MapIterator ret = *this;
																if (_node->right)
																{
																	_node = _node->right;
																	while (_node->left)
																		_node = _node->left;
																}
																else
																{
																	node_pointer curr = _node;
																	_node = _node->parent;
																	while (_node->left != curr)
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (ret);
															}
		MapIterator		operator--(int)
															{
																MapIterator curr = *this;
																if (_node->left)
																{
																	_node = _node->left;
																	while (_node->right)
																		_node = _node->right;
																}
																else
																	_node = _node->parent;
																return (curr);
															}
		bool			operator==(const MapIterator & second) const
															{ return (_node == second._node); }
		bool			operator!=(const MapIterator & second) const
															{ return (_node != second._node); }
	};

	template <typename T, typename Key>
	class ConstMapIterator
	{
	public:
		typedef const T					value_type;
		typedef const std::pair<const Key, T> pair_type;
		typedef pair_type *pointer;
		typedef pair_type &reference;
		typedef const __map_node<Key, T>		node_type;
		typedef node_type *				node_pointer;
		node_pointer					_node;

	public:
		ConstMapIterator() 							: _node(nullptr) {}
		ConstMapIterator(node_pointer p) 			: _node(p) {}
		ConstMapIterator(const MapIterator<T, Key> & src) 	: _node(src._node) {}

		ConstMapIterator &	operator=(const ConstMapIterator &src)	{ _node = src._node; return (*this); }
		ConstMapIterator &	operator=(const MapIterator<T, Key> &src)	{ _node = src._node; return (*this); }
		reference &			operator*() const					{ return (_node->element); }
		ConstMapIterator &	operator++()						
															{
																if (_node->right)				// если у узла есть правый ребенок(большее значение)
																{
																	_node = _node->right;		// переходим в него
																	while (_node->left)			// пока у него есть левый ребенок
																		_node = _node->left;	// идем вниз влево (в меньшую сторону)
																}
																else							// если у узла нет правого ребенка, мы должны шагать наверх
																{
																	node_pointer curr = _node;	// запоминаем текущий
																	_node = _node->parent;		// переходим в родителя
																	while (_node->left != curr)	// пока не найдем следующий элемент, явщяющийся левым потомком
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (*this);
															}
		ConstMapIterator &	operator--()						
															{
																if (_node->left)				// если есть меньший элемент (левый потомок)
																{
																	_node = _node->left;		// переходим в него
																	while (_node->right)		// пока есть правый потомок (больший элемент)
																		_node = _node->right;	// переходим в него
																}
																else
																	_node = _node->parent;		// иначе переходим в родителя
																return (*this);
															}
		ConstMapIterator		operator++(int)		
															{
																ConstMapIterator ret = *this;
																if (_node->right)
																{
																	_node = _node->right;
																	while (_node->left)
																		_node = _node->left;
																}
																else
																{
																	node_pointer curr = _node;
																	_node = _node->parent;
																	while (_node->left != curr)
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (ret);
															}
		ConstMapIterator		operator--(int)
															{
																ConstMapIterator curr = *this;
																if (_node->left)
																{
																	_node = _node->left;
																	while (_node->right)
																		_node = _node->right;
																}
																else
																	_node = _node->parent;
																return (curr);
															}
		bool			operator==(const ConstMapIterator & second) const
															{ return (_node == second._node); }
		bool			operator!=(const ConstMapIterator & second) const
															{ return (_node != second._node); }
	};

	template <typename T, typename Key>
	class RevMapIterator
	{
	public:
		typedef T						value_type;
		typedef std::pair<const Key, T> pair_type;
		typedef pair_type *pointer;
		typedef pair_type &reference;
		typedef __map_node<Key, T>		node_type;
		typedef node_type *				node_pointer;
		node_pointer					_node;

	public:
		RevMapIterator() 					: _node(nullptr) {}
		RevMapIterator(node_pointer p) 		: _node(p) {}

		RevMapIterator &	operator=(const RevMapIterator &src)	{ _node = src._node; return (*this); }
		reference &			operator*() const						{ return (_node->element); }
		RevMapIterator &	operator--()						
															{
																if (_node->right)				// если у узла есть правый ребенок(большее значение)
																{
																	_node = _node->right;		// переходим в него
																	while (_node->left)			// пока у него есть левый ребенок
																		_node = _node->left;	// идем вниз влево (в меньшую сторону)
																}
																else							// если у узла нет правого ребенка, мы должны шагать наверх
																{
																	node_pointer curr = _node;	// запоминаем текущий
																	_node = _node->parent;		// переходим в родителя
																	while (_node->left != curr)	// пока не найдем следующий элемент, явщяющийся левым потомком
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (*this);
															}
		RevMapIterator &	operator++()						
															{
																if(_node->left)
																{
																	_node = _node->left;
																	while (_node->right)
																		_node = _node->right;
																}
																else
																{
																	node_pointer tmp = _node;
																	_node = _node->parent;
																	while (_node->right != tmp)
																	{
																		tmp = _node;
																		_node = _node->parent;
																	}
																}
																return (*this);
															}
		RevMapIterator		operator--(int)		
															{
																RevMapIterator ret = *this;
																if (_node->right)
																{
																	_node = _node->right;
																	while (_node->left)
																		_node = _node->left;
																}
																else
																{
																	node_pointer curr = _node;
																	_node = _node->parent;
																	while (_node->left != curr)
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (ret);
															}
		RevMapIterator		operator++(int)
															{
																RevMapIterator curr = *this;
																if (_node->left)
																{
																	_node = _node->left;
																	while (_node->right)
																		_node = _node->right;
																}
																else
																{
																	node_pointer tmp = _node;
																	_node = _node->parent;
																	while (_node->right != tmp)
																	{
																		tmp = _node;
																		_node = _node->parent;
																	}
																}
																return (curr);
															}
		bool			operator==(const RevMapIterator & second) const
															{ return (_node == second._node); }
		bool			operator!=(const RevMapIterator & second) const
															{ return (_node != second._node); }
	};

	template <typename T, typename Key>
	class ConstRevMapIterator
	{
	public:
		typedef const T									value_type;
		typedef const std::pair<const Key, T> pair_type;
		typedef pair_type *pointer;
		typedef pair_type &reference;
		typedef const __map_node<Key, T>				node_type;
		typedef node_type *								node_pointer;
		node_pointer									_node;

	public:
		ConstRevMapIterator() 					: _node(nullptr) {}
		ConstRevMapIterator(node_pointer p) 		: _node(p) {}
		ConstRevMapIterator(const RevMapIterator<T, Key> & src) 	: _node(src._node) {}

		ConstRevMapIterator &	operator=(const ConstRevMapIterator &src)		{ _node = src._node; return (*this); }
		ConstRevMapIterator &	operator=(const RevMapIterator<T, Key> &src)	{ _node = src._node; return (*this); }
		reference &				operator*() const								{ return (_node->element); }
		ConstRevMapIterator &	operator--()						
															{
																if (_node->right)				// если у узла есть правый ребенок(большее значение)
																{
																	_node = _node->right;		// переходим в него
																	while (_node->left)			// пока у него есть левый ребенок
																		_node = _node->left;	// идем вниз влево (в меньшую сторону)
																}
																else							// если у узла нет правого ребенка, мы должны шагать наверх
																{
																	node_pointer curr = _node;	// запоминаем текущий
																	_node = _node->parent;		// переходим в родителя
																	while (_node->left != curr)	// пока не найдем следующий элемент, явщяющийся левым потомком
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (*this);
															}
		ConstRevMapIterator &	operator++()						
															{
																if (_node->left)
																{
																	_node = _node->left;
																	while (_node->right)
																		_node = _node->right;
																}
																else
																{
																	node_pointer tmp = _node;
																	_node = _node->parent;
																	while (_node->right != tmp)
																	{
																		tmp = _node;
																		_node = _node->parent;
																	}
																}
																return (*this);
															}
		ConstRevMapIterator		operator--(int)		
															{
																ConstRevMapIterator ret = *this;
																if (_node->right)
																{
																	_node = _node->right;
																	while (_node->left)
																		_node = _node->left;
																}
																else
																{
																	node_pointer curr = _node;
																	_node = _node->parent;
																	while (_node->left != curr)
																	{
																		curr = _node;
																		_node = _node->parent;
																	}
																}
																return (ret);
															}
		ConstRevMapIterator		operator++(int)
															{
																ConstRevMapIterator curr = *this;
																if (_node->left)
																{
																	_node = _node->left;
																	while (_node->right)
																		_node = _node->right;
																}
																else
																{
																	node_pointer tmp = _node;
																	_node = _node->parent;
																	while (_node->right != tmp)
																	{
																		tmp = _node;
																		_node = _node->parent;
																	}
																}
																return (curr);
															}
		bool			operator==(const ConstRevMapIterator & second) const
															{ return (_node == second._node); }
		bool			operator!=(const ConstRevMapIterator & second) const
															{ return (_node != second._node); }
	};
}