#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 10

void printCenterAligned(char *text);
void printMenu();
void FCFS(int n, int a[], int b[]);
void preemptiveSJF(int n, int a[], int b[]);
void nonPreemptiveSJF(int n, int a[], int b[], int p[]);
void roundRobin(int n, int a[], int b[], int quantum);
void priority(int n, int a[], int b[], int p[], int pr[]);

void printCenterAligned(char *text) {
    int length = strlen(text);
    int spaces = (80 - length) / 2;
    printf("%*s%s%*s\n", spaces, "", text, spaces, "");
}

void printMenu() {
    printf("***********************************************************************************\n");
    printCenterAligned("PROCESS SCHEDULING SIMULATOR");
    printf("***********************************************************************************\n");
    printCenterAligned("1. FCFS");
    printCenterAligned("2. PRE-EMPTIVE SJF");
    printCenterAligned("3. NON PRE-EMPTIVE SJF");
    printCenterAligned("4. ROUND ROBIN");
    printCenterAligned("5. PRIORITY");
    printf("\n");
}

void FCFS(int n, int a[], int b[]) {
    int wt[n], tat[n], i;
    float avg_wt = 0, avg_tat = 0;
    wt[0] = 0;

    // Calculate waiting time for each process
    for (i = 1; i < n; i++)
        wt[i] = wt[i-1] + b[i-1];

    // Calculate turnaround time and averages
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + b[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    // Print Gantt chart
    printf("\n");
    printCenterAligned("Gantt Chart (FCFS):");
    printf(" ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n|");
    for (i = 0; i < n; i++)
        printf("  P%d   |", i + 1);
    printf("\n ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n0");
    for (i = 0; i < n; i++)
        printf("      %d", wt[i] + b[i]);
    printf("\n");

    // Print average waiting time and average turnaround time
    printf("\nAverage waiting time: %.2f\n", avg_wt);
    printf("Average turnaround time: %.2f\n", avg_tat);
}

void preemptiveSJF(int n, int a[], int b[]) {
    int remainingTime[n], wt[n], tat[n];
    int i, currentTime = 0, completed = 0, shortest = -1;
    for (i = 0; i < n; i++)
        remainingTime[i] = b[i];

    while (completed != n) {
        shortest = -1;
        for (i = 0; i < n; i++) {
            if (a[i] <= currentTime && remainingTime[i] > 0) {
                if (shortest == -1 || remainingTime[i] < remainingTime[shortest]) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        remainingTime[shortest]--;
        currentTime++;

        if (remainingTime[shortest] == 0) {
            completed++;
            wt[shortest] = currentTime - a[shortest] - b[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = b[i] + wt[i];
    }

    // Calculate average waiting time and average turnaround time
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    // Print Gantt chart
    printf("\n");
    printCenterAligned("Gantt Chart (Preemptive SJF):");
    printf(" ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n|");
    for (i = 0; i < n; i++)
        printf("  P%d   |", i + 1);
    printf("\n ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n0");
    for (i = 0; i < n; i++)
        printf("      %d", tat[i]);
    printf("\n");

    // Print average waiting time and average turnaround time
    printf("\nAverage waiting time: %.2f\n", avg_wt);
    printf("Average turnaround time: %.2f\n", avg_tat);
}

void nonPreemptiveSJF(int n, int a[], int b[], int p[]) {
    int wt[n], tat[n], i, j;
    int completed[n], s = 0;
    memset(completed, 0, sizeof(completed));

    for (i = 0; i < n; i++) {
        int min_bt = 999, min_index = -1;
        for (j = 0; j < n; j++) {
            if (!completed[j] && a[j] <= s && b[j] < min_bt) {
                min_bt = b[j];
                min_index = j;
            }
        }

        if (min_index != -1) {
            s += b[min_index];
            tat[min_index] = s - a[min_index];
            wt[min_index] = tat[min_index] - b[min_index];
            completed[min_index] = 1;
        }
    }

    // Calculate average waiting time and average turnaround time
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    // Printing Gantt chart
    printf("\n");
    printCenterAligned("Gantt Chart (Non-preemptive SJF):");
    printf(" ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n|");
    for (i = 0; i < n; i++)
        printf("  P%d   |", p[i]);
    printf("\n ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n0");
    for (i = 0; i < n; i++)
        printf("      %d", tat[i]);
    printf("\n");

    // Printing results
    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t\t%d\n", p[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

void roundRobin(int n, int a[], int b[], int quantum) {
    int i, wt[n], tat[n], remaining_time[n];
    int gantt[n * 10], gantt_time[n * 10]; // Assuming a maximum of 10 quanta per process for Gantt chart
    int gantt_index = 0; // To track the Gantt chart entries

    for (i = 0; i < n; i++)
        remaining_time[i] = b[i];

    int currentTime = 0;
    int completed = 0;

    while (completed != n) {
        for (i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                if (remaining_time[i] > quantum) {
                    currentTime += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    currentTime += remaining_time[i];
                    wt[i] = currentTime - b[i] - a[i];
                    remaining_time[i] = 0;
                    completed++;
                }
                // Record in Gantt chart
                gantt[gantt_index] = i + 1; // Process number
                gantt_time[gantt_index] = currentTime; // Time when process completes
                gantt_index++;
            }
        }
    }

    // Calculate turnaround time and averages
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        tat[i] = b[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;

    // Print Gantt chart
    printf("\n");
    printCenterAligned("Gantt Chart (Round Robin):");
    printf(" ");
    for (i = 0; i < gantt_index; i++)
        printf("-------");
    printf("\n|");
    for (i = 0; i < gantt_index; i++)
        printf("  P%d   |", gantt[i]);
    printf("\n ");
    for (i = 0; i < gantt_index; i++)
        printf("-------");
    printf("\n0");
    for (i = 0; i < gantt_index; i++)
        printf("      %d", gantt_time[i]);
    printf("\n");

    // Print average waiting time and average turnaround time
    printf("\nAverage waiting time: %.2f\n", avg_wt);
    printf("Average turnaround time: %.2f\n", avg_tat);
}

void priority(int n, int a[], int b[], int p[], int pr[]) {
    int wt[n], tat[n], i, j;

    // Sorting based on priority using Selection Sort
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                int temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;

                temp = b[i];
                b[i] = b[j];
                b[j] = temp;

                temp = a[i];
                a[i] = a[j];
                a[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculating completion time
    int comp[n], s = 0;
    for (i = 0; i < n; i++) {
        s += b[i];
        comp[i] = s;
    }

    // Calculating turnaround time and waiting time
    for (i = 0; i < n; i++) {
        tat[i] = comp[i] - a[i];
        wt[i] = tat[i] - b[i];
    }

    // Calculating average waiting time and average turnaround time
    float avg_wt = 0, avg_tat = 0;
    for (j = 0; j < n; j++) {
        avg_wt += wt[j];
        avg_tat += tat[j];
    }
    avg_wt /= n;
    avg_tat /= n;

    // Printing Gantt chart
    printf("\n");
    printCenterAligned("Gantt Chart (Priority Scheduling):");
    printf(" ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n|");
    for (i = 0; i < n; i++)
        printf("  P%d   |", p[i]);
    printf("\n ");
    for (i = 0; i < n; i++)
        printf("-------");
    printf("\n0");
    for (i = 0; i < n; i++)
        printf("      %d", comp[i]);
    printf("\n");

    // Printing results
    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t\t%d\n", p[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}

int main() {
    int n, i, choice, quantum;
    int a[MAX_PROCESSES], b[MAX_PROCESSES], p[MAX_PROCESSES], pr[MAX_PROCESSES];

    while (1) {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 5) {
            printf("Invalid choice, please try again.\n");
            continue;
        }

        printf("Enter the number of processes (max 10): ");
        scanf("%d", &n);

        for (i = 0; i < n; i++) {
            printf("Enter arrival time for process P%d: ", i + 1);
            scanf("%d", &a[i]);
            printf("Enter burst time for process P%d: ", i + 1);
            scanf("%d", &b[i]);
            p[i] = i + 1; // Process number for reference in Gantt chart
            if (choice == 5) {
                printf("Enter priority for process P%d: ", i + 1);
                scanf("%d", &pr[i]);
            }
        }

        if (choice == 4) {
            printf("Enter quantum time: ");
            scanf("%d", &quantum);
        }

        switch (choice) {
            case 1:
                FCFS(n, a, b);
                break;
            case 2:
                preemptiveSJF(n, a, b);
                break;
            case 3:
                nonPreemptiveSJF(n, a, b, p);
                break;
            case 4:
                roundRobin(n, a, b, quantum);
                break;
            case 5:
                priority(n, a, b, p, pr);
                break;
            default:
                printf("Invalid choice.\n");
        }

        printf("\nDo you want to simulate another scheduling algorithm? (y/n): ");
        char cont;
        scanf(" %c", &cont);
        if (cont == 'n' || cont == 'N')
            break;
    }

    return 0;
}
