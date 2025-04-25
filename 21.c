#include <windows.h>
#include <stdio.h>

// Function to execute a process
void executeProcess(const char *processName) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create the process
    if (!CreateProcess(NULL, (LPSTR)processName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "Error: CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until the child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// Function to execute FCFS scheduling algorithm program
void executeFCFS() {
    executeProcess("C:\\Users\\Asus\\OneDrive\\Documents\\VSC\\C\\gtk project\\scheduling_algorithms\\fcfs.exe");
}

// Function to execute Preemptive SJF scheduling algorithm program
void executePreemptiveSJF() {
    executeProcess("C:\\Users\\Asus\\OneDrive\\Documents\\VSC\\C\\gtk project\\scheduling_algorithms\\preemptive_sjf.exe");
}

// Function to execute Non-Preemptive SJF scheduling algorithm program
void executeNonPreemptiveSJF() {
    executeProcess("C:\\Users\\Asus\\OneDrive\\Documents\\VSC\\C\\gtk project\\scheduling_algorithms\\nonpreemptive_sjf.exe");
}

// Function to execute Round Robin scheduling algorithm program
void executeRoundRobin() {
    executeProcess("C:\\Users\\Asus\\OneDrive\\Documents\\VSC\\C\\gtk project\\scheduling_algorithms\\roundrobin.exe");
}

// Function to execute Priority scheduling algorithm program
void executePriority() {
    executeProcess("C:\\Users\\Asus\\OneDrive\\Documents\\VSC\\C\\gtk project\\scheduling_algorithms\\priority.exe");
}

// Main function
int main() {
    // Example: Execute FCFS program
    executeFCFS();

    // Example: Execute Preemptive SJF program
    executePreemptiveSJF();

    // Example: Execute Non-Preemptive SJF program
    executeNonPreemptiveSJF();

    // Example: Execute Round Robin program
    executeRoundRobin();

    // Example: Execute Priority program
    executePriority();

    return 0;
}
