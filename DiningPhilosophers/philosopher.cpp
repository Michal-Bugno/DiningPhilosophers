#include "philosopher.h"
#include <iostream>
using namespace std;

Philosopher::Philosopher(char* n, int i, Window_handler& _handler, table& t, mutex& left, 
	mutex& right) : name(n), index(i), handler(_handler), dining_table(t), left_fork(left),
	right_fork(right) {
		can_eat = new atomic<bool>{true};
		handler.set_name(index, name);
	}

void Philosopher::set_neighbor(Philosopher* neighbor){
	right_neighbor = neighbor;
}


void Philosopher::set_can_eat(bool can){
	*can_eat = can;
}

void Philosopher::dine(){
	while(!dining_table.ready){
		continue;
	}

	do{
		think();
		eat();
	} while(dining_table.ready);
}

void Philosopher::eat(){
	handler.set_state(index, "----trying to eat---");
	if(!can_eat)
		return;
	left_fork.lock();
	handler.set_fork(index, false);
	this_thread::sleep_for(chrono::milliseconds(500));
	bool has_forks = right_fork.try_lock(); //Uzycie try_lock zapobiega zakleszczeniu
	if(!has_forks){
		left_fork.unlock();
		handler.set_fork(index, true);
		return;
	}
	handler.set_fork((index+1)%5, false);
	handler.set_state(index, "-------eating-------");
	handler.countdown(index, rand()%3+2);
	handler.set_state(index, "---finished eating--");
	right_fork.unlock();
	handler.set_fork((index+1)%5, true);
	this_thread::sleep_for(chrono::milliseconds(500));
	left_fork.unlock();
	handler.set_fork(index, true);
	set_can_eat(false); //Zapobiega wyglodzeniu
	right_neighbor->set_can_eat(true);
}

void Philosopher::think(){
	handler.set_state(index, "------thinking------");
	handler.countdown(index, rand()%3+2);
}