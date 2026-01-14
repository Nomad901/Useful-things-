#include <iostream>
#include <string>
#include <format>

int32_t main()
{
	std::string someString = "heeey everyone!!!\n";
	int32_t key = 1;
	std::string encoded_string; 
	std::string decoded_string;

	for (size_t i = 0; i < someString.size(); ++i)
	{
		encoded_string += someString[i] + key;
	}
	std::cout << std::format("encoded string: {}\n", encoded_string);
	for (size_t i = 0; i < encoded_string.size(); ++i)
	{
		decoded_string += encoded_string[i] - key;
	}
	std::cout << std::format("decoded string: {}\n", decoded_string);
}
