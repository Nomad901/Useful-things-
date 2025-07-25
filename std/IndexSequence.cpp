#include <iostream>
#include <utility>

template<std::size_t... I>
void printIndexSequence(std::index_sequence<I...>)
{
	((std::cout << I << ','), ...);
	std::cout << '\n';
}

int main()
{
	std::index_sequence is = std::make_index_sequence<5>();
	printIndexSequence(is);

	std::index_sequence<1, 2, 3, 4, 5> is2;
	printIndexSequence(is2);

}
