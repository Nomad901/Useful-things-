#include <iostream>
#include <format>
#include <concepts>
#include <type_traits>

class A{};

class B : public A
{ };

class C : private A
{
};

int main()
{
	/*
	* Derived from:
	* parameters: first is derived, second is the base
	* works the same like std::is_base_of, but returns false, if 
	* the derived class was derived in a private essence;
	*/

	std::cout << std::format("B derived from A (std::derived_from): {}\n", std::derived_from<B, A>); // true
	std::cout << std::format("C derived from A (std::derived_from): {}\n", std::derived_from<C, A>); // false (private inheritance)
	
	std::cout << std::format("B derived from A (std::is_base_of_v): {}\n", std::is_base_of_v<A, B>); // true 
	std::cout << std::format("C derived from A (std::is_base_of_v): {}\n", std::is_base_of_v<A, C>); // true 
}
