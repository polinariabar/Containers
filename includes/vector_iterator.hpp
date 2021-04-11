#pragma once

#include "vector.hpp"
#include <iostream>
class vector;

namespace ft
{
	template <typename _T>
	class VectorIterator
	{
	public:
		typedef _T						value_type;
		typedef _T&						reference;
		typedef _T*						pointer;
		pointer							node;

	public:
		VectorIterator() : node(nullptr) {}
		VectorIterator(pointer p) : node(p) {}
		
		VectorIterator &operator=(const VectorIterator &src){ node = src.node; return (*this); }
		reference		operator*()							{ return (*node); }
		pointer			operator->()						{ return (node); }
		reference		operator[](size_t n)				{ return (*(node + n)); }		
		VectorIterator &operator++()						{ node++; return (*this); }
		VectorIterator &operator--()						{ node--; return (*this); }
		VectorIterator	operator++(int)		
															{ 
																VectorIterator curr = *this;
																node++;
																return (curr);
															}
		VectorIterator	operator--(int)
															{
																VectorIterator curr = *this;
																node--;
																return (curr);
															}
		VectorIterator&	operator+=(int n)					{ node += n; return (*this); }
		VectorIterator&	operator-=(int n)					{ node -= n; return (*this); }
		VectorIterator	operator+(int n) const				{
																VectorIterator tmp = *this;
																tmp.node += n;
																return tmp;
															}
		VectorIterator	operator-(int n) const				{
																VectorIterator tmp = *this;
																tmp.node -= n;
																return tmp;
															}
		size_t			operator-(VectorIterator & other) const		
															{ return (node - other.node); }
		bool			operator==(const VectorIterator & second) const
															{ return (node == second.node); }
		bool			operator!=(const VectorIterator & second) const
															{ return (node != second.node); }
															
	};

	template <typename _T>
	class ConstVectorIterator
	{
	public:
		typedef const _T				value_type;
		typedef const _T&				reference;
		typedef const _T*				pointer;
		pointer							node;

	public:
		ConstVectorIterator() 								: node(nullptr) {}
		ConstVectorIterator(pointer p) 						: node(p) {}
		ConstVectorIterator(const VectorIterator<_T> &src) 	: node(src.node) {}

		ConstVectorIterator & operator=(const VectorIterator<_T> &src)
															{ node = src.node; return (*this); }
		ConstVectorIterator &operator=(const ConstVectorIterator &src)
															{ node = src.node; return (*this); }
		reference		operator*()							{ return (*node); }
		pointer			operator->()						{ return (node); }
		reference		operator[](size_t n)				{ return (*(node + n)); }		
		ConstVectorIterator &operator++()					{ node++; return (*this); }
		ConstVectorIterator &operator--()					{ node--; return (*this); }
		ConstVectorIterator	operator++(int)		
															{ 
																ConstVectorIterator curr = *this;
																node++;
																return (curr);
															}
		ConstVectorIterator	operator--(int)
															{
																ConstVectorIterator curr = *this;
																node--;
																return (curr);
															}
		ConstVectorIterator&	operator+=(int n)			{ node += n; return (*this); }
		ConstVectorIterator&	operator-=(int n)			{ node -= n; return (*this); }
		ConstVectorIterator	operator+(int n) const			{
																ConstVectorIterator tmp = *this;
																tmp.node += n;
																return tmp;
															}
		ConstVectorIterator	operator-(int n) const			{
																ConstVectorIterator tmp = *this;
																tmp.node -= n;
																return tmp;
															}
		size_t			operator-(ConstVectorIterator & other) const
															{ return (node - other.node); }
		bool			operator==(const ConstVectorIterator & second) const
															{ return (node == second.node); }
		bool			operator!=(const ConstVectorIterator & second) const
															{ return (node != second.node); }
															
	};

	template <typename _T>
	class RevVectorIterator
	{
	public:
		typedef _T						value_type;
		typedef _T&						reference;
		typedef _T*						pointer;
		pointer							node;

	public:
		RevVectorIterator() 			: node(nullptr) {}
		RevVectorIterator(pointer p) 	: node(p) {}
		
		RevVectorIterator &	operator=(const RevVectorIterator &src)
																{ node = src.node; return (*this); }
		reference			operator*()							{ return (*node); }
		pointer				operator->()						{ return (node); }
		reference			operator[](size_t n)				{ return (*(node - n)); }		
		RevVectorIterator &	operator++()						{ node--; return (*this); }
		RevVectorIterator &	operator--()						{ node++; return (*this); }
		RevVectorIterator	operator++(int)		
																{ 
																	RevVectorIterator curr = *this;
																	node--;
																	return (curr);
																}
		RevVectorIterator	operator--(int)
																{
																	RevVectorIterator curr = *this;
																	node++;
																	return (curr);
																}
		RevVectorIterator&	operator+=(int n)					{ node -= n; return (*this); }
		RevVectorIterator&	operator-=(int n)					{ node += n; return (*this); }
		RevVectorIterator	operator+(int n) const				{
																	RevVectorIterator tmp = *this;
																	tmp.node -= n;
																	return tmp;
																}
		RevVectorIterator	operator-(int n) const				{
																	RevVectorIterator tmp = *this;
																	tmp.node += n;
																	return tmp;
																}
		size_t				operator-(RevVectorIterator & other) const		
																{ return (node - other.node); }
		bool				operator==(const RevVectorIterator & second) const
																{ return (node == second.node); }
		bool				operator!=(const RevVectorIterator & second) const
																{ return (node != second.node); }
															
	};

	template <typename _T>
	class ConstRevVectorIterator
	{
	public:
		typedef const _T				value_type;
		typedef const _T&				reference;
		typedef const _T*				pointer;
		pointer							node;

	public:
		ConstRevVectorIterator() : node(nullptr) {}
		ConstRevVectorIterator(pointer p) : node(p) {}
		ConstRevVectorIterator(const RevVectorIterator<_T> &src) 	: node(src.node) {}

		ConstRevVectorIterator & operator=(const RevVectorIterator<_T> &src)
																{ node = src.node; return (*this); }
		ConstRevVectorIterator & operator=(const ConstRevVectorIterator &src)
																{ node = src.node; return (*this); }
		reference			operator*()							{ return (*node); }
		pointer				operator->()						{ return (node); }
		reference			operator[](size_t n)				{ return (*(node - n)); }		
		ConstRevVectorIterator	&operator++()						{ node--; return (*this); }
		ConstRevVectorIterator &operator--()						{ node++; return (*this); }
		ConstRevVectorIterator	operator++(int)		
																{ 
																	ConstRevVectorIterator curr = *this;
																	node--;
																	return (curr);
																}
		ConstRevVectorIterator	operator--(int)
																{
																	ConstRevVectorIterator curr = *this;
																	node++;
																	return (curr);
																}
		ConstRevVectorIterator	&operator+=(int n)					{ node -= n; return (*this); }
		ConstRevVectorIterator	&operator-=(int n)					{ node += n; return (*this); }
		ConstRevVectorIterator	operator+(int n) const				{
																	ConstRevVectorIterator tmp = *this;
																	tmp.node -= n;
																	return tmp;
																}
		ConstRevVectorIterator	operator-(int n) const				{
																	ConstRevVectorIterator tmp = *this;
																	tmp.node += n;
																	return tmp;
																}
		size_t				operator-(ConstRevVectorIterator & other) const		
																{ return (node - other.node); }
		bool				operator==(const ConstRevVectorIterator & second) const
																{ return (node == second.node); }
		bool				operator!=(const ConstRevVectorIterator & second) const
																{ return (node != second.node); }
															
	};
}