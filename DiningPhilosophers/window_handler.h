#include <array>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <ncurses.h>

/*
 Klasa obslugujaca wyswietlanie stanu watkow i zasobow
*/

using namespace std;

struct position{
	int row, col;
};

class Window_handler{

private:
	array<char*, 5> names;
	array<position, 5> philosophers_positions;
	array<position, 5> forks_positions;

public:
	mutex write_mutex;
	Window_handler();
	void init();
	void set_name(int, char*);
	void set_state(int, char*);
	void set_fork(int, bool);
	void countdown(int, float);
};