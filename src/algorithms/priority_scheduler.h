#pragma once
#include "algorithms/scheduler.h"
#include "types/event.h"
#include "types/scheduling_decision.h"
#include "types/thread.h"
#include "types/process.h"
#include <queue>

/**
 * Represents a scheduling queue that gives threads of each type a different
 * priority.
 */
class PriorityScheduler : public Scheduler {
public:

  virtual SchedulingDecision* get_next_thread(const Event* event) override;


  virtual void enqueue(const Event* event, Thread* thread) override;


  virtual bool should_preempt_on_arrival(const Event* event) const override;


  virtual size_t size() const override;

private:

	std::queue<Thread*> qSys;
	std::queue<Thread*> qInt;
	std::queue<Thread*> qNor;
	std::queue<Thread*> qBa;
  // TODO: add any instance variables you need
};
