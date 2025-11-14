#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define FILE_NAME "records.txt"

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll_no);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Record added successfully.\n");
}

void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }
    Student s;
    printf("\n%-10s %-25s %-10s\n", "Roll No", "Name", "Marks");
    printf("-----------------------------------------------\n");
    while (fread(&s, sizeof(Student), 1, fp))
        printf("%-10d %-25s %-10.2f\n", s.roll_no, s.name, s.marks);
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }
    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);
    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == roll) {
            printf("Record found: %d %s %.2f\n", s.roll_no, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Record not found.\n");
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "wb");
    int roll, found = 0;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);
    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no != roll)
            fwrite(&s, sizeof(Student), 1, temp);
        else
            found = 1;
    }
    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    if (found) printf("Record deleted successfully.\n");
    else printf("Record not found.\n");
}
