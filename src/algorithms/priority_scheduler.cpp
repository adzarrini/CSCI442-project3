#include "algorithms/priority_scheduler.h"

using namespace std;


SchedulingDecision* PriorityScheduler::get_next_thread(const Event* event) {
  if(size() == 0) return nullptr;
	SchedulingDecision* decision = new SchedulingDecision();
	if(!qSys.empty()) {
		decision->thread = qSys.front();
		string message = "Selected from queue 0 [S:"+std::to_string(qSys.size())+" I:"+
		std::to_string(qInt.size())+" N:"+std::to_string(qNor.size())+" B:"+
		std::to_string(qBa.size())+"]";
		decision->explanation = message.c_str();
		qSys.pop();
	}
	else if(!qInt.empty()) {
		decision->thread = qInt.front();
		string message = "Selected from queue 1 [S:"+std::to_string(qSys.size())+" I:"+
		std::to_string(qInt.size())+" N:"+std::to_string(qNor.size())+" B:"+
		std::to_string(qBa.size())+"]";
		decision->explanation = message.c_str();
		qInt.pop();
	}
	else if(!qNor.empty()) {
		decision->thread = qNor.front();
		string message = "Selected from queue 2 [S:"+std::to_string(qSys.size())+" I:"+
		std::to_string(qInt.size())+" N:"+std::to_string(qNor.size())+" B:"+
		std::to_string(qBa.size())+"]";
		decision->explanation = message.c_str();
		qNor.pop();
	}
	else if(!qBa.empty()) {
		decision->thread = qBa.front();
		string message = "Selected from queue 3 [S:"+std::to_string(qSys.size())+" I:"+
		std::to_string(qInt.size())+" N:"+std::to_string(qNor.size())+" B:"+
		std::to_string(qBa.size())+"]";
		decision->explanation = message.c_str();
		qBa.pop();
	}

  return decision;

}


void PriorityScheduler::enqueue(const Event* event, Thread* thread) {
  // TODO: implement me
  switch(event->thread->process->type){
  	case Process::Type::SYSTEM:
  		qSys.push(thread);
  		break;
  	case Process::Type::INTERACTIVE:
  		qInt.push(thread);
  		break;
  	case Process::Type::NORMAL:
  		qNor.push(thread);
  		break;
  	case Process::Type::BATCH:
  		qBa.push(thread);
  		break;
  }
}


bool PriorityScheduler::should_preempt_on_arrival(const Event* event) const {
  // TODO: implement me
  return false;
}


size_t PriorityScheduler::size() const {
  // TODO: implement me
  return qSys.size()+qInt.size()+qNor.size()+qBa.size();
}
