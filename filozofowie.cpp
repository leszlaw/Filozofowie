#include <Windows.h>
#include "Philosopher.h"

void cls()
{
    COORD pos;	pos.X = 0;	pos.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main()
{
    int N, sleeping_time, eating_time;
    std::cout << "Write parameters one by one: philosopher_count -> sleeping_time (ms) -> eating_time (ms) ."<<std::endl;
    std::cin >> N >> sleeping_time >> eating_time;
    system("cls");
    Philosopher** philosophers = new Philosopher * [N];
    Table* table = new Table(N);
    for (int i = 0; i < N; i++) {
        philosophers[i] = new Philosopher(table, i,sleeping_time,eating_time);
    }
    while (true) {
        table->print_state();
        if (GetKeyState('Q') & 0x8000)
        {
            for (int i = 0; i < N; i++) {
                philosophers[i]->detach();
            }
            return 0;
        }
        cls();
        Sleep(100);
    }
}