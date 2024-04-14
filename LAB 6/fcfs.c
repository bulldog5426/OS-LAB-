#include <stdio.h>

// Structure to represent a process
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
} Process;

// Function to calculate waiting time and turnaround time for FCFS scheduling
void fcfs(Process processes[], int n, int waiting[], int turnaround[]) {
    int completion[n];  // Completion time for each process

    // Initialize completion time for the first process
    completion[0] = processes[0].burst;

    // Calculate completion time for each process
    for (int i = 1; i < n; i++) {
        completion[i] = completion[i - 1] + processes[i].burst;
    }

    // Calculate waiting time and turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - processes[i].arrival;
        waiting[i] = turnaround[i] - processes[i].burst;
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAverageTimes(Process processes[], int n) {
    int waiting[n], turnaround[n];
    float totalWaiting = 0, totalTurnaround = 0;

    // Calculate waiting time and turnaround time using FCFS
    fcfs(processes, n, waiting, turnaround);

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
    }

    // Calculate and print average waiting time and turnaround time
    calculateAverageTimes(processes, n);

    return 0;
}
