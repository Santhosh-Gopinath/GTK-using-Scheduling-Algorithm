#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10

void printCenterAligned(char *text);
void FCFS(int n, int a[], int b[]);

void printCenterAligned(char *text) {
    int length = strlen(text);
    int spaces = (80 - length) / 2;
    printf("%*s%s%*s\n", spaces, "", text, spaces, "");
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

int main() {
    int n, i;
    int a[MAX_PROCESSES], b[MAX_PROCESSES];

    printf("Enter the number of processes (max 10): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &a[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &b[i]);
    }

    FCFS(n, a, b);

    return 0;
}
