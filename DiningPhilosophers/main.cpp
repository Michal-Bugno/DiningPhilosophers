#include "philosopher.h"

using namespace std;



void quit_check(){
	while(getch() != 'q')
		continue;
}



int main(){
	table dining_table;
	dining_table.ready = false;
	
	Window_handler handler;
	handler.init();
	array<Philosopher, 5> philosophers
	{
		{
			{"Philosopher0", 0, handler, dining_table, dining_table.forks[0], dining_table.forks[1]},
			{"Philosopher1", 1, handler, dining_table, dining_table.forks[1], dining_table.forks[2]},
			{"Philosopher2", 2, handler, dining_table, dining_table.forks[2], dining_table.forks[3]},
			{"Philosopher3", 3, handler, dining_table, dining_table.forks[3], dining_table.forks[4]},
			{"Philosopher4", 4, handler, dining_table, dining_table.forks[4], dining_table.forks[0]}
		}
	};

	

	philosophers[4].set_neighbor(&philosophers[0]);
	for(int i = 0; i<4; i++){
		philosophers[i].set_neighbor(&philosophers[(i+1)]);
	}


	
	array<thread*, 5> threads;
	for(int i = 0; i<5; i++)
		threads[i] = new thread(&Philosopher::dine, &philosophers[i]);

	dining_table.ready = true;
	
	thread* quit_checking_thread = new thread(quit_check);
	quit_checking_thread->join();

	dining_table.ready = false;
	move(0, 0);
	printw("Finishing...");
	for(int i = 0; i<5; i++)
		threads[i]->join();
	endwin();
	fflush(stdout);

}