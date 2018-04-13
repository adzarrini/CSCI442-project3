#include "algorithms/multilevel_feedback_scheduler.h"

using namespace std;


SchedulingDecision* MultilevelFeedbackScheduler::get_next_thread(
    const Event* event) {
  // TODO: implement me
  if(size() == 0) return nullptr;
	SchedulingDecision* decision = new SchedulingDecision();

	if (!q0.empty()) {
		decision->thread = q0.front();
		decision->time_slice = 3;
		decision->explanation = "Selected from queue 0";
		q0.pop();
	}
	else if (!q1.empty()) {
		decision->thread = q1.front();
		decision->time_slice = 3;
		decision->explanation = "Selected from queue 1";
		q1.pop();
	}
	else if (!q2.empty()) {
		decision->thread = q2.front();
		decision->time_slice = 3;
		decision->explanation = "Selected from queue 2";
		q2.pop();
	}
	else if (!q3.empty()) {
		decision->thread = q3.front();
		decision->time_slice = 3;
		decision->explanation = "Selected from queue 3";
		q3.pop();
	}
	else if (!q4.empty()) {
		decision->thread = q4.front();
		decision->time_slice = 5;
		decision->explanation = "Selected from queue 4";
		q4.pop();
	}
	else if (!q5.empty()) {
		decision->thread = q5.front();
		decision->time_slice = 6;
		decision->explanation = "Selected from queue 5";;
		q5.pop();
	}
	else if (!q6.empty()) {
		decision->thread = q6.front();
		decision->time_slice = 7;
		decision->explanation = "Selected from queue 6";;
		q6.pop();
	}
	else if (!q7.empty()) {
		decision->thread = q7.front();
		decision->time_slice = 8;
		decision->explanation = "Selected from queue 7";
		q7.pop();
	}
  return decision;
}


void MultilevelFeedbackScheduler::enqueue(const Event* event, Thread* thread) {
  // TODO: implement me
  	switch(event->thread->process->type){
		case Process::Type::SYSTEM:
			if(event->thread->preempted) q4.push(thread);
			else q0.push(thread);
			break;
		case Process::Type::INTERACTIVE:
			if(event->thread->preempted) q5.push(thread);
			else q1.push(thread);;
			break;
		case Process::Type::NORMAL:
			if(event->thread->preempted) q6.push(thread);
			else q2.push(thread);
			break;
		case Process::Type::BATCH:
			if(event->thread->preempted) q7.push(thread);
			else q3.push(thread);
			break;
		}
}


bool MultilevelFeedbackScheduler::should_preempt_on_arrival(const Event* event) const {
  return false;
}


size_t MultilevelFeedbackScheduler::size() const {
  // TODO: implement me
  return q0.size() + q1.size() + q2.size() + q3.size() + q4.size() + q5.size() + q6.size() + q7.size();
}
