#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10

void printCenterAligned(char *text);
void roundRobin(int n, int a[], int b[], int quantum);

void printCenterAligned(char *text) {
    int length = strlen(text);
    int spaces = (80 - length) / 2;
    printf("%*s%s%*s\n", spaces, "", text, spaces, "");
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

int main() {
    int n, i, quantum;
    int a[MAX_PROCESSES], b[MAX_PROCESSES];

    printf("Enter the number of processes (max 10): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &a[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &b[i]);
    }

    printf("Enter quantum time: ");
    scanf("%d", &quantum);

    roundRobin(n, a, b, quantum);

    return 0;
}
