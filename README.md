# Process Scheduling Algorithms
An implementation of various process scheduling algorithms in C++. The algorithms included are First Come First Serve (FCFS), Round Robin (RR), Shortest Job Next (SJN), Shortest Remaining Time (SRT), Highest Response Ratio Next (HRRN), and Aging.

## Table of Contents
- [Process Scheduling Algorithms](#process-scheduling-algorithms)
  - [Algorithms](#algorithms)
    - [First Come First Serve (FCFS)](#first-come-first-serve-fcfs)
    - [Round Robin with varying time quantum (RR)](#round-robin-with-varying-time-quantum-rr)
    - [Shortest Job Next (SJN)](#shortest-job-next-sjn)
    - [Shortest Remaining Time (SRT)](#shortest-remaining-time-srt)
    - [Highest Response Ratio Next (HRRN)](#highest-response-ratio-next-hrrn)
    - [Aging](#aging)

## Algorithms

### First Come First Serve (FCFS)
- First Come First Served (FCFS) is a scheduling algorithm in which the process that arrives first is executed first. It is a simple and easy-to-understand algorithm, but it can lead to poor performance if there are processes with long burst times. This algorithm does not have any mechanism for prioritizing processes, so it is considered a non-preemptive algorithm. In FCFS scheduling, the process that arrives first is executed first, regardless of its burst time or priority. This can lead to poor performance, as longer running processes will block shorter ones from being executed. It is commonly used in batch systems where the order of the processes is important.

### Round Robin with varying time quantum (RR)
- Round Robin (RR) with variable quantum is a scheduling algorithm that uses a time-sharing approach to divide CPU time among processes. In this version of RR, the quantum (time slice) is not fixed and can be adjusted depending on the requirements of the processes.

- The algorithm works by maintaining a queue of processes, where each process is given a quantum of time to execute on the CPU. When a process's quantum expires, it is moved to the back of the queue, and the next process in the queue is given a quantum of time to execute.

- The variable quantum allows the algorithm to be more efficient as it allows the CPU to spend more time on shorter processes and less time on longer ones. This can help to minimize the average waiting time for processes. Additionally, it also helps to avoid the issue of starvation, which occurs when a process with a long burst time prevents other processes from executing.

### Shortest Job Next (SJN)
- Shortest Job Next (SJN) is a scheduling algorithm that prioritizes the execution of processes based on their burst time, or the amount of time they need to complete their task. It is a non-preemptive algorithm which means that once a process starts executing, it runs until completion or until it enters a waiting state.

- The algorithm maintains a queue of processes, where each process is given a burst time when it arrives. The process with the shortest burst time is executed first, and as new processes arrive, they are added to the queue and sorted based on their burst time. The process with the shortest burst time will always be at the front of the queue, and thus will always be executed next.

- This algorithm can be beneficial in situations where the objective is to minimize the average waiting time for processes, since shorter processes will be executed first, and thus will spend less time waiting in the queue. However, it can lead to longer running processes being blocked by shorter ones, which can negatively impact the overall performance of the system.

- In summary, SJN is a scheduling algorithm that prioritizes the execution of processes based on their burst time, it's non-preemptive and it's commonly used in situations where the objective is to minimize the average waiting time for processes.

### Shortest Remaining Time (SRT)
- Shortest Remaining Time Next (SRT) is a scheduling algorithm that is similar to the Shortest Process Next (SJN) algorithm, but it is a preemptive algorithm. This means that once a process starts executing, it can be interrupted by a new process with a shorter remaining time.

- The algorithm maintains a queue of processes, where each process is given a burst time when it arrives. The process with the shortest remaining time is executed first, and as new processes arrive, they are added to the queue and sorted based on their remaining time. The process with the shortest remaining time will always be at the front of the queue, and thus will always be executed next.

- This algorithm can be beneficial in situations where the objective is to minimize the average waiting time for processes, since shorter processes will be executed first, and thus will spend less time waiting in the queue. Additionally, it can be useful in situations where the burst time of processes is not known in advance, since the algorithm can adapt to changes in the remaining time as the process is executing.

- In summary, SRT is a scheduling algorithm that prioritizes the execution of processes based on their remaining time, it's a preemptive algorithm, which means that it can interrupt a process that's already executing if a new process with a shorter remaining time arrives and it's commonly used in situations where the objective is to minimize the average waiting time for processes and burst time is not known in advance.

### Highest Response Ratio Next (HRRN)

- Highest Response Ratio Next (HRRN) is a scheduling algorithm that prioritizes the execution of processes based on their response ratio. It is a non-preemptive algorithm which means that once a process starts executing, it runs until completion or until it enters a waiting state.

- The response ratio is calculated by taking the ratio of the waiting time of a process and its burst time. The process with the highest response ratio is executed first, and as new processes arrive, they are added to the queue and sorted based on their response ratio. The process with the highest response ratio will always be at the front of the queue, and thus will always be executed next.

- This algorithm can be beneficial in situations where the objective is to minimize the average waiting time for processes, since processes with longer waiting times will be executed first, and thus will spend less time waiting in the queue. Additionally, it can be useful in situations where the burst time of processes is not known in advance, since the algorithm can adapt to changes in the waiting time as the process is executing.

- In summary, HRRN is a scheduling algorithm that prioritizes the execution of processes based on their response ratio, it's non-preemptive and it's commonly used in situations where the objective is to minimize the average waiting time for processes and burst time is not known in advance.

### Aging

- Xinu is an operating system developed at Purdue University. The scheduling invariant in Xinu assumes that at any
time, the highest priority process eligible for CPU service is executing, with round-robin scheduling for processes of
equal priority. Under this scheduling policy, the processes with the highest priority will always be executing. As a
result, all the processes with lower priority will never get CPU time. As a result, starvation is produced in Xinu when
we have two or more processes eligible for execution that have different priorities. For ease of discussion, we call the
set of processes in the ready list and the current process as the eligible processes.

- To overcome starvation, an aging scheduler may be used. On each rescheduling operation, a timeout for instance, the
scheduler increases the priority of all the ready processes by a constant number. This avoids starvation as each ready
process can be passed over by the scheduler only a finite number of times before it has the highest priority.

- Each process has an initial priority that is assigned to it at process creation. Every time the scheduler is called it takes
the following steps.
    - The priority of the current process is set to the initial priority assigned to it.
    - The priorities of all the ready processes (not the current process) are incremented by 1.
    - The scheduler choses the highest priority process from among all the eligible processes.
