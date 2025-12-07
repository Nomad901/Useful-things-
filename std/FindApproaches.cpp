#include <iostream>
#include <format>
#include <string>
#include <string_view>
#include <chrono>
#include <ranges>
#include <algorithm>
#include <filesystem>
#include <source_location>

class benchmark
{
public:
	enum class typeOfTime
	{
		MICROSECONDS = 0,
		MILLISECONDS = 1,
		SECONDS = 2,
		MINUTES = 3
	};
public:
	benchmark(std::string_view pNameOfExample = "", typeOfTime pTypeOfTime = typeOfTime::MICROSECONDS)
	{
		mNameOfExample = pNameOfExample;
		mTimePoint1 = std::chrono::steady_clock::now();
		mTypeOfTime = pTypeOfTime;
	}
	int32_t getResult()
	{
		mTimePoint2 = std::chrono::steady_clock::now();
		switch (mTypeOfTime)
		{
		case benchmark::typeOfTime::MICROSECONDS:
			return std::chrono::duration_cast<std::chrono::microseconds>(mTimePoint2 - mTimePoint1).count();
			break;
		case benchmark::typeOfTime::MILLISECONDS:
			return std::chrono::duration_cast<std::chrono::milliseconds>(mTimePoint2 - mTimePoint1).count();
			break;
		case benchmark::typeOfTime::SECONDS:
			return std::chrono::duration_cast<std::chrono::seconds>(mTimePoint2 - mTimePoint1).count();
			break;
		case benchmark::typeOfTime::MINUTES:
			return std::chrono::duration_cast<std::chrono::minutes>(mTimePoint2 - mTimePoint1).count();
			break;
		}

		return 0;
	}
	~benchmark()
	{
		mTimePoint2 = std::chrono::steady_clock::now();
		std::cout << "\n---------------------------\n\n";
		switch (mTypeOfTime)
		{
		case benchmark::typeOfTime::MICROSECONDS:
			if (!mNameOfExample.empty())
			{
				std::cout << std::format("Time: {} microseconds, Example number: {}, Name: {}.\n",
										  std::chrono::duration_cast<std::chrono::microseconds>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples,
										  mNameOfExample);
			}
			else
			{
				std::cout << std::format("Time: {} microseconds, Example number: {}.\n", 
										  std::chrono::duration_cast<std::chrono::microseconds>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples);
			}
			break;
		case benchmark::typeOfTime::MILLISECONDS:
			if (!mNameOfExample.empty())
			{
				std::cout << std::format("Time: {} milliseconds, Example number: {}, Name: {}.\n",
										  std::chrono::duration_cast<std::chrono::milliseconds>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples, 
										  mNameOfExample);
			}
			else
			{
				std::cout << std::format("Time: {} milliseconds, Example number: {}.\n",
										  std::chrono::duration_cast<std::chrono::milliseconds>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples);
			}
			break;
		case benchmark::typeOfTime::SECONDS:
			if (!mNameOfExample.empty())
			{
				std::cout << std::format("Time: {} seconds, Example number: {}, Name: {}.\n",
										  std::chrono::duration_cast<std::chrono::seconds>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples,
										  mNameOfExample);
			}
			else
			{
				std::cout << std::format("Time: {} seconds, Example number: {}.\n",
										  std::chrono::duration_cast<std::chrono::seconds>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples);
			}
			break;
		case benchmark::typeOfTime::MINUTES:
			if (!mNameOfExample.empty())
			{
				std::cout << std::format("Time: {} minutes, Example number: {}, Name: {}.\n",
										  std::chrono::duration_cast<std::chrono::minutes>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples, 
										  mNameOfExample);
			}
			else
			{
				std::cout << std::format("Time: {} minutes, Example number: {}.\n",
										  std::chrono::duration_cast<std::chrono::minutes>(mTimePoint2 - mTimePoint1).count(),
										  mCounterOfExamples);
			}
			break;
		}
		std::cout << "\n---------------------------\n\n";
		mCounterOfExamples++;
	}

public:
	std::chrono::steady_clock::time_point mTimePoint1;
	std::chrono::steady_clock::time_point mTimePoint2;
	typeOfTime mTypeOfTime;
	std::string mNameOfExample;

	static inline uint32_t mCounterOfExamples = 0;
};

int main()
{
	// binary search example:
	// the same thing as usual std::find(), but it operates on sorted array, and this is a bit slower than the usual std::find(),
	// but if u just need to know has the storage an object or not - there you go: it returns bool, not the iterator; 
	{
		benchmark b1("Binary-Search");
		std::vector<int32_t> storageForBinarySearch = { 1, 6, 3, 2, 10, 9, 15, 4 };
		// std::sort(storageForBinarySearch.begin(), storageForBinarySearch.end());
		std::ranges::sort(storageForBinarySearch);
	
		// bool result = std::binary_search(storageForBinarySearch.begin(), storageForBinarySearch.end() 3); 
		bool result = std::ranges::binary_search(storageForBinarySearch, 3);
		std::cout << std::format("Result of binarySearch: {}\n", result);
	}
	{
		benchmark b2("Find");
		std::vector<int32_t> storageForBinarySearch = { 1, 6, 3, 2, 10, 9, 15, 4 };

		//auto result = std::find(storageForBinarySearch.begin(), storageForBinarySearch.end(), 3);
		auto result = std::ranges::find(storageForBinarySearch, 3);

		if (result != storageForBinarySearch.end())
			std::cout << std::format("Result of find: {}\n", true);
		else 
			std::cout << std::format("Result of find: {}\n", false);
	}
	// Lower-bound:
	// finds a number, which is >= than the number, which was written into the search;
	{
		benchmark b3("Lower-bound");
		std::vector<int32_t> storageForBinarySearch = { 1, 6, 3, 2, 10, 9, 15, 4 };
		// std::sort(storageForBinarySearch.begin(), storageForBinarySearch.end());
		std::ranges::sort(storageForBinarySearch);

		//auto it = std::lower_bound(storageForBinarySearch.begin(), storageForBinarySearch.end(), 3);
		auto it = std::ranges::lower_bound(storageForBinarySearch, 3);
		if (*it == 3)
		{
			std::cout << std::format("Iterator points on number with position: {}. Number: {}",
									  std::distance(storageForBinarySearch.begin(), it),
									  *it);
		}
		else
			std::cout << "Number doesnt exist!\n";
	}
	// Upper-bound:
	// finds a number which is > than the number, which was written into the search;
	{
		benchmark b4("Upper-bound");
		std::vector<int32_t> storageForBinarySearch = { 1, 6, 3, 2, 10, 9, 15, 4 };
		// std::sort(storageForBinarySearch.begin(), storageForBinarySearch.end());
		std::ranges::sort(storageForBinarySearch);

		//auto it = std::upper_bound(storageForBinarySearch.begin(), storageForBinarySearch.end(), 3);
		auto it = std::ranges::upper_bound(storageForBinarySearch, 3);
		if (*it == 4)
		{
			std::cout << std::format("Iterator points on number with position: {}. Number: {}",
				std::distance(storageForBinarySearch.begin(), it),
				*it);
		}
		else
			std::cout << "Number doesnt exist!\n";
	}
	{
		benchmark b5("Equal-Range");
		std::vector<int32_t> storageForEqualRange = { 1, 2, 2, 2, 3, 4, 5 };

		//auto range = std::equal_range(storageForEqualRange.begin(), storageForEqualRange.end(), 2);
		auto range = std::ranges::equal_range(storageForEqualRange, 2);
		std::cout << std::format("Range: {}\n", range);
	}
}
