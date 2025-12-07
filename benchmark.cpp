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



