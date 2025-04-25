#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10

void printCenterAligned(char *text);
void preemptiveSJF(int n, int a[], int b[]);

void printCenterAligned(char *text) {
    int length = strlen(text);
    int spaces = (80 - length) / 2;
    printf("%*s%s%*s\n", spaces, "", text, spaces, "");
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

    preemptiveSJF(n, a, b);

    return 0;
}
