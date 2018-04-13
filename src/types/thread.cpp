#include "types/thread.h"

void Thread::set_ready(int time) {
	if(current_state == State::NEW) arrival_time = time;
	if(previous_state == State::NEW) state_change_time = time;
	previous_state = current_state;
	current_state = State::READY;
	
}

void Thread::set_running(int time) {
	if((int)start_time == -1) start_time = time;
	if(previous_state == State::NEW) state_change_time = time;
	previous_state = current_state;
	current_state = Thread::State::RUNNING;
}

void Thread::set_blocked(int time) {
	if(previous_state == State::NEW) state_change_time = time;
	previous_state = current_state;
	current_state = Thread::State::BLOCKED;
}

void Thread::set_exit(int time) {
	if(previous_state == State::NEW) state_change_time = time;
	previous_state = current_state;
	current_state = Thread::State::EXIT;
	end_time = time;
}

// TODO: implement the behavior for your thread methods (optional)
