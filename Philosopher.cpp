#include "Philosopher.h"

void start(Philosopher* p) {
	while (p->running) {
		p->update();
	}
}

Philosopher::Philosopher(Table* table,int number, int sleeping_time, int eating_time)
{
	this->running = true;
	thread = new std::thread(start, this);
	this->table = table;
	this->number = number;
	this->sleeping_time = sleeping_time;
	this->eating_time = eating_time;
}

void Philosopher::update()
{
	sleep();
	take_forks();
	eat();
	put_forks();
}

void Philosopher::join()
{
	this->running = false;
	thread->join();
}

void Philosopher::detach()
{
	this->running = false;
	thread->detach();
}

void Philosopher::eat()
{
	srand(time(NULL) + number);
	int random_delta = (rand() % 41 - 20) * eating_time / 100;
	table->eating_counts[number]++;
	std::this_thread::sleep_for(std::chrono::milliseconds(eating_time + random_delta));
}

void Philosopher::sleep()
{
	srand(time(NULL) + number);
	int random_delta = (rand() % 41 - 20) * sleeping_time / 100;
	std::this_thread::sleep_for(std::chrono::milliseconds(sleeping_time + random_delta));
}

void Philosopher::take_forks()
{
	table->mutex->lock();
	table->states[number] = HUNGRY;
	test(number);
	table->mutex->unlock();
	while (!table->semaphore[number]);
	table->semaphore[number]--;
}

void Philosopher::put_forks()
{
	table->mutex->lock();
	table->states[number] = SLEEPING;
	table->forks[number] = false;
	table->forks[(number + 1) % table->N] = false;
	test((number - 1 + table->N) % (table->N));
	test((number + 1 + table->N) % (table->N));
	table->mutex->unlock();
}

void Philosopher::test(int i)
{
	if (table->states[i] == HUNGRY &&
		table->states[(i - 1 + table->N) % (table->N)] != EATING &&
		table->states[(i + 1 + table->N) % (table->N)] != EATING) {
		table->states[i] = EATING;
		table->semaphore[i]++;
		table->forks[i] = true;
		table->forks[(i + 1) % table->N] = true;
	}
}