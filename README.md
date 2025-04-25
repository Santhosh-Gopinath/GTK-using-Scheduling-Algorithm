CPU Scheduler with GTK Interface
A C-based CPU scheduler implementing FCFS, Priority (Preemptive and Non-Preemptive), and Round Robin scheduling algorithms. The program features a GTK+ 3.0 graphical interface for inputting process details (PID, arrival time, burst time, priority) and displays the scheduling results, including a Gantt chart, completion times, turnaround times, waiting times, and averages, in the terminal.
Features

Graphical Interface: Built with GTK+ 3.0 for easy input of process details.
Scheduling Algorithms:
First-Come, First-Serve (FCFS)
Priority Scheduling (Preemptive and Non-Preemptive)
Round Robin (with configurable time quantum)


Output: Detailed terminal output with Gantt chart and process metrics.
Input Format: Enter processes in the format PID,Arrival,Burst,Priority (one per line).

Prerequisites

GTK+ 3.0 development libraries (libgtk-3-dev on Ubuntu/Debian)
GCC compiler

Installation

Install GTK+ 3.0:sudo apt-get install libgtk-3-dev


Clone the repository:git clone https://github.com/Santhosh-Gopinath/GTK-using-Scheduling-Algorithm.git
cd GTK-using-Scheduling-Algorithm


Compile the program:gcc scheduler.c -o scheduler `pkg-config --cflags --libs gtk+-3.0`


Run the program:./scheduler



Usage

Launch the program to open the GTK window.
Enter process details in the text area (e.g., 1,0,5,2\n2,1,3,1\n3,2,4,3).
Specify the time quantum for Round Robin (default: 2).
Select the scheduling algorithm (FCFS, Priority, or Round Robin).
Check the "Preemptive" box for Priority scheduling if desired.
Click "Run Scheduler" to compute and display results in the terminal.

Example Output
For input:
1,0,5,2
2,1,3,1
3,2,4,3

Using FCFS, the terminal output might be:
Gantt Chart:
| P1 (0-5) | P2 (5-8) | P3 (8-12) |

PID     Arrival Burst   Priority        Completion      Turnaround      Waiting
1       0       5       2               5               5               0
2       1       3       1               8               7               4
3       2       4       3               12              10              6

Average Turnaround Time: 7.33
Average Waiting Time: 3.33

Contributing
Contributions are welcome! Feel free to:

Add new scheduling algorithms.
Enhance the GTK interface (e.g., display results in the GUI).
Improve documentation or error handling.

License
MIT License
