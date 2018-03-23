#include "fcfs_scheduler.h"

using namespace std;


SchedulingDecision* FcfsScheduler::get_next_thread(const Event* event) {
  // TODO: implement me
	if(q.empty()) return nullptr;
	string message = "Selected from " + std::to_string(size()) + " threads: will run to completion of burst";
	SchedulingDecision* decision = new SchedulingDecision(); 
	decision->thread = q.front();
	decision->explanation = message.c_str();
	q.pop();

  return decision;
}


void FcfsScheduler::enqueue(const Event* event, Thread* thread) {
  // TODO: implement me
  q.push(thread);	
}


bool FcfsScheduler::should_preempt_on_arrival(const Event* event) const {
  // TODO: implement me


  return false;
}


size_t FcfsScheduler::size() const {
  // TODO: implement me

  return q.size();
}
