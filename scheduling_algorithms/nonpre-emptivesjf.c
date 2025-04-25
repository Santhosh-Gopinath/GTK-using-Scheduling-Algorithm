#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10

void printCenterAligned(char *text);
void nonPreemptiveSJF(int n, int a[], int b[], int p[]);

void printCenterAligned(char *text) {
    int length = strlen(text);
    int spaces = (80 - length) / 2;
    printf("%*s%s%*s\n", spaces, "", text, spaces, "");
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

int main() {
    int n, i;
    int a[MAX_PROCESSES], b[MAX_PROCESSES], p[MAX_PROCESSES];

    printf("Enter the number of processes (max 10): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &a[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &b[i]);
        p[i] = i + 1; // Process number for reference in Gantt chart
    }

    nonPreemptiveSJF(n, a, b, p);

    return 0;
}
