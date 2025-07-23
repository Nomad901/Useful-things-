#include <iostream>
#include <memory>
#include <format> //c++20 

/*
	The differences between .size() / std::size() / std::ssize():
	.size() is a feature, which returns size_t type;
	std::size() the same thing like .size(), but more modern and works with a lotta types(vector,array etc.);
	std::ssize() the same thing like std::size(), but instead of unsigned int32_t is;
	returning signed int32_t, which is really convenient for arithmetic operations;

	//
	// for me personally - using std::ssize is the better approach;
	//
*/


int main()
{
	std::vector<int32_t> tmpVctr = { 1,2,3,4,5 };

	std::cout << std::format(".size(): {}\n", tmpVctr.size());
	std::cout << std::format("std::size(): {}\n", std::size(tmpVctr)); // c++ 17
	std::cout << std::format("std::SSize(): {}\n", std::ssize(tmpVctr)); // c++ 20

	// use cases of std::ssize() (which is, btw, a much more better, than the usual one) 
	//for (int32_t i = 0; i < tmpVctr.size() - 10; ++i)
	//{
	//	std::cout << std::format("Index: {}\n", i);
	//} // garbage value in a deduce!;
	//
	// but instead - we can use this
	//
	for (int32_t i = 0; i < std::ssize(tmpVctr) - 10; ++i)
	{
	} // doesnt  work, cuz there is no point in this, but at least this doesnt create 1000+ values;
}
