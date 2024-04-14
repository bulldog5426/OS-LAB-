#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int allocated;
    int *data;
} Block;

typedef struct {
    int size;
    int allocated;
    int *data;
} Process;

Block *blocks;
Process *processes;
int num_blocks, num_processes;

void mem_init() {
    blocks = NULL;
    num_blocks = 0;

    // Initialize memory blocks
    int block_size = 100;
    for (int i = 0; i < num_blocks; i++) {
        blocks = (Block *)realloc(blocks, sizeof(Block) * (num_blocks + 1));
        blocks[num_blocks].size = block_size;
        blocks[num_blocks].allocated = 0;
        blocks[num_blocks].data = NULL;
        num_blocks++;
        block_size += 100;
    }
}

void dump_mem_structs() {
    printf("Memory Blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: Size = %d, Allocated = %d\n", i, blocks[i].size, blocks[i].allocated);
    }

    printf("Processes:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: Size = %d, Allocated = %d\n", i, processes[i].size, processes[i].allocated);
    }
}

int worst_fit(int process_size) {
    int max_index = -1;
    int max_size = -1;

    for (int i = 0; i < num_blocks; i++) {
        if (blocks[i].allocated == 0 && blocks[i].size >= process_size) {
            if (blocks[i].size > max_size) {
                max_size = blocks[i].size;
                max_index = i;
            }
        }
    }

    if (max_index == -1) {
        return -1;
    }

    blocks[max_index].allocated = 1;
    blocks[max_index].data = (int *)malloc(process_size * sizeof(int));
    processes[current_process].allocated = 1;

    return max_index;
}

void my_malloc(int process_size) {
    int block_index = worst_fit(process_size);
    if (block_index == -1) {
        printf("Memory allocation failed for process %d\n", current_process);
        return;
    }

    printf("Process %d allocated to Block %d\n", current_process, block_index);

    // Update memory block and process data structures
    blocks[block_index].size -= process_size;
    processes[current_process].allocated = 1;
    processes[current_process].data = blocks[block_index].data;

    current_process++;
}

void my_free(int process_index) {
    if (processes[process_index].allocated == 0) {
        printf("Process %d is not allocated any memory\n", process_index);
        return;
