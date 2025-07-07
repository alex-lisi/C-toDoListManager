#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void addToFile();
void removeFromFile();
void viewToDoList();
void clearToDoList();

int main() {
    int userChoice;

    while (1) {
        printf("\n(1) Add a task to the to-do list\n");
        printf("(2) Remove a task from the to-do list\n");
        printf("(3) View the to-do list\n");
        printf("(4) Clear the to-do list\n");
        printf("(5) Exit\n");
        printf("\nYour choice (1-5): ");
        scanf("%d", &userChoice);
        getchar(); // consume leftover newline

        if (userChoice == 1) {
            addToFile();
        } else if (userChoice == 2) {
            removeFromFile();
        } else if (userChoice == 3) {
            viewToDoList();
        } else if (userChoice == 4) {
            clearToDoList();
        } else if (userChoice == 5) {
            printf("Exiting. Goodbye!\n");
            break; // exit the loop
        } else {
            printf("Invalid selection.\n");
        }
    }

    return 0;
}

void addToFile() {
    FILE *fp = fopen("data/to-do.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char userInput[200];
    printf("\nAdd to the to-do list:\n");
    fgets(userInput, sizeof(userInput), stdin);
    fprintf(fp, "%s", userInput);
    fclose(fp);

    printf("\nTask added.\n");
}

// Remove a task by line number
void removeFromFile() {
    FILE *fp = fopen("data/to-do.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Read lines into memory
    char lines[100][200]; // up to 100 tasks, each up to 200 chars
    int count = 0;
    while (fgets(lines[count], sizeof(lines[count]), fp)) { // read and ascertain how many lines with "count". each "count" has 200 chars
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("\nThe to-do list is empty.\n");
        return;
    }

    // Show tasks
    printf("\n--- To-Do List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s", i + 1, lines[i]);
    }

    // Ask which line to remove
    int removeIndex;
    printf("\nEnter the number of the task to remove: ");
    scanf("%d", &removeIndex);
    getchar();

    if (removeIndex < 1 || removeIndex > count) {
        printf("Invalid selection.\n");
        return;
    }

    // Write all lines except the removed one to a temp file
    FILE *temp = fopen("data/temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temp file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (i != removeIndex - 1) {
            fputs(lines[i], temp);
        }
    }
    fclose(temp);

    // Replace original file
    remove("data/to-do.txt");
    rename("data/temp.txt", "data/to-do.txt");

    printf("\nTask removed.\n");
}

void viewToDoList() {
    FILE *fp = fopen("data/to-do.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[200];
    int count = 1;
    printf("\n--- To-Do List ---\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%d: %s", count, line);
        count++;
    }
    fclose(fp);
    if (count == 1) {
        printf("The to-do list is empty.\n");
    }
    printf("-------------------\n");
}

void clearToDoList() {
    FILE *fp = fopen("data/to-do.txt", "w");  // Open in write mode to truncate
    if (fp == NULL) {
        printf("Error clearing the to-do list\n");
        return;
    }

    fclose(fp);
    printf("\nTo-do list cleared.\n");
}