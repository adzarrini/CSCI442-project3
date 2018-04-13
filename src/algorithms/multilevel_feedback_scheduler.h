#pragma once
#include "algorithms/scheduler.h"
#include "types/event.h"
#include "types/scheduling_decision.h"
#include "types/thread.h"
#include "types/process.h"

/**
 * Represents a scheduling queue that demotes threads after being preempted.
 */
class MultilevelFeedbackScheduler : public Scheduler {
public:

  virtual SchedulingDecision* get_next_thread(const Event* event) override;


  virtual void enqueue(const Event* event, Thread* thread) override;


  virtual bool should_preempt_on_arrival(const Event* event) const override;


  virtual size_t size() const override;

private:

	std::queue<Thread*> q0;
	std::queue<Thread*> q1;
	std::queue<Thread*> q2;
	std::queue<Thread*> q3;

	std::queue<Thread*> q4;
	std::queue<Thread*> q5;
	std::queue<Thread*> q6;
	std::queue<Thread*> q7;
  // TODO: add any instance variables you need
};
