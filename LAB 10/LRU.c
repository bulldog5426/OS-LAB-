#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a page
typedef struct {
    int number;  // Page number
    int time;    // Time of last reference
} Page;

// Function to find the index of the least recently used page in the frames
int find_lru_page(Page *frames, int n_frames) {
    int lru_index = 0;
    int lru_time = frames[0].time;

    for (int i = 1; i < n_frames; i++) {
        if (frames[i].time < lru_time) {
            lru_index = i;
            lru_time = frames[i].time;
        }
    }

    return lru_index;
}

// Function to simulate LRU page replacement algorithm
int lru(int pages[], int n_pages, int n_frames) {
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
                frames[j].time = i;  // Update last reference time
                page_found = true;
                break;
            }
        }

        // If page not found, find the least recently used page and replace it
        if (!page_found) {
            if (frame_index < n_frames) {
                frames[frame_index].number = pages[i];
                frames[frame_index].time = i;
                frame_index++;
            } else {
                int lru_index = find_lru_page(frames, n_frames);
                frames[lru_index].number = pages[i];
                frames[lru_index].time = i;
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

    int lru_faults = lru(pages, n_pages, n_frames);
    printf("Total page faults using LRU: %d\n", lru_faults);

    free(pages);
    return 0;
}
