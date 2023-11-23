#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task
struct Task {
    int taskId;
    char description[100];
};

// Function to load tasks from a file
void loadTasksFromFile(struct Task tasks[], int *numTasks) {
    FILE *file = fopen("tasks.txt", "r");

    if (file != NULL) {
        while (fscanf(file, "%d %[^\n]", &tasks[*numTasks].taskId, tasks[*numTasks].description) != EOF) {
            (*numTasks)++;
            if (*numTasks >= 10) {
                break;  // Avoid overflow of tasks array
            }
        }

        fclose(file);
    } else {
        printf("No existing tasks file found.\n");
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nTo-Do List Menu:\n");
    printf("1. Add Task\n");
    printf("2. Display Tasks\n");
    printf("3. Save Tasks to File\n");
    printf("4. Edit Task\n");
    printf("5. Delete Task\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

// Function to add a task
void addTask(struct Task tasks[], int *numTasks) {
    if (*numTasks < 10) {
        printf("Enter task description: ");
        scanf(" %[^\n]s", tasks[*numTasks].description);

        tasks[*numTasks].taskId = (*numTasks) + 1; // Assigning a number to the task
        (*numTasks)++;
        printf("Task added successfully.\n");
    } else {
        printf("Task list is full. Cannot add more tasks.\n");
    }
}

// Function to display tasks
void displayTasks(struct Task tasks[], int numTasks) {
    printf("\nTask List:\n");
    printf("Task ID\tDescription\n");

    for (int i = 0; i < numTasks; i++) {
        printf("%d\t%s\n", tasks[i].taskId, tasks[i].description);
    }
}

// Function to save tasks to a file
void saveTasksToFile(struct Task tasks[], int numTasks) {
    FILE *file = fopen("tasks.txt", "w");

    if (file != NULL) {
        for (int i = 0; i < numTasks; i++) {
            fprintf(file, "%d\t%s\n", tasks[i].taskId, tasks[i].description);
        }

        fclose(file);
        printf("Tasks saved to file successfully.\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

// Function to edit a task
void editTask(struct Task tasks[], int numTasks) {
    int taskIndex;
    displayTasks(tasks, numTasks);

    printf("Enter the ID of the task you want to edit: ");
    scanf("%d", &taskIndex);

    int foundIndex = -1;
    for (int i = 0; i < numTasks; i++) {
        if (tasks[i].taskId == taskIndex) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Enter the new task description: ");
        scanf(" %[^\n]s", tasks[foundIndex].description);

        printf("Task edited successfully.\n");
    } else {
        printf("Invalid task ID.\n");
    }
}

// Function to delete a task
void deleteTask(struct Task tasks[], int *numTasks) {
    int taskIndex;
    displayTasks(tasks, *numTasks);

    printf("Enter the ID of the task you want to delete: ");
    scanf("%d", &taskIndex);

    int foundIndex = -1;
    for (int i = 0; i < *numTasks; i++) {
        if (tasks[i].taskId == taskIndex) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift tasks to remove the selected task
        for (int i = foundIndex; i < *numTasks - 1; i++) {
            tasks[i] = tasks[i + 1];
        }

        (*numTasks)--;
        printf("Task deleted successfully.\n");
    } else {
        printf("Invalid task ID.\n");
    }
}

int main() {
    struct Task tasks[10];
    int numTasks = 0;
    int choice;

    loadTasksFromFile(tasks, &numTasks);

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &numTasks);
                break;
            case 2:
                displayTasks(tasks, numTasks);
                break;
            case 3:
                saveTasksToFile(tasks, numTasks);
                break;
            case 4:
                editTask(tasks, numTasks);
                break;
            case 5:
                deleteTask(tasks, &numTasks);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
