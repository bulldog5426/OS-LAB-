#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to simulate the FCFS disk scheduling algorithm
void fcfs(int requests[], int n_requests, int head_position) {
    int total_distance = 0;
    int current_position = head_position;

    printf("FCFS Sequence: ");
    for (int i = 0; i < n_requests; i++) {
        printf("%d ", requests[i]);
        total_distance += abs(requests[i] - current_position);
        current_position = requests[i];
    }

    printf("\nTotal head movement: %d\n", total_distance);
}

// Function to simulate the LOOK disk scheduling algorithm
void look(int requests[], int n_requests, int head_position, bool direction_up) {
    int total_distance = 0;
    int current_position = head_position;
    int min_request = 0, max_request = 199;

    // Find min and max requests
    for (int i = 0; i < n_requests; i++) {
        if (requests[i] < min_request) {
            min_request = requests[i];
        }
        if (requests[i] > max_request) {
            max_request = requests[i];
        }
    }

    // Initialize variables for LOOK
    bool *visited = (bool *)malloc(n_requests * sizeof(bool));
    for (int i = 0; i < n_requests; i++) {
        visited[i] = false;
    }

    // Perform LOOK in the specified direction
    printf("LOOK Sequence: ");
    while (true) {
        bool found = false;
        if (direction_up) {
            for (int i = current_position; i <= max_request; i++) {
                for (int j = 0; j < n_requests; j++) {
                    if (requests[j] == i && !visited[j]) {
                        printf("%d ", requests[j]);
                        total_distance += abs(requests[j] - current_position);
                        current_position = requests[j];
                        visited[j] = true;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            direction_up = false;
        } else {
            for (int i = current_position; i >= min_request; i--) {
                for (int j = 0; j < n_requests; j++) {
                    if (requests[j] == i && !visited[j]) {
                        printf("%d ", requests[j]);
                        total_distance += abs(requests[j] - current_position);
                        current_position = requests[j];
                        visited[j] = true;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            direction_up = true;
        }

        bool all_visited = true;
        for (int i = 0; i < n_requests; i++) {
            if (!visited[i]) {
                all_visited = false;
                break;
            }
        }

        if (all_visited) {
            break;
        }
    }

    printf("\nTotal head movement: %d\n", total_distance);
    free(visited);
}

int main() {
    int n_requests, head_position;
    bool direction_up;
    int *requests;

    printf("Enter the number of requests: ");
    scanf("%d", &n_requests);

    requests = (int *)malloc(n_requests * sizeof(int));
    if (requests == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the requests: ");
    for (int i = 0; i < n_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head_position);

    printf("Enter the direction (1 for up, 0 for down): ");
    scanf("%d", &direction_up);
    if (direction_up != 0 && direction_up != 1) {
        printf("Invalid direction.\n");
        return 1;
    }

    int choice;
    while (true) {
        printf("\nDisk Scheduling Algorithms:\n");
        printf("1. First-Come-First-Serve (FCFS)\n");
        printf("2. LOOK\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fcfs(requests, n_requests, head_position);
                break;
            case 2:
                look(requests, n_requests, head_position, direction_up);
                break;
            case 3:
                free(requests);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
