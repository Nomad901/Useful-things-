/*
	
	Taken from: https://youtu.be/ywJ4cq67-uc?si=B3-TByzqNevo1wqw

*/

#include <iostream>
#include <format>
#include <thread>
#include <chrono>

int main()
{
	size_t N;
	std::cout << "Number of threads: ";
	std::cin >> N;
	double t_start = 0, t_join = 0;
	double t_start_max = 0, t_join_max = 0;
	for (size_t i = 0; i < N; ++i)
	{
		auto start = std::chrono::system_clock::now();
		auto thread_start = start;
		std::thread t([&] {thread_start = std::chrono::system_clock::now(); });
		t.join();
		auto end = std::chrono::system_clock::now();
		double t1 = std::chrono::duration<double>(end - start).count();
		double t2 = std::chrono::duration<double>(thread_start - start).count();
		t_join += t1;
		t_start += t2;
		if (t1 > t_join_max)
			t_join_max += t1;
		if (t2 > t_start_max)
			t_start_max += t2;
	}
	std::cout << "Average time to start a thread: " << t_start / N << "s, to join: " << t_join / N << "s\n";
	std::cout << "Max time to start a thread: " << t_start_max << "s, to join: " << t_join_max << "s\n";
}