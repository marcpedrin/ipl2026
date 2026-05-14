/*The advantage of storing array of structures as binary files is that we can use fseek to go to specific record and get the record.
Write a program to store n records in binary file.
Write a function to get mth record and display.
Use fseek
Write a function to delete a record.
Deleting a record requires thinking.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "players.dat"

typedef struct Record{
    char name[100];
    int roll;
    int sem;
}Record;

int main(){
    int n;
    print("Enter number of student records");
    scanf("%d",&n);
}

void create(int n){

}

bool seek(Record *arr, int n){

}

bool delete(Record *arr, int n){

}
