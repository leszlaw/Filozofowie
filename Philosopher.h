#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       
#include "Table.h"

class Philosopher
{
	std::thread* thread;
	int number;
	Table* table;
	int eating_time;
	int sleeping_time;

public:
	bool running;
	static const int HUNGRY = 0;
	static const int SLEEPING = 1;
	static const int EATING = 2;

	Philosopher(Table* table,int number,int sleeping_time,int eating_time);
	void update();
	void join();
	void detach();
	void eat();
	void sleep();
	void take_forks();
	void put_forks();
	void test(int i);
};
