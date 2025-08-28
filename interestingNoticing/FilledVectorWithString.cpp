#include <iostream>
#include <format> 
#include <vector> 
#include <string>

int main()
{
	std::string smth = "qewq"; 
	std::vector<uint32_t> vctr(smth.begin(), smth.end());
	std::cout << std::format("Your vctr: {}\n\n", vctr);
	/*
		Your vctr: 113
		Your vctr: 101
		Your vctr: 119
		Your vctr: 113
	*/
	
	std::vector<char> objects{ 113,101,119,113 };
	std::cout << std::format("Your objects: {}\n", objects);
}
