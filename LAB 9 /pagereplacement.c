#include <stdio.h>

#define NUM_FRAMES 3
#define NUM_PAGES 10

int frames[NUM_FRAMES];
int counter = 0;
int page_faults = 0;

void reference_page(int page) {
    int found = 0;
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == page) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        if (counter < NUM_FRAMES) {
            frames[counter] = page;
            counter++;
            page_faults++;
        } else {
            frames[counter % NUM_FRAMES] = page;
            page_faults++;
        }
    }
}

void print_frames() {
    printf("Frames: ");
    for (int i = 0; i < NUM_FRAMES; i++) {
        printf("%d ", frames[i]);
    }
    printf("\n");
}

int main() {
    int references[NUM_PAGES] = {4, 2, 1, 5, 2, 4, 5, 3, 2, 1};

    printf("Page References: ");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("%d ", references[i]);
        reference_page(references[i]);
        print_frames();
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
