#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    bool visited;   // Flag to track if the process is visited or not
} Process;

// Function to find the process with the shortest burst time
int findShortestJob(Process processes[], int n, int time) {
    int minBurst = __INT_MAX__;
    int shortestJob = -1;

    for (int i = 0; i < n; i++) {
        if (!processes[i].visited && processes[i].arrival <= time && processes[i].burst < minBurst) {
            minBurst = processes[i].burst;
            shortestJob = i;
        }
    }

    return shortestJob;
}

// Function to calculate waiting time and turnaround time for SJF scheduling
void sjf(Process processes[], int n, int waiting[], int turnaround[]) {
    int time = 0;
    int completed = 0;

    while (completed < n) {
        int shortestJob = findShortestJob(processes, n, time);
        if (shortestJob == -1) {
            time++;
            continue;
        }

        waiting[shortestJob] = time - processes[shortestJob].arrival;
        turnaround[shortestJob] = waiting[shortestJob] + processes[shortestJob].burst;
        processes[shortestJob].visited = true;
        time += processes[shortestJob].burst;
        completed++;
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAverageTimes(Process processes[], int n) {
    int waiting[n], turnaround[n];
    float totalWaiting = 0, totalTurnaround = 0;

    // Calculate waiting time and turnaround time using SJF
    sjf(processes, n, waiting, turnaround);

    // Print process details and times
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival, processes[i].burst,
               waiting[i], turnaround[i]);
        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];
    }

    // Calculate and print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    printf("Enter arrival and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst);
        processes[i].visited = false;
    }

    // Calculate and print average waiting time and turnaround time
    calculateAverageTimes(processes, n);

    return 0;
}
