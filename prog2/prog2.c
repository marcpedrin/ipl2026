/*Write a program that stores array of structures in ascii format in a file.
Write a function to create an array of seek positions of the beginning of the
each record(structure) in the file Write a function to display the record given
the position.*/
#include <stdio.h>
#include <stdlib.h>

#define FILENAME "players.txt"
#define MAX_RECORDS 50

typedef struct {
  char name[100];
  int roll;
  int sem;
} Record;

// Function to create the file with 'n' records
void create(Record records[], int n) {
  FILE *fp = fopen(FILENAME, "w");
  if (fp == NULL) {
    perror("Error opening file for writing");
    return;
  }

  for (int i = 0; i < n; i++) {
    // Write to file in ASCII format
    fprintf(fp, "%s %d %d\n", records[i].name, records[i].roll, records[i].sem);
  }

  fclose(fp);
  printf("\nFile '%s' created successfully with %d records.\n", FILENAME, n);
}

// Function to create an array of seek positions
int create_seek_positions(long int positions[]) {
  FILE *fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    perror("Error opening file for reading");
    return 0;
  }

  int count = 0;
  char line[200];

  while (count < MAX_RECORDS) {
    // Store position BEFORE reading the line
    positions[count] = ftell(fp);
    if (fgets(line, sizeof(line), fp) == NULL) break;
    // Skip blank lines
    if (line[0] == '\n' || line[0] == '\0') continue;
    count++;
  }

  fclose(fp);
  return count; // Return number of records
}

// Function to display the record given the position
void display_record(long int position) {
  FILE *fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    perror("Error opening file");
    return;
  }

  // Move to the specified position
  if (fseek(fp, position, SEEK_SET) != 0) {
    printf("Error moving to position %ld\n", position);
    fclose(fp);
    return;
  }

  Record p;
  // Read the record
  if (fscanf(fp, "%s %d %d", p.name, &p.roll, &p.sem) == 3) {
    printf("\n--- Record at position %ld ---\n", position);
    printf("Name: %s\n", p.name);
    printf("Roll No: %d\n", p.roll);
    printf("Semester: %d\n", p.sem);
  } else {
    printf("No record found at position %ld\n", position);
  }

  fclose(fp);
}

int main() {
  int n;
  printf("Enter number of student records: ");
  if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_RECORDS) {
    printf("Invalid number of records.\n");
    return 1;
  }

  Record records[MAX_RECORDS];

  // Input records
  printf("Enter %d student records:\n", n);
  for (int i = 0; i < n; i++) {
    printf("\n--- Record %d ---\n", i + 1);
    printf("Enter Name: ");
    scanf("%s", records[i].name);
    printf("Enter Roll No: ");
    scanf("%d", &records[i].roll);
    printf("Enter Semester: ");
    scanf("%d", &records[i].sem);
  }

  // Create the file with records
  create(records, n);

  // Create array of seek positions
  long int seek_positions[MAX_RECORDS + 1];
  int num_records = create_seek_positions(seek_positions);

  printf("\nSeek positions created for %d records.\n", num_records);

  // Display all records using seek positions
  printf("\nDisplaying all records:\n");
  for (int i = 0; i < num_records; i++) {
    display_record(seek_positions[i]);
  }

  // Example: Display a specific record
  int record_to_display;
  printf("\nDo you want to display a specific record? (1 for yes, 0 for no): ");
  scanf("%d", &record_to_display);

  if (record_to_display == 1) {
    int index;
    printf("Enter the record number to display (1-%d): ", num_records);
    scanf("%d", &index);

    if (index >= 1 && index <= num_records) {
      display_record(seek_positions[index - 1]);
    } else {
      printf("Invalid record number.\n");
    }
  }

  return 0;
}