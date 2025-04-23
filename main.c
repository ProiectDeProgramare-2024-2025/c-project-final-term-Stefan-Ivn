#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLUE   "\x1b[34m"
#define GREEN  "\x1b[32m"
#define RED    "\x1b[31m"
#define RESET  "\x1b[0m"

/// STRUCTS
typedef struct {
    char name[100];
    char faculty[100];
    char specialization[100];
} University;

typedef struct {
    char firstName[50];
    char lastName[50];
    int age;
    char highschool[100];
    float baccalaureateGrade;
    University chosen;
} Application;

/// UTILS
void clearScreen() {
    system("cls");
}

void waitForEnter() {
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

int getValidatedAge() {
    int age;
    while (1) {
        printf("Age (15-100): ");
        if (scanf("%d", &age) == 1 && age >= 15 && age <= 100) break;
        printf(RED "Invalid age!\n" RESET);
        while (getchar() != '\n');
    }
    return age;
}

float getValidatedGrade() {
    float grade;
    while (1) {
        printf("Baccalaureate grade (1.00 - 10.00): ");
        if (scanf("%f", &grade) == 1 && grade >= 1.0f && grade <= 10.0f) break;
        printf(RED "Invalid grade!\n" RESET);
        while (getchar() != '\n');
    }
    return grade;
}

/// CORE FUNCTIONALITY
void submitApplication() {
    Application app;
    clearScreen();
    printf("=== Submit Application ===\n");

    printf("First name: ");
    scanf("%s", app.firstName);
    printf("Last name: ");
    scanf("%s", app.lastName);
    app.age = getValidatedAge();
    getchar();

    printf("Highschool name: ");
    fgets(app.highschool, sizeof(app.highschool), stdin);
    strtok(app.highschool, "\n");

    app.baccalaureateGrade = getValidatedGrade();
    getchar();

    printf("University name: ");
    fgets(app.chosen.name, sizeof(app.chosen.name), stdin);
    strtok(app.chosen.name, "\n");

    printf("Faculty name: ");
    fgets(app.chosen.faculty, sizeof(app.chosen.faculty), stdin);
    strtok(app.chosen.faculty, "\n");

    printf("Specialization name: ");
    fgets(app.chosen.specialization, sizeof(app.chosen.specialization), stdin);
    strtok(app.chosen.specialization, "\n");

    FILE *file = fopen("applications.txt", "a");
    if (!file) {
        printf(RED "Error opening file for writing.\n" RESET);
        waitForEnter();
        return;
    }

    fprintf(file, "%s|%s|%d|%s|%.2f|%s|%s|%s\n",
        app.firstName, app.lastName, app.age, app.highschool,
        app.baccalaureateGrade, app.chosen.name, app.chosen.faculty, app.chosen.specialization);
    fclose(file);

    printf(GREEN "\nApplication submitted successfully!\n" RESET);
    waitForEnter();
}

void viewApplications() {
    clearScreen();
    printf("=== Submitted Applications ===\n");
    FILE *file = fopen("applications.txt", "r");
    if (!file) {
        printf(RED "No applications found.\n" RESET);
        waitForEnter();
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        Application app;
        sscanf(line, "%49[^|]|%49[^|]|%d|%99[^|]|%f|%99[^|]|%99[^|]|%99[^\n]",
            app.firstName, app.lastName, &app.age, app.highschool, &app.baccalaureateGrade,
            app.chosen.name, app.chosen.faculty, app.chosen.specialization);

        printf("Name: " BLUE "%s %s" RESET ", Age: %d\n", app.firstName, app.lastName, app.age);
        printf("Highschool: %s | Grade: " GREEN "%.2f" RESET "\n", app.highschool, app.baccalaureateGrade);
        printf("University: " BLUE "%s" RESET " | Faculty: %s | Specialization: %s\n\n",
               app.chosen.name, app.chosen.faculty, app.chosen.specialization);
    }

    fclose(file);
    waitForEnter();
}

/// MENU
void showMainMenu() {
    clearScreen();
    printf("=== University Admission System ===\n");
    printf("1. Submit application\n");
    printf("2. View submitted applications\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int option;
    while (1) {
        showMainMenu();
        scanf("%d", &option);
        switch (option) {
            case 1: submitApplication(); break;
            case 2: viewApplications(); break;
            case 3: clearScreen(); printf("Exiting...\n"); return 0;
            default: printf(RED "Invalid option!\n" RESET); waitForEnter();
        }
    }
    return 0;
}
