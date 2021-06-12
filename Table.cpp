#include "Table.h"

Table::Table(int N)
{
	this->N = N;
	forks = new bool[N];
	mutex = new std::mutex();
	states = new int[N];
	semaphore = new int[N];
	eating_counts = new int[N];
	for (int i = 0; i < N; i++) {
		states[i] = 1;
		semaphore[i] = 0;
		eating_counts[i] = 0;
		forks[i] = false;
	}
}

void Table::print_state()
{
	for (int i = 0; i < N; i++) {
		std::cout << "State of philosopher nr " << i << " is ";
		switch (states[i])
		{
		case 0:
			std::cout << "HUNGRY  ";
			break;
		case 1:
			std::cout << "SLEEPING";
			break;
		case 2:
			std::cout << "EATING  ";
			break;
		default:
			std::cout << "UNKNOWN ";
			break;
		}
		std::cout << " and ate " << eating_counts[i] << " times     "<<std::endl;
	}
	std::cout << std::endl << "Forks:"<< std::endl;
	for (int i = 0; i < N; i++) {
		std::cout << forks[i] <<" ";
	}
}
