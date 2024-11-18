#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int is_used;
} File;

File directory[MAX_FILES];

void initialize_directory() {
    for (int i = 0; i < MAX_FILES; i++) {
        directory[i].is_used = 0;
    }
}

void create_file(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].is_used && strcmp(directory[i].name, name) == 0) {
            printf("File %s already exists.\n", name);
            return;
        }
    }
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (!directory[i].is_used) {
            strcpy(directory[i].name, name);
            directory[i].is_used = 1;
            printf("File %s created.\n", name);
            return;
        }
    }
    printf("Directory is full. Cannot create more files.\n");
}

void delete_file(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].is_used && strcmp(directory[i].name, name) == 0) {
            directory[i].is_used = 0;
            printf("File %s deleted.\n", name);
            return;
        }
    }
    printf("File %s not found.\n", name);
}

void list_files() {
    printf("Files in directory:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (directory[i].is_used) {
            printf("%s\n", directory[i].name);
        }
    }
}

int main() {
    initialize_directory();
    
    int choice;
    char filename[MAX_FILENAME_LENGTH];
    
    while (1) {
        printf("\nSingle-Level Directory System\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter filename to create: ");
                scanf("%s", filename);
                create_file(filename);
                break;
            case 2:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                delete_file(filename);
                break;
            case 3:
                list_files();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
