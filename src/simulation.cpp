#include "simulation.h"
#include "types/event.h"
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;


void Simulation::run(const string& filename) {
  read_file(filename);

  // While their are still events to process, invoke the corresponding methods
  // to handle them.
  while (!events.empty()) {
    const Event* event = events.top();
    events.pop();

    // Invoke the appropriate method on the scheduler for the given event type.
    switch (event->type) {
    case Event::THREAD_ARRIVED:
      handle_thread_arrived(event);
      break;

    case Event::THREAD_DISPATCH_COMPLETED:
      handle_thread_dispatch_completed(event);
      break;

    case Event::PROCESS_DISPATCH_COMPLETED:
      handle_process_dispatch_completed(event);
      break;

    case Event::CPU_BURST_COMPLETED:
      handle_cpu_burst_completed(event);
      break;

    case Event::IO_BURST_COMPLETED:
      handle_io_burst_completed(event);
      break;

    case Event::THREAD_COMPLETED:
      handle_thread_completed(event);
      break;

    case Event::THREAD_PREEMPTED:
      handle_thread_preempted(event);
      break;

    case Event::DISPATCHER_INVOKED:
      handle_dispatcher_invoked(event);
      break;
    }
    if (event->thread && event->thread->current_state != event->thread->previous_state) {
      logger.print_state_transition(event, event->thread->previous_state, event->thread->current_state);
    }

    stats.total_time = event->time;
    // Free the event's memory.
    delete event;
  }

  for(auto entry: processes) {
    logger.print_process_details(entry.second);
  }
  logger.print_statistics(calculate_statistics());
}


//==============================================================================
// Event-handling methods
//==============================================================================


void Simulation::handle_thread_arrived(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // Set ready enqueue
  // if(Processor idle) {
  //  DISPATCHER_INVOKED;
  //}
  //else {
  // Thread Preempted
  //}

  event->thread->set_ready(event->time);
  scheduler->enqueue(event, event->thread);
  if(active_thread == nullptr) {
    add_event(new Event(Event::Type::DISPATCHER_INVOKED, event->time, nullptr));  
  }
  // else{
  //   // Does not need to be implemented for FCFS. 
  // }

  //cout << "event: THREAD_ARRIVED" << endl;
}


void Simulation::handle_thread_dispatch_completed(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // Set running
  // Set last thread = current thread;
  // if (thread time slice < burst time) {
  //   Thread preempted;
  // }
  // else {
  //   cpu burst completed;
  // }

  event->thread->set_running(event->time);

  int time_slice = event->scheduling_decision->time_slice;
  int burst_length = event->thread->bursts.front()->length;

  size_t event_time = (time_slice == -1) 
    ? (event->time+burst_length) 
    : event->time + time_slice;

  if(time_slice < burst_length) {
    event->thread->service_time += burst_length;
    add_event(new Event(Event::Type::CPU_BURST_COMPLETED, event_time, event->thread));
  }
  else {
    add_event(new Event(Event::Type::THREAD_PREEMPTED, event_time, event->thread));
  }

  
  //cout << "event: THREAD_DISPATCH_COMPLETED" << endl;
}


void Simulation::handle_process_dispatch_completed(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // Set running
  // Set last thread = current thread;
  // if (thread time slice < burst time) {
  //   THrad preempted;
  // }
  // else {
  //   cput burst completed;
  // }

  event->thread->set_running(event->time);

  int time_slice = event->scheduling_decision->time_slice;
  int burst_length = event->thread->bursts.front()->length;

  size_t event_time = (time_slice == -1) 
    ? (event->time+burst_length) 
    : event->time + time_slice;



  if(time_slice < burst_length) {
    event->thread->service_time += burst_length;
    add_event(new Event(Event::Type::CPU_BURST_COMPLETED, event_time, event->thread));
  }
  else {
    add_event(new Event(Event::Type::THREAD_PREEMPTED, event_time, event->thread));
  }


  cout << "event: THREAD_PROCESS_COMPLETED" << endl;
}


void Simulation::handle_cpu_burst_completed(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // pop burst
  // unset current thread
  // dispatcher invoker;
  // if(last cpu burst) {
  //   thread competed;
  // }
  // else {
  //   set blocked;
  //   io burst completed;
  // }

  event->thread->bursts.pop();
  prev_thread = active_thread;
  active_thread = nullptr;

  if(event->thread->bursts.empty()){
    add_event(new Event(Event::Type::THREAD_COMPLETED, event->time,event->thread));
  }
  else{
    event->thread->set_blocked(event->time);

    Burst* temp = event->thread->bursts.front();
    event->thread->io_time+=temp->length;
    add_event(new Event(Event::Type::IO_BURST_COMPLETED,event->time+temp->length,event->thread));
  }
  add_event(new Event(Event::Type::DISPATCHER_INVOKED, event->time, event->thread));

  cout << "event: CPU_BURST_COMPLETED" << endl;
}


void Simulation::handle_io_burst_completed(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // set ready 
  // enqueu;
  // pop burst;
  // dispatcher invoked;

  event->thread->set_ready(event->time);
  scheduler->enqueue(event, event->thread);
  event->thread->bursts.pop();
  if(active_thread == NULL) {
    add_event(new Event(Event::Type::DISPATCHER_INVOKED, event->time, event->thread));
  }

  cout << "event: IO_BURST_COMPLETED" << endl;
}


void Simulation::handle_thread_completed(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // set exit;
  event->thread->set_exit(event->time);

  //add_event(new Event(Event::DISPATCHER_INVOKED, event->time, nullptr));

  cout << "event: THREAD_COMPLETED" << endl;
}


void Simulation::handle_thread_preempted(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // Set ready enqueue
  //decrese cpu burst
  // thread dispatcher envoked;

  event->thread->set_ready(event->time);

  scheduler->enqueue(event, event->thread);

  add_event(new Event(Event::DISPATCHER_INVOKED, event->time, nullptr));

  cout << "event: THREAD_PREEMPTED" << endl;
}


void Simulation::handle_dispatcher_invoked(const Event* event) {
  // TODO: handle this event properly (feel free to modify code structure, tho)

  // Get scheduling decision and set current thread
  // if(made decision) {
  //   if(process switch){
  //     thread dispatch completed
  //   }
  //   else {
  //     process dispatch completed
  //   }
  // }

  if(scheduler->size() !=0){
    SchedulingDecision* scheduling_decision = scheduler->get_next_thread(event);
    if(prev_thread != nullptr){
      if(prev_thread->process != scheduling_decision->thread->process){
        stats.dispatch_time+=process_switch_overhead;
        add_event(new Event(Event::Type::PROCESS_DISPATCH_COMPLETED, event->time + process_switch_overhead, scheduling_decision->thread,scheduling_decision));
      }
      else{
        stats.dispatch_time+=thread_switch_overhead;
        add_event(new Event(Event::Type::THREAD_DISPATCH_COMPLETED, event->time+thread_switch_overhead, scheduling_decision->thread,scheduling_decision));
      }
    }
    else{
      stats.dispatch_time+=process_switch_overhead;
      add_event(new Event(Event::Type::PROCESS_DISPATCH_COMPLETED, event->time + process_switch_overhead, scheduling_decision->thread,scheduling_decision));
    }

    active_thread = scheduling_decision->thread;
  }

  cout << "event: DISPATCHER_INVOKED" << endl;
}


//==============================================================================
// Utility methods
//==============================================================================


void Simulation::add_event(Event* event) {
  if (event != nullptr) {
    events.push(event);
  }
}


void Simulation::read_file(const string& filename) {
  ifstream file(filename.c_str());

  if (!file) {
    cerr << "Unable to open simulation file: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  size_t num_processes;

  // Read the total number of processes, as well as the dispatch overheads.
  file >> num_processes >> thread_switch_overhead >> process_switch_overhead;

  // Read in each process.
  for (size_t p = 0; p < num_processes; p++) {
    Process* process = read_process(file);

    processes[process->pid] = process;
  }
}


Process* Simulation::read_process(istream& in) {
  int pid, type;
  size_t num_threads;

  // Read in the process ID, its type, and the number of threads.
  in >> pid >> type >> num_threads;

  // Create the process and register its existence in the processes map.
  Process* process = new Process(pid, (Process::Type) type);

  // Read in each thread in the process.
  for (size_t tid = 0; tid < num_threads; tid++) {
    process->threads.push_back(read_thread(in, tid, process));
  }

  return process;
}


Thread* Simulation::read_thread(istream& in, int tid, Process* process) {
  int arrival_time;
  size_t num_cpu_bursts;

  // Read in the thread's arrival time and its number of CPU bursts.
  in >> arrival_time >> num_cpu_bursts;

  Thread* thread = new Thread(arrival_time, tid, process);

  // Read in each burst in the thread.
  for (size_t n = 0, burst_length; n < num_cpu_bursts * 2 - 1; n++) {
    in >> burst_length;

    Burst::Type burst_type = (n % 2 == 0)
        ? Burst::CPU
        : Burst::IO;

    thread->bursts.push(new Burst(burst_type, burst_length));
  }

  // Add an arrival event for the thread.
  events.push(new Event(Event::THREAD_ARRIVED, thread->arrival_time, thread));

  return thread;
}


SystemStats Simulation::calculate_statistics() {
  // TODO: your code here (optional; feel free to modify code structure)
  for(auto entry : processes) {
    Process* process = entry.second;
    Process::Type type = process->type;
    for(Thread*thread : process->threads) {
      stats.thread_counts[type]++;
      stats.service_time += thread->service_time;
      stats.io_time += thread->io_time;
      stats.avg_thread_response_times[type] += thread-> response_time();
      stats.avg_thread_turnaround_times[type] += thread-> turnaround_time();
    }
  }
  stats.total_cpu_time = stats.service_time + stats.dispatch_time;
  stats.total_idle_time = stats.total_time - stats.total_cpu_time;
  stats.cpu_utilization = 100.0*stats.total_cpu_time / stats.total_time;
  stats.cpu_efficiency = 100.0*stats.service_time / stats.total_time;

  for(size_t i = Process::SYSTEM; i <= Process::BATCH; i++) {
    if(stats.thread_counts[i] == 0) continue;
    stats.avg_thread_response_times[i] /= stats.thread_counts[i];
    stats.avg_thread_turnaround_times[i] /= stats.thread_counts[i];
  }

  return stats;
}
