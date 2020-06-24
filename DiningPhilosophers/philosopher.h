#include <atomic>
#include <string>
#include "window_handler.h"

/*
 Klasa reprezentuje filozofa
*/

using namespace std;


struct table{
	atomic<bool> ready{false};
	array<mutex, 5> forks;  //Reprezentacja widelcow za pomoca mutexow
};

class Philosopher{
private:
	char* name;
	int index;
	Window_handler& handler;
	Philosopher* right_neighbor;
	atomic<bool>* can_eat;
	table& dining_table;
	mutex& left_fork;
	mutex& right_fork;

public:
	Philosopher(char*, int, Window_handler&, table&, mutex&, mutex&);
	void set_neighbor(Philosopher*);
	void dine();
	void think();
	void eat();
	void set_can_eat(bool);
	void set_name(int, char*);
};