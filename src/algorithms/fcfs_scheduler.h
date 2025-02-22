#pragma once
#include "algorithms/scheduler.h"
#include "types/event.h"
#include "types/scheduling_decision.h"
#include "types/thread.h"
#include<queue>

/**
 * Represents a scheduling queue that uses first-come, first-served.
 */
class FcfsScheduler : public Scheduler {
public:

  virtual SchedulingDecision* get_next_thread(const Event* event) override;


  virtual void enqueue(const Event* event, Thread* thread) override;


  virtual bool should_preempt_on_arrival(const Event* event) const override;


  virtual size_t size() const override;

private:

	std::queue<Thread*> q;
  // TODO: add any instance variables you need
};
