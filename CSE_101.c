#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERM_LENGTH 50
#define MAX_DEF_LENGTH 200
#define MAX_SUBFIELD_LENGTH 50
#define MAX_RECORDS 100

// Struct to represent a term record
typedef struct {
    char term[MAX_TERM_LENGTH];
    char definition[MAX_DEF_LENGTH];
    char subfield[MAX_SUBFIELD_LENGTH];
} TermRecord;

// Global variables
TermRecord termRecords[MAX_RECORDS];
int numTerms = 0;

// Function declarations
void addRecord();
void displayAllTerms();
void updateDefinition();
void searchTerm();
void deleteRecord();

// Main function
int main() {
    int choice;

    // Load existing records from file
    FILE *fp = fopen("terms.txt", "r");
    if (fp != NULL) {
        fread(&numTerms, sizeof(int), 1, fp);
        fread(termRecords, sizeof(TermRecord), numTerms, fp);
        fclose(fp);
    }

    // Menu loop
    while (1) {
        // Print menu options
        printf("\nMedical Terminology Dictionary Management\n");
        printf("----------------------------------------\n");
        printf("1. Add record to file\n");
        printf("2. Display all terms in alphabetical order\n");
        printf("3. Update definition\n");
        printf("4. Search for term by name\n");
        printf("5. Delete record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Call corresponding function based on user choice
        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayAllTerms();
                break;
            case 3:
                updateDefinition();
                break;
            case 4:
                searchTerm();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                // Save records to file and exit program
                fp = fopen("terms.txt", "w");
                fwrite(&numTerms, sizeof(int), 1, fp);
                fwrite(termRecords, sizeof(TermRecord), numTerms, fp);
                fclose(fp);
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add a term record to the array
void addRecord() {
    // Check if there is space in the array
    if (numTerms >= MAX_RECORDS) {
        printf("Error: Maximum number of records reached.\n");
        return;
    }

    // Read input from user
    printf("\nEnter the term: ");
    scanf("%s", termRecords[numTerms].term);
    printf("Enter the definition: ");
    scanf(" %[^\n]s", termRecords[numTerms].definition);
    printf("Enter the subfield: ");
    scanf("%s", termRecords[numTerms].subfield);

    // Increment the number of terms
    numTerms++;

    printf("Record added successfully.\n");
}

// Function to display all terms in alphabetical order
void displayAllTerms() {
    int i, j;
    TermRecord temp;

    // Sort the array in alphabetical order by term name
    for (i = 0; i < numTerms - 1; i++) {
        for (j = i + 1; j < numTerms; j++) {
            if (strcmp(termRecords[i].term, termRecords[j].term) > 0) {
                temp = termRecords[i];
            termRecords[i] = termRecords[j];
            termRecords[j] = temp;
        }
    }
}

// Print all terms
printf("\nAll Terms in Alphabetical Order\n");
printf("--------------------------------\n");
for (i = 0; i < numTerms; i++) {
    printf("%s\t(%s): %s\n", termRecords[i].term, termRecords[i].subfield, termRecords[i].definition);
}
}
// Function to update the definition of a term
void updateDefinition() {
char term[MAX_TERM_LENGTH];
int i;

// Read input from user
printf("\nEnter the term to update: ");
scanf("%s", term);

// Find the term in the array
for (i = 0; i < numTerms; i++) {
    if (strcmp(termRecords[i].term, term) == 0) {
        // Update the definition
        printf("Enter the new definition: ");
        scanf(" %[^\n]s", termRecords[i].definition);
        printf("Definition updated successfully.\n");
        return;
    }
}

printf("Term not found. Please try again.\n");
}

// Function to search for a term by name
void searchTerm() {
char term[MAX_TERM_LENGTH];
int i;
// Read input from user
printf("\nEnter the term to search for: ");
scanf("%s", term);

// Find the term in the array
for (i = 0; i < numTerms; i++) {
    if (strcmp(termRecords[i].term, term) == 0) {
        // Print the term and its definition
        printf("\n%s\t(%s): %s\n", termRecords[i].term, termRecords[i].subfield, termRecords[i].definition);
        return;
    }
}

printf("Term not found. Please try again.\n");
}

// Function to delete a term record from the array
void deleteRecord() {
char term[MAX_TERM_LENGTH];
int i, j;
// Read input from user
printf("\nEnter the term to delete: ");
scanf("%s", term);

// Find the term in the array
for (i = 0; i < numTerms; i++) {
    if (strcmp(termRecords[i].term, term) == 0) {
        // Shift all elements after the deleted element one position to the left
        for (j = i + 1; j < numTerms; j++) {
            termRecords[j-1] = termRecords[j];
        }

        // Decrement the number of terms
        numTerms--;

        printf("Record deleted successfully.\n");
        return;
    }
}

printf("Term not found. Please try again.\n");
}
