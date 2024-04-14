#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a page
typedef struct {
    int number;  // Page number
    int time;    // Time of last reference
} Page;

// Function to find the index of the oldest page in the frames
int find_oldest_page(Page *frames, int n_frames) {
    int oldest_index = 0;
    int oldest_time = frames[0].time;

    for (int i = 1; i < n_frames; i++) {
        if (frames[i].time < oldest_time) {
            oldest_index = i;
            oldest_time = frames[i].time;
        }
    }

    return oldest_index;
}

// Function to simulate FIFO page replacement algorithm
int fifo(int pages[], int n_pages, int n_frames) {
    Page *frames = (Page *)malloc(n_frames * sizeof(Page));
    if (frames == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    int page_faults = 0;
    int frame_index = 0;

    for (int i = 0; i < n_pages; i++) {
        bool page_found = false;

        // Check if the page is already in the frames
        for (int j = 0; j < n_frames; j++) {
            if (frames[j].number == pages[i]) {
                page_found = true;
                break;
            }
        }

        // If page not found, replace the oldest page in the frames
        if (!page_found) {
            frames[frame_index].number = pages[i];
            frames[frame_index].time = i;
            frame_index = (frame_index + 1) % n_frames;
            page_faults++;
        }
    }

    free(frames);
    return page_faults;
}

// Function to simulate Optimal page replacement algorithm
int optimal(int pages[], int n_pages, int n_frames) {
    Page *frames = (Page *)malloc(n_frames * sizeof(Page));
    if (frames == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    int page_faults = 0;
    int frame_index = 0;

    for (int i = 0; i < n_pages; i++) {
        bool page_found = false;

        // Check if the page is already in the frames
        for (int j = 0; j < n_frames; j++) {
            if (frames[j].number == pages[i]) {
                page_found = true;
                break;
            }
        }

        // If page not found, find the page that will not be used for the longest time
        if (!page_found) {
            if (frame_index < n_frames) {
                frames[frame_index].number = pages[i];
                frames[frame_index].time = i;
                frame_index++;
            } else {
                int oldest_index = find_oldest_page(frames, n_frames);
                frames[oldest_index].number = pages[i];
                frames[oldest_index].time = i;
            }
            page_faults++;
        }
    }

    free(frames);
    return page_faults;
}

int main() {
    int n_pages, n_frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n_pages);
    int *pages = (int *)malloc(n_pages * sizeof(int));
    if (pages == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the page sequence: ");
    for (int i = 0; i < n_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &n_frames);

    int fifo_faults = fifo(pages, n_pages, n_frames);
    printf("Total page faults using FIFO: %d\n", fifo_faults);

    int optimal_faults = optimal(pages, n_pages, n_frames);
    printf("Total page faults using Optimal: %d\n", optimal_faults);

    free(pages);
    return 0;
}
