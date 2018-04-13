Project 3: CPU Scheduling Simulator

Name: Allee Zarrini

Files and what they do:
	util folder: Has all the flags, and logger stuff that were pre-implemented for us by josh

	types folder: This folder for the most part didn't take any modification. Only thread.h and thread.cpp. Contains declarations for bursts, events, processes, threads that are used in our simulations. Also, includes a class on which scheduling_decision is used in our simulation, alongside system stats that are printed at the end.

	algorithms folder: contains the code for our schedulers. Code is included for first come first serve, multilevel feedback, priority, and round robin. 

	main.cpp and simulations.h are untouched.

	simulation.cpp: Contains all the code for the simulation and stats printing. The simulation follows the flowchart of piazza almost exactly. Plus a few other timing and task keeping associated with the code.

Approximate Hours: 20 hrs

MLFQ:
	The implementation of this was very similar to the implementation of priority. Instead we utilize double the number of queues and has a time slice assoicated. The secondary queue only checks to see if the thread has been preempted before hand. I've added a boolean to thread to account for this preemption. The time slice follows 3 seconds similar to our round robin. You will notice that the secondary queue's are alotted a larger time slice. This process however, is very susceptible to starvation. Especially by adding more queues, we allow some of our lower, level queues, like the queues for batch to stay stuck in a lower level for a very long time. This is why the secondary queues have a larger time slice allocated to them. 

Essential Notes:
Collaboration and josh thomas' generosity in class was essential to completing this project.



 
