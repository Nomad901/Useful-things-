#include <iostream>
#include <utility>
#include <tuple>

template <typename Tuple, std::size_t... Is>
void printTupleElementsImpl(const Tuple& t, std::index_sequence<Is...>) {
	((std::cout << std::get<Is>(t) << " "), ...); 
	std::cout << std::endl;
}

template <typename Tuple>
void printTupleElements(const Tuple& t) {
	printTupleElementsImpl(t, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

int main()
{
	std::tuple<int, double, char> my_tuple(10, 3.14, 'A');
	printTupleElements(my_tuple); // output: 10 3.14 A 
	
	std::cout << std::format("\nNumber: {}\n", std::tuple_size_v<decltype(my_tuple)>); // size of a tuple
}
