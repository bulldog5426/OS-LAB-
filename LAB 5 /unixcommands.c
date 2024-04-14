#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate the ls -l command
void ls_l(const char *directory) {
    char command[100];
    sprintf(command, "ls -l %s", directory);
    system(command);
}

// Function to simulate the cp command
void cp(const char *source, const char *destination) {
    FILE *src, *dest;
    char ch;

    src = fopen(source, "r");
    if (src == NULL) {
        printf("Error: Cannot open source file.\n");
        return;
    }

    dest = fopen(destination, "w");
    if (dest == NULL) {
        printf("Error: Cannot create destination file.\n");
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    printf("File copied successfully.\n");

    fclose(src);
    fclose(dest);
}

// Function to simulate the wc command
void wc(const char *filename) {
    FILE *file;
    char ch;
    int lines = 0, words = 0, characters = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') {
            words++;
        }
    }

    printf("Number of lines: %d\n", lines);
    printf("Number of words: %d\n", words);
    printf("Number of characters: %d\n", characters);

    fclose(file);
}

int main() {
    int choice;
    char source[100], destination[100], directory[100], filename[100];

    printf("1. ls -l\n");
    printf("2. cp\n");
    printf("3. wc\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter directory path: ");
            scanf("%s", directory);
            ls_l(directory);
            break;
        case 2:
            printf("Enter source file path: ");
            scanf("%s", source);
            printf("Enter destination file path: ");
            scanf("%s", destination);
            cp(source, destination);
            break;
        case 3:
            printf("Enter file path: ");
            scanf("%s", filename);
            wc(filename);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
