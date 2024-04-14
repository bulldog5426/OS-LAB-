#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort the requests in ascending order
void sortRequests(int requests[], int numRequests) {
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                swap(&requests[j], &requests[j + 1]);
            }
        }
    }
}

// Function to simulate SSTF (Shortest Seek Time First) algorithm
void sstf(int requests[], int numRequests, int head) {
    int totalSeekTime = 0;
    int visited[MAX_REQUESTS] = {0};

    for (int i = 0; i < numRequests; i++) {
        int minSeek = abs(head - requests[0]);
        int minIndex = 0;
        for (int j = 1; j < numRequests; j++) {
            if (!visited[j] && abs(head - requests[j]) < minSeek) {
                minSeek = abs(head - requests[j]);
                minIndex = j;
            }
        }
        visited[minIndex] = 1;
        totalSeekTime += minSeek;
        head = requests[minIndex];
    }

    printf("SSTF Total Seek Time: %d\n", totalSeekTime);
}

// Function to simulate SCAN algorithm
void scan(int requests[], int numRequests, int head, int direction) {
    int totalSeekTime = 0;

    sortRequests(requests, numRequests);

    int i, pos;
    for (i = 0; i < numRequests; i++) {
        if (requests[i] >= head) {
            pos = i;
            break;
        }
    }

    if (direction == 0) { // Left
        for (int j = pos - 1; j >= 0; j--) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
        totalSeekTime += head;
        head = 0;
        for (int j = pos; j < numRequests; j++) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
    } else { // Right
        for (int j = pos; j < numRequests; j++) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
        totalSeekTime += (999 - head);
        head = 999;
        for (int j = pos - 1; j >= 0; j--) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
    }

    printf("SCAN Total Seek Time: %d\n", totalSeekTime);
}

// Function to simulate C-SCAN algorithm
void cscan(int requests[], int numRequests, int head, int direction) {
    int totalSeekTime = 0;

    sortRequests(requests, numRequests);

    int i, pos;
    for (i = 0; i < numRequests; i++) {
        if (requests[i] >= head) {
            pos = i;
            break;
        }
    }

    if (direction == 0) { // Left
        for (int j = pos - 1; j >= 0; j--) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
        totalSeekTime += (999 - requests[numRequests - 1]);
        head = 999;
        for (int j = 0; j < pos; j++) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
    } else { // Right
        for (int j = pos; j < numRequests; j++) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
        totalSeekTime += head;
        head = 0;
        for (int j = numRequests - 1; j >= pos; j--) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
    }

    printf("C-SCAN Total Seek Time: %d\n", totalSeekTime);
}

// Function to simulate C-LOOK algorithm
void clook(int requests[], int numRequests, int head, int direction) {
    int totalSeekTime = 0;

    sortRequests(requests, numRequests);

    int i, pos;
    for (i = 0; i < numRequests; i++) {
        if (requests[i] >= head) {
            pos = i;
            break;
        }
    }

    if (direction == 0) { // Left
        for (int j = pos - 1; j >= 0; j--) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
        for (int j = numRequests - 1; j >= pos; j--) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
    } else { // Right
        for (int j = pos; j < numRequests; j++) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
        for (int j = 0; j < pos; j++) {
            totalSeekTime += abs(head - requests[j]);
            head = requests[j];
        }
    }

    printf("C-LOOK Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int requests[MAX_REQUESTS], numRequests, head, direction;

    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    printf("Enter the requests: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    sstf(requests, numRequests, head);
    scan(requests, numRequests, head, direction);
    cscan(requests, numRequests, head, direction);
    clook(requests, numRequests, head, direction);

    return 0;
}
