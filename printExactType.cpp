#include <iostream>
#include <type_traits>

template<typename T>
static constexpr void printExactType()
{
	if constexpr (std::is_const_v<std::remove_reference_t<T>>)
		std::cout << "const ";

	std::cout << typeid(T).name();

	if constexpr (std::is_lvalue_reference_v<T>)
		std::cout << "&";
	else if constexpr (std::is_rvalue_reference_v<T>)
		std::cout << "&&";
	else if constexpr (std::is_pointer_v<T>)
		std::cout << "*";

	std::cout << '\n';
}


template<typename T>
void foo(T pType)
{
	printExactType<decltype(pType)>();
}

template<typename T>
void foo1(T& pType)
{
	printExactType<decltype(pType)>();
}

template<typename T>
void foo2(const T& pType)
{
	printExactType<decltype(pType)>();
}

template<typename T>
void foo3(T&& pType)
{
	printExactType<decltype(pType)>();
}


int main()
{
	int i = 3;
	const int i2 = 4;
	const int& i3 = 5;

	foo(i);
	foo1(i);
	foo2(i);
	foo3(i);
	std::cout << '\n';
	foo(i2);
	foo1(i2);
	foo2(i2);
	foo3(i2);
	std::cout << '\n';
	foo(i3);
	foo1(i3);
	foo2(i3);
	foo3(i3);
	std::cout << '\n';
	foo(1);
	//foo1(2);
	foo2(3);
	foo3(4);

}