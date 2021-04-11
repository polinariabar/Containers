#pragma once

#define RED_NODE true
#define BLACK_NODE false

template <typename _T>
struct __list_node
{
	struct __list_node *prev;
	struct __list_node *next;

	_T					element;

	__list_node() : element(_T()) {}
	__list_node(const _T &value) : element(value) {}
};

template <typename _T>
struct __stack_node
{
	struct __stack_node *next;

	_T					element;

	__stack_node() : element(_T()) {}
	__stack_node(const _T &value) : element(value) {}
};

template <typename Key, typename T>
struct __map_node
{
	struct __map_node *parent;
	struct __map_node *left;
	struct __map_node *right;
	std::pair<const Key, T> element;
	bool is_empty;
	bool color;

	__map_node(std::pair<const Key, T> pair) : parent(NULL),
											   left(NULL),
											   right(NULL),
											   element(pair),
											   is_empty(false),
											   color(RED_NODE) {}
	__map_node() : parent(NULL),
				   left(NULL),
				   right(NULL),
				   is_empty(false),
				   color(BLACK_NODE) {}
};