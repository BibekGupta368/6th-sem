#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
    char name[100];
    int roll;
    float cgpa;
    struct Student* next;
};

struct Student* createStudent(char name[], int roll, float cgpa) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->roll = roll;
    newStudent->cgpa = cgpa;
    newStudent->next = NULL;
    return newStudent;
}

void insertStudentSorted(struct Student** head, char name[], int roll, float cgpa) {
    struct Student* newStudent = createStudent(name, roll, cgpa);

    if (*head == NULL || (*head)->cgpa < cgpa) {
        newStudent->next = *head;
        *head = newStudent;
        return;
    }

    struct Student* current = *head;
    while (current->next != NULL && current->next->cgpa >= cgpa) {
        current = current->next;
    }

    newStudent->next = current->next;
    current->next = newStudent;
}

void displayStudents(struct Student* head) {
    struct Student* temp = head;
    printf("Student List sorted according to CGPA):\n");
    while (temp != NULL) {
        printf("Name: %s, Roll: %d, CGPA: %.2f\n", temp->name, temp->roll, temp->cgpa);
        temp = temp->next;
    }
}

int main() {
    struct Student* head = NULL; 


    for (int i = 0; i < 10; i++) {
        char name[100];
        int roll;
        float cgpa;
        
        printf("Enter details for student %d\n", i + 1);
        printf("Name: ");
        scanf("%s", name);
        printf("Roll Number: ");
        scanf("%d", &roll);
        printf("CGPA: ");
        scanf("%f", &cgpa);

        insertStudentSorted(&head, name, roll, cgpa);
    }
    displayStudents(head);

    return 0;
}
