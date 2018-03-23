#include "fcfs_scheduler.h"

using namespace std;


SchedulingDecision* FcfsScheduler::get_next_thread(const Event* event) {
  // TODO: implement me
  return event->scheduling_decision;
}


void FcfsScheduler::enqueue(const Event* event, Thread* thread) {
  // TODO: implement me
  event->type = Event::THREAD_ARRIVED;
	event->scheduling_decision->thread = thread;
	size++;
}


bool FcfsScheduler::should_preempt_on_arrival(const Event* event) const {
  // TODO: implement me
	

  return false;
}


size_t FcfsScheduler::size() const {
  // TODO: implement me

  return size;
}
