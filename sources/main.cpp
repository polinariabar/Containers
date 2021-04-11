#include "test_list.cpp"
#include "test_vector.cpp"
#include "test_stack.cpp"
#include "test_queue.cpp"
#include "test_map.cpp"
#include <ctime>
#include "../includes/map.hpp"
#include "../includes/tests/Tests.hpp"
#include <map>

void random_string(std::string & str)
{
	int size = rand() % 20;
	for (int j = 0; j < size; j++)
		str += rand() % 65 + 60;
}

int main()
{	
	srand(time(NULL));
	int			int_keys[30];
	char		char_vals[30];
	char		char_keys[30];
	std::string str_vals[30];
	for (int i = 0; i < 30; i++)
	{
		int_keys[i] = rand() % 100;
		char_vals[i] = rand() % 70 + 40;
		char_keys[i] = rand() % 48 + 70;
	}
	for (int i = 0; i < 30; i++)
		random_string(str_vals[i]);

	map_test<int, char>(int_keys, char_vals);
	map_test<char, int>(char_vals, int_keys);
	map_test<char, char>(char_keys, char_vals);
	map_test<int, std::string>(int_keys, str_vals);
	map_test<std::string, char>(str_vals, char_vals);

	list_test<char>('@', 'o', '*');
	list_test<std::string>(str_vals[0], str_vals[1], str_vals[3]);
	list_test<double>(-0.89, 1.333, 99.99);
	list_test<int>(12, 0, 99);

	vector_test<int>(12, 0, 99);
	vector_test<char>('@', 'o', '*');
	vector_test<std::string>("wow", "*****", "peppa");
	vector_test<double>(-0.89, 1.333, 99.99);

	stack_test<char>('@', 'o', '*');
	stack_test<std::string>("wow", "*****", "pipa");
	stack_test<double>(-0.89, 1.333, 99.99);
	stack_test<int>(12, 0, 99);

	queue_test<char>('@', 'o', '*');
	queue_test<std::string>("wow", "*****", "kjnkjnk");
	queue_test<double>(-0.89, 1.333, 99.99);
	queue_test<int>(12, 0, 99);

	// while (1) ;
}