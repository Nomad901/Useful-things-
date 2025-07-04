#include <iostream>
#include <chrono>

class benchmark
{
public:
	benchmark()
	{
		point1 = std::chrono::high_resolution_clock::now();
	}
	int getResult()
	{
		point2 = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(point2 - point1).count();
	}
	~benchmark()
	{
		point2 = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(point2 - point1).count() << '\n';
	}
	std::chrono::steady_clock::time_point point1;
	std::chrono::steady_clock::time_point point2;
};


int main()
{


}
