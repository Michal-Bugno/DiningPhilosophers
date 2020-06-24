#include "window_handler.h"

using namespace std;

Window_handler::Window_handler(){
	philosophers_positions[2] = {5, 5};
	philosophers_positions[1] = {5, 40};
	philosophers_positions[0] = {5, 75};
	philosophers_positions[3] = {10, 10};
	philosophers_positions[4] = {10, 40};

	forks_positions[3] = {9, 1};
	forks_positions[2] = {5, 30};
	forks_positions[1] = {5, 65};
	forks_positions[0] = {9, 69};
	forks_positions[4] = {9, 30};
}

void Window_handler::init(){
	initscr();
	resizeterm(20, 100);
	curs_set(0);
	refresh();
	move(0, 0);
	printw("Philosophers\n");
	printw("_ - fork available, | - in use");
	printw("q - quit\n");
	refresh();
	for(int i = 0; i<5; i++)
		set_fork(i, true);
}

void Window_handler::set_state(int index, char* state){
	write_mutex.lock();
	move(philosophers_positions[index].row+1, philosophers_positions[index].col);
	printw(state);
	refresh();
	write_mutex.unlock();
}

void Window_handler::set_name(int index, char* name){
	write_mutex.lock();
	names[index] = name;
	move(philosophers_positions[index].row, philosophers_positions[index].col);
	printw(names[index]);
	refresh();
	write_mutex.unlock();
}

void Window_handler::set_fork(int index, bool available){
	write_mutex.lock();
	move(forks_positions[index].row, forks_positions[index].col);
	if(available){
		printw("_ fork %d", index);
	}
	else{
		printw("| fork %d", index);
	}
	refresh();
	write_mutex.unlock();
}

void Window_handler::countdown(int index, float time){
	for(float i = time; i>=0; i-=0.1){
		this_thread::sleep_for(chrono::milliseconds(100));
		write_mutex.lock();
		move(philosophers_positions[index].row+2, philosophers_positions[index].col);
		printw("%.1f", i);
		refresh();
		write_mutex.unlock();
	}
}