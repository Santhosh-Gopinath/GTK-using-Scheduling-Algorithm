#include <stdio.h>
#include <string.h>

#define MAX_PROCESSES 10

void printCenterAligned(char *text);
void priority(int n, int a[], int b[], int p[], int pr[]);

void printCenterAligned(char *text) {
    int length = strlen(text);
    int spaces = (80 - length) / 2;
    printf("%*s%s%*s\n", spaces, "", text, spaces, "");
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
    int n, i;
    int a[MAX_PROCESSES], b[MAX_PROCESSES], p[MAX_PROCESSES], pr[MAX_PROCESSES];

    printf("Enter the number of processes (max 10): ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &a[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &b[i]);
        p[i] = i + 1; // Process number for reference in Gantt chart
        printf("Enter priority for process P%d: ", i + 1);
        scanf("%d", &pr[i]);
    }

    priority(n, a, b, p, pr);

    return 0;
}
