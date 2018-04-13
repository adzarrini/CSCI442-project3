#include "round_robin_scheduler.h"

using namespace std;


SchedulingDecision* RoundRobinScheduler::get_next_thread(const Event* event) {
  // TODO: implement me
	if(q.size()==0) return nullptr;
	SchedulingDecision* decision = new SchedulingDecision(); 
	decision->thread = q.front();
	decision->time_slice = 3;
	string message = "Selected from " + std::to_string(size()) + " threads; will run for at most " + std::to_string(decision->time_slice) + " ticks";
	decision->explanation = message.c_str();
	q.pop();

  return decision;
}


void RoundRobinScheduler::enqueue(const Event* event, Thread* thread) {
  // TODO: implement me
  q.push(thread);
}


bool RoundRobinScheduler::should_preempt_on_arrival(const Event* event) const {
  // TODO: implement me
  return false;
}


size_t RoundRobinScheduler::size() const {
  // TODO: implement me
  return q.size();
}
