#include <iostream>
#include <format>
#include <future>
#include <vector>

int main()
{
	/*
	 * The difference between std::async and std::packaged_task:
	 *
	 * std::async:
	 * - Executes immediately when created
	 * - Works like std::jthread + built-in result storage
	 * - Convenient but inflexible - "fire and forget"
	 * - Your hands are tied: you can only check status and get results
	 *
	 * std::packaged_task:
	 * - Gives you ultimate flexibility and control
	 * - Create now, execute whenever you want
	 * - Get results on your own terms
	 * - Perfect for advanced task management
	 *
	 * Think of it like:
	 * - std::async = Creating 3D-models in blender (they are created automatically, u dont need to write a code)
	 * - std::packaged_task = Creating 3D-models in a code on your own (u need to create all of this by your hands)
	 */

	// creating vectors:
	// tasks - a package of std::packaged_task which we will execute in the future;
	// results - a storage of future-results accordingly;
	// realResults - a storage of results from future-result. cuz future contains the result, it doesnt give it at once >:(;
	std::vector<std::packaged_task<int32_t()>> tasks;
	std::vector<std::future<int32_t>> results;
	std::vector<int32_t> realResults;

	// counter and i are created for clogging up somehow a function;
	int64_t counter = 1;
	for (int64_t i = 0; i < 15; ++i, ++counter)
	{
		// creating the std::packaged_task with the function; 
		// std::packaged_task<return_type(parameters)>;
		std::packaged_task<int32_t()> task([i, counter] {return std::pow(i, counter); });
		
		// getting the future for our storage of futures, which we can get in the FUTURE;
		results.push_back(task.get_future());

		// just moving our tasks here in order to execute them later;
		tasks.push_back(std::move(task));
	}

	// executing the tasks by taking values from tasks-storage;
	// again, this is so flexible, u can invoke the function whenever u want!;
	for (auto& i : tasks)
	{
		i();
	}

	// getting the results of those tasks; 
	for (auto& i : results)
	{
		realResults.push_back(i.get());
	}

	// writing out the results in the console;
	for (size_t i = 0; i < realResults.size(); ++i)
	{
		std::cout << std::format("Result - {}: {}\n", i, realResults[i]);
	}
}
