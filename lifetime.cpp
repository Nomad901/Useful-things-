#include <iostream>
#include <source_location>

struct Lifetime
{
	Lifetime()
	{
		std::cout << source.function_name() << '\n';
	}
	Lifetime(int pI) : i(pI)
	{
		std::cout << source.function_name() << '\n';
	}
	~Lifetime()
	{
		std::cout << "Destructor" << '\n';
	}
	Lifetime(const Lifetime&)
	{
		std::cout << source.function_name() << '\n';
	}
	Lifetime operator=(const Lifetime&)
	{
		std::cout << source.function_name() << '\n';
		return *this;
	}
	Lifetime(Lifetime&&) noexcept
	{
		std::cout << source.function_name() << '\n';
	}
	Lifetime operator=(Lifetime&&) noexcept
	{
		std::cout << source.function_name() << '\n';
		return *this;
	}

	std::source_location source = std::source_location::current();
	int32_t i{};
};

int main()
{


}
