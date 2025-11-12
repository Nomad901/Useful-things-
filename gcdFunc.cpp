void getPrimeFactorizationNumbers(std::vector<uint32_t>& pValues, int32_t pFirstValue, int32_t pSecondValue)
{
	auto getFactorizationNumbers = [](std::vector<uint32_t>& pValues, int32_t pValue)
		{
			uint32_t divider = 2;
			while (pValue > 1)
			{
				if (pValue % divider == 0)
				{
					pValues.push_back(divider);
					pValue /= divider;
				}
				else
				{
					divider++;
					assert(divider <= pValue);
				}
			}
		};

	std::vector<uint32_t> firstStorage;
	firstStorage.reserve(pFirstValue);
	std::vector<uint32_t> secondStorage;
	secondStorage.reserve(pSecondValue);

	getFactorizationNumbers(firstStorage, pFirstValue);
	getFactorizationNumbers(secondStorage, pSecondValue);

	std::ranges::sort(firstStorage);
	std::ranges::sort(secondStorage);

	std::ranges::set_intersection(firstStorage, secondStorage, std::back_inserter(pValues));
}

int32_t gcd(int32_t pFirstValue, int32_t pSecondValue)
{
	assert(pFirstValue >= 1 && pSecondValue >= 1);
	
	std::vector<uint32_t> primeFactorizationNumbers; 
	primeFactorizationNumbers.reserve(pSecondValue + (pFirstValue - pSecondValue) / 2);
	getPrimeFactorizationNumbers(primeFactorizationNumbers, pFirstValue, pSecondValue);

	return std::accumulate(primeFactorizationNumbers.begin(),
						   primeFactorizationNumbers.end(), 
						   1, 
						   std::multiplies<int32_t>());
}
