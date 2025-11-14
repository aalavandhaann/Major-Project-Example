#ifndef STUDENT_H
#define STUDENT_H

typedef struct {
    int roll_no;
    char name[50];
    float marks;
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();

#endif
