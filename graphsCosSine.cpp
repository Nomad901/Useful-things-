int32_t main()
{ 
	int32_t size = 80, height = 21;

	std::vector<std::string> chart(height, std::string(size, ' '));
	chart[height / 2] = std::string(size, '-');

	for (int32_t i = 0; i < size; ++i) 
	{
		float findingCosine = 10 * std::cos(i / 4.5) + 10;
		int32_t equation = std::round(findingCosine);
		chart[static_cast<int32_t>(equation)][i] = 'x';
	}

	for (auto&& s : chart) 
	{
		std::cout << s << '\n';
	}
}
