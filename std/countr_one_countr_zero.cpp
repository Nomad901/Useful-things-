#include <iostream>
#include <string>
#include <format>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <array>
#include <numeric>
#include <bit>
#include <bitset>

int32_t main()
{
	uint32_t numbers[] = { 43, 51, 54 ,76, 123, 543, 76, 4 };
	/*
		43  = 00101011
		51  = 00110011
		54  = 00110110
		76  = 01001100
		123 = 01111011
		543 = 00011111
		76  = 01001100
		4   = 00000100
	*/
	// ---------------countr_one--------------------
	// 43 = 00101011 -> ______11 <- there are two ones, then it will give 2 
	std::countr_one(numbers[0]); // result: 2
	// 54 = 00110110 -> _______0 <- there is no one at the beginning, 
	// then it means there is no leading from the right one. result = 0;
	std::countr_one(numbers[2]); // result: 0
	// ---------------------------------------------

	// ---------------countr_zero--------------------
	// 76 = 01001100 -> ______00 <- there are two zeros, then it will give us 2;
	std::countr_zero(numbers[3]); // result 2;
	// 123 = 01111011 -> ________ <- there is no zeros at the beginning. the same system
	// like with ones. result = 0;
	std::countr_zero(numbers[4]);
	// ----------------------------------------------

	// ---------------countl_one + countl_zero--------------------
	// will be absolutely the same logic like countr_one and countr_zero, but it
	// will be counting from the LEFT side, instead of the right one;
	// -----------------------------------------------------------
}
