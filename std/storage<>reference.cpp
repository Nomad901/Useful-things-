#include <iostream>
#include <vector>
#include <format>

int main()
{
	std::vector<int32_t> storage = { 10,20,30 };
	std::cout << std::format("Element: {}\n", storage[0]); // Element: 10

	std::vector<int32_t>::reference firstEl = storage[0];
	firstEl = 50;
	std::cout << std::format("Element: {}\n", storage[0]); // Element : 50

	int32_t& firstElInt = storage[0];
	firstElInt = 100;
	std::cout << std::format("Element: {}\n", storage[0]); // Element : 100
}
