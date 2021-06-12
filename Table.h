#include <mutex>
#include <iostream>

class Table
{
public:
	int N;
	bool* forks;
	int* semaphore;
	int* states;
	int* eating_counts;
	std::mutex* mutex;

	Table(int N);
	void print_state();
};
