/*The advantage of storing array of structures as binary files is that we can
use fseek to go to specific record and get the record. Write a program to store
n records in binary file. Write a function to get mth record and display. Use
fseek Write a function to delete a record. Deleting a record requires
thinking.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "players.dat"

typedef struct Record {
    char name[100];
    int roll;
    int sem;
} Record;

/* --- Create: write n records to the binary file --- */
void create(int n) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    Record r;
    for (int i = 0; i < n; i++) {
        printf("\n--- Record %d ---\n", i + 1);
        printf("Name: ");
        scanf("%s", r.name);
        printf("Roll: ");
        scanf("%d", &r.roll);
        printf("Sem:  ");
        scanf("%d", &r.sem);
        fwrite(&r, sizeof(Record), 1, fp);
    }

    fclose(fp);
    printf("\n%d record(s) saved to %s.\n", n, FILENAME);
}

/* --- Seek: fetch and display the mth record using fseek --- */
int seek(int m) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    /* Jump directly to the (m-1)th record; no need to loop */
    if (fseek(fp, (long)(m - 1) * sizeof(Record), SEEK_SET) != 0) {
        printf("fseek failed.\n");
        fclose(fp);
        return 0;
    }

    Record r;
    if (fread(&r, sizeof(Record), 1, fp) == 1) {
        printf("\nRecord %d: Name=%-15s  Roll=%-5d  Sem=%d\n",
               m, r.name, r.roll, r.sem);
        fclose(fp);
        return 1;
    }

    printf("Record %d not found.\n", m);
    fclose(fp);
    return 0;
}

/* --- Delete: remove the mth record by rewriting the file without it --- */
int delete(int m) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    FILE *tmp = fopen("tmp_players.dat", "wb");
    if (tmp == NULL) {
        perror("Error creating temp file");
        fclose(fp);
        return 0;
    }

    Record r;
    int idx = 1, deleted = 0;

    while (fread(&r, sizeof(Record), 1, fp) == 1) {
        if (idx == m) {
            deleted = 1;   /* skip this record */
        } else {
            fwrite(&r, sizeof(Record), 1, tmp);
        }
        idx++;
    }

    fclose(fp);
    fclose(tmp);

    if (deleted) {
        remove(FILENAME);
        rename("tmp_players.dat", FILENAME);
        printf("Record %d deleted successfully.\n", m);
    } else {
        remove("tmp_players.dat");
        printf("Record %d not found (file has only %d record(s)).\n", m, idx - 1);
    }

    return deleted;
}

/* --- Main menu --- */
int main() {
    int choice, n, m;

    while (1) {
        printf("\n===== Binary File Records =====\n");
        printf("1. Create N records\n");
        printf("2. Get Mth record\n");
        printf("3. Delete Mth record\n");
        printf("4. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter number of records: ");
                scanf("%d", &n);
                create(n);
                break;
            case 2:
                printf("Enter record number to fetch: ");
                scanf("%d", &m);
                seek(m);
                break;
            case 3:
                printf("Enter record number to delete: ");
                scanf("%d", &m);
                delete(m);
                break;
            case 4:
                printf("Goodbye.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}