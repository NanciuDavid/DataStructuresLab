#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 256

typedef struct Project {
    char *title;
    char *owner;
    unsigned char numExecutants;
    float budget;
} Project;

typedef struct dlNode {
    Project *project;
    struct dlNode *next;
    struct dlNode *prev;
} dlNode;

// Function to print project details
void printProject(Project *project) {
    printf("\nThe project is entitled %s, its owner is %s, it has %d participants, and a budget of %.1f\n",
    project->title, project->owner, project->numExecutants, project->budget);
}

// Function to increase project budget based on threshold and percentage
void increaseProjectBudget(dlNode *head, unsigned char threshold, float percentage) {
    dlNode *temp = head;
    while (temp) {
        if (temp->project->numExecutants > threshold) {
            temp->project->budget += temp->project->budget * (percentage / 100.0);
        }
        temp = temp->next;
    }
}

// Function to create a new project
Project *createProject(const char *title, const char *owner, unsigned char numExecutants, float budget) {
    Project *project = (Project *)malloc(sizeof(Project));
    project->title = strdup(title);
    project->owner = strdup(owner);
    project->numExecutants = numExecutants;
    project->budget = budget;

    return project;
}

// Function to free memory allocated for a project
void freeProject(Project *project) {
    if (project) {
        free(project->owner);
        free(project->title);
        free(project);
    } else {
        printf("Error: Attempt to free NULL project pointer\n");
    }
}

// Function to create a new node for the double linked list
dlNode *createNode(Project *project) {
    dlNode *node = (dlNode *)malloc(sizeof(dlNode));
    node->project = project;
    node->next = node->prev = NULL;
    return node;
}

// Function to insert a node into the double linked list
dlNode *insertNode(dlNode *head, Project *project) {
    dlNode *node = createNode(project);
    if (head == NULL) {
        return node;
    } else {
        dlNode *tmp = head;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = node;
        node->prev = tmp;
        return head;
    }
}

// Function to calculate the total number of executants for projects owned by a specific owner
unsigned char totalExecutantsByKey(dlNode *head, const char *name) {
    dlNode *tmp = head;
    unsigned char count = 0;
    while (tmp) {
        printf("Checking project owned by: %s\n", tmp->project->owner);
        if (strcmp(tmp->project->owner, name) == 0) {
            printf("Owner matches!\n");
            count += tmp->project->numExecutants;
        }
        tmp = tmp->next;
    }
    return count;
}

// Function to display the list of projects
void displayList(dlNode *head) {
    dlNode *tmp = head;
    while (tmp) {
        printProject(tmp->project);
        tmp = tmp->next;
    }
}

// Function to delete the entire double linked list and free memory
void deleteList(dlNode **head) {
    dlNode *tmp = *head;
    while (tmp) {
        dlNode *nextNode = tmp->next;
        freeProject(tmp->project);
        free(tmp);
        tmp = nextNode;
    }
    *head = NULL;
}

// Function to create and return an array of project titles for projects having budget over a threshold
char **getProjectTitlesOverThreshold(dlNode *head, float threshold) {
    dlNode *tmp = head;
    int count = 0;

    // Count the number of projects with a budget over the threshold
    while (tmp) {
        if (tmp->project->budget > threshold) {
            count++;
        }
        tmp = tmp->next;
    }

    // Allocate memory for the array of project titles
    char **titles = (char **)malloc((count + 1) * sizeof(char *)); // Add one for the NULL terminator

    // Initialize all elements to NULL
    for (int i = 0; i < count + 1; i++) {
        titles[i] = NULL;
    }

    // Traverse the list again to extract titles for projects with budget over threshold
    tmp = head;
    int index = 0;
    while (tmp) {
        if (tmp->project->budget > threshold) {
            // Allocate memory for the title and copy it
            titles[index] = (char*)malloc(strlen(tmp->project->title) + 1);
            if (titles[index] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");

                // Free previously allocated memory before exiting
                for (int i = 0; i < index; i++) {
                    free(titles[i]);
                }
                free(titles);
                exit(EXIT_FAILURE);
            }
            strcpy(titles[index], tmp->project->title);
            index++;
        }
        tmp = tmp->next;
    }
    return titles;
}

// Main function
int main(void) {
    dlNode *head = NULL;
    FILE *fileInput = fopen("Data.txt", "r");

    if (fileInput) {
        char buffer[BUFFER_SIZE];
        char *token;
        while (fgets(buffer, sizeof(buffer), fileInput)) {
            // Tokenizing the buffer string
            token = strtok(buffer, ",");
            char* projectTitle = (char*)malloc(strlen(token) + 1);
            strcpy(projectTitle, token);

            token = strtok(NULL, ","); // Passing NULL to strtok continues from the previous string
            char *projectOwner = (char*)malloc(strlen(token) + 1);
            strcpy(projectOwner, token);

            token = strtok(NULL, ",");
            unsigned char projectNumExecutants = atoi(token);

            token  = strtok(NULL, ",");
            float projectBudget = atof(token);

            Project *project = createProject(projectTitle, projectOwner, projectNumExecutants, projectBudget);
            head = insertNode(head, project);
        }
        fclose(fileInput); // Close the file after reading
    } else {
        printf("File not opened");
        exit(EXIT_FAILURE);
    }    

    // Calculate the total number of participants of projects owned by "DAVID"
    unsigned char totalPart = totalExecutantsByKey(head, "DAVID");
    printf("\nTotal participants of projects owned by DAVID: %d\n", totalPart);

    // Display the list of projects
    displayList(head);

    // Increase project budgets by 30% if they have more than 2 participants
    increaseProjectBudget(head, 2, 30);

    // Display the updated list of projects
    displayList(head);

    // Get project titles with budget over 2000.0
    char **array = getProjectTitlesOverThreshold(head, 2000.0);
    if (array != NULL) {
        for (int i = 0; array[i] != NULL; i++) {
            printf("\n%s", array[i]);
        }

        // Free memory allocated for the array of project titles
        for (int i = 0; array[i] != NULL; i++) {
            free(array[i]);
        }
        free(array);
    }

    // Free memory allocated for the list of projects
    deleteList(&head);
    return 0;
}
