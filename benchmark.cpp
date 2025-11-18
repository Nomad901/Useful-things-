#include <iostream>
#include <format>
#include <chrono>

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
	benchmark(typeOfTime pTypeOfTime = typeOfTime::MICROSECONDS)
	{
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
		switch (mTypeOfTime)
		{
		case benchmark::typeOfTime::MICROSECONDS:
			std::cout<<std::format("Time: {}\n", std::chrono::duration_cast<std::chrono::microseconds>(mTimePoint2 - mTimePoint1).count());
			break;
		case benchmark::typeOfTime::MILLISECONDS:
			std::cout << std::format("Time: {}\n", std::chrono::duration_cast<std::chrono::milliseconds>(mTimePoint2 - mTimePoint1).count());
			break;
		case benchmark::typeOfTime::SECONDS:
			std::cout << std::format("Time: {}\n", std::chrono::duration_cast<std::chrono::seconds>(mTimePoint2 - mTimePoint1).count());
			break;
		case benchmark::typeOfTime::MINUTES:
			std::cout << std::format("Time: {}\n", std::chrono::duration_cast<std::chrono::minutes>(mTimePoint2 - mTimePoint1).count());
			break;
		}
	}

public:
	std::chrono::steady_clock::time_point mTimePoint1;
	std::chrono::steady_clock::time_point mTimePoint2;
	typeOfTime mTypeOfTime;
};

int main()
{
	// first example with using destructor;
	{
		benchmark b;
		uint32_t counter = 0;
		for (size_t i = 0; i < 100000; i++)
		{
			counter++;
		}
	}

	// second example with using getResult() method;
	benchmark b;
	uint32_t counter = 0;
	for (size_t i = 0; i < 100000; i++)
	{
		counter++;
	}
	std::cout<<std::format("Time of the counter: {}\n", b.getResult());
}

