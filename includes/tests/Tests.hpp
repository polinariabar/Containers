#pragma once

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../list.hpp"
#include "../vector.hpp"
#include "../stack.hpp"
#include "../queue.hpp"
#include "../map.hpp"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

#define CORRECT true
#define ERROR	false

template <typename T>
class Test
{
protected:
	bool _result;

public:
	Test() : _result(CORRECT) {}

	static void print_result(bool res)
	{
		if (res == CORRECT)
			std::cout << GREEN << "TEST CORRECT\n"
					  << RESET;
		else
			std::cout << RED << "TEST FAIL\n"
					  << RESET;
		//_result = CORRECT;
	}

	void print_result()
	{
		if (_result == CORRECT)
			std::cout << GREEN << "TEST CORRECT\n"
					  << RESET;
		else
			std::cout << RED << "TEST FAIL\n"
					  << RESET;
		//_result = CORRECT;
	}
	void print_error(bool result)
	{
		if (result == ERROR)
		{
			std::cout << RED << "ERROR\n"
					  << RESET;
			_result = ERROR;
		}
	}

	static void print_test(int i, const std::string &name)
	{
		std::cout << CYAN
				  << "\n-----------------------------------------------\n"
				  << " [TEST " << i << "]  " << name
				  << "\n-----------------------------------------------\n"
				  << RESET;
	}

	bool get_result() const {return (_result);}
};