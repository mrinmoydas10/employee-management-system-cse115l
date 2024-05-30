#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define MAX_CREDENTIALS_LENGTH 50

typedef struct {
    int id;
    char name[50];
    char position[50];
    char email[50];
    int experience;
    float salary;
    char education[100];
    char phone[15];
} Candidate;

typedef struct {
    char username[MAX_CREDENTIALS_LENGTH];
    char password[MAX_CREDENTIALS_LENGTH];
} Credentials;

void viewRecords(Candidate candidates[], int count) {
    if (count == 0) {
        printf("No information found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID        : %d\n", candidates[i].id);
        printf("Name      : %s\n", candidates[i].name);
        printf("Position  : %s\n", candidates[i].position);
        printf("Email     : %s\n", candidates[i].email);
        printf("Experience: %d years\n", candidates[i].experience);
        printf("Salary    : %.2f\n", candidates[i].salary);
        printf("Education : %s\n", candidates[i].education);
        printf("Phone     : %s\n", candidates[i].phone);
        printf("\n");
    }
}

int isIdUnique(Candidate candidates[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (candidates[i].id == id) {
            return 0; // ID already exists
        }
    }
    return 1; // ID is unique
}

void addRecord(Candidate candidates[], int *count) {
    if (*count >= MAX_RECORDS) {
        printf("Max records reached. Cannot add more candidates.\n");
        return;
    }
    Candidate newCandidate;
    printf("Enter ID          : ");
    scanf("%d", &newCandidate.id);
    if (!isIdUnique(candidates, *count, newCandidate.id)) {
        printf("ID already exists. Please enter a unique ID.\n");
        return;
    }
    printf("Enter name        : ");
    scanf(" %[^\n]%*c", newCandidate.name);
    printf("Enter position    : ");
    scanf(" %[^\n]%*c", newCandidate.position);
    printf("Enter email       : ");
    scanf(" %[^\n]%*c", newCandidate.email);
    printf("Enter experience  : ");
    scanf("%d", &newCandidate.experience);
    printf("Enter salary      : ");
    scanf("%f", &newCandidate.salary);
    printf("Enter education   : ");
    scanf(" %[^\n]%*c", newCandidate.education);
    printf("Enter phone       : ");
    scanf(" %[^\n]%*c", newCandidate.phone);

    candidates[*count] = newCandidate;
    (*count)++;
    printf("Record added successfully!\n");
}

int searchRecord(Candidate candidates[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (candidates[i].id == id) {
            return i;
        }
    }
    return -1;
}

void updateRecord(Candidate candidates[], int count) {
    int id;
    printf("Enter the candidate ID to update: ");
    scanf("%d", &id);
    int index = searchRecord(candidates, count, id);
    if (index != -1) {
        printf("Updating candidate with ID: %d\n", id);
        printf("Enter new name        : ");
        scanf(" %[^\n]%*c", candidates[index].name);
        printf("Enter new position    : ");
        scanf(" %[^\n]%*c", candidates[index].position);
        printf("Enter new email       : ");
        scanf(" %[^\n]%*c", candidates[index].email);
        printf("Enter new experience  : ");
        scanf("%d", &candidates[index].experience);
        printf("Enter new salary      : ");
        scanf("%f", &candidates[index].salary);
        printf("Enter new education   : ");
        scanf(" %[^\n]%*c", candidates[index].education);
        printf("Enter new phone       : ");
        scanf(" %[^\n]%*c", candidates[index].phone);
        printf("Candidate updated successfully!\n");
    } else {
        printf("Candidate with ID %d not found.\n", id);
    }
}

void deleteRecord(Candidate candidates[], int *count) {
    int id;
    printf("Enter the candidate ID to delete: ");
    scanf("%d", &id);
    int index = searchRecord(candidates, *count, id);
    if (index != -1) {
        for (int i = index; i < *count - 1; i++) {
            candidates[i] = candidates[i + 1];
        }
        (*count)--;
        printf("Record with ID %d deleted successfully!\n", id);
    } else {
        printf("Candidate with ID %d not found.\n", id);
    }
}

void saveRecords(Candidate candidates[], int count, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Unable to open file for saving.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(candidates, sizeof(Candidate), count, file);
    fclose(file);
    printf("Records saved to %s successfully.\n", filename);
}

void loadRecords(Candidate candidates[], int *count, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Unable to open file for loading.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(candidates, sizeof(Candidate), *count, file);
    fclose(file);
    printf("Records loaded from %s successfully.\n", filename);
}

void setCredentials(Credentials *creds) {
    printf("Set Username: ");
    scanf(" %[^\n]%*c", creds->username);
    printf("Set Password: ");
    scanf(" %[^\n]%*c", creds->password);
    printf("\nUsername and Password set successfully!\n\n");
}

int login(const Credentials *creds) {
    char username[MAX_CREDENTIALS_LENGTH];
    char password[MAX_CREDENTIALS_LENGTH];

    printf("\nEnter Username: ");
    scanf(" %[^\n]%*c", username);
    printf("Enter Password: ");
    scanf(" %[^\n]%*c", password);

    if (strcmp(creds->username, username) == 0 && strcmp(creds->password, password) == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid username or password.\n");
        return 0;
    }
}

void updateCredentials(Credentials *creds) {
    int choice;
    printf("\n1. Update Username\n");
    printf("2. Update Password\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new username: ");
            scanf(" %[^\n]%*c", creds->username);
            printf("Username updated successfully!\n");
            break;
        case 2:
            printf("Enter new password: ");
            scanf(" %[^\n]%*c", creds->password);
            printf("Password updated successfully!\n");
            break;
        default:
            printf("Invalid choice.\n");
    }
}

int main() {
    Candidate candidates[MAX_RECORDS];
    int count = 0;
    int choice;
    const char *filename = "candidates.dat";
    int loggedIn = 0;

    Credentials creds;
    setCredentials(&creds);

    // Load records at the start of the program
    loadRecords(candidates, &count, filename);

    while (1) {
        printf("\n--- Main Menu ---\n\n");
        printf("1. Employee Management \n");
        printf("2. Update Username or Password\n");
        printf("3. Exit\n\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (!loggedIn) {
                    loggedIn = login(&creds);
                }
                if (loggedIn) {
                    while (1) {
                        printf("\n--- Welcome to Employee Management System ---\n\n");
                        printf("1. View Records\n");
                        printf("2. Add Record\n");
                        printf("3. Search Record\n");
                        printf("4. Update Record\n");
                        printf("5. Delete Record\n");
                        printf("6. Save Records\n");
                        printf("7. Load Records\n");
                        printf("8. Logout\n");
                        printf("\nEnter your choice: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1:
                                viewRecords(candidates, count);
                                break;
                            case 2:
                                addRecord(candidates, &count);
                                break;
                            case 3: {
                                int id;
                                printf("Enter candidate ID to search: ");
                                scanf("%d", &id);
                                int index = searchRecord(candidates, count, id);
                                if (index != -1) {
                                    printf("Candidate found:\n");
                                    printf("\nID        : %d\n", candidates[index].id);
                                    printf("Name      : %s\n", candidates[index].name);
                                    printf("Position  : %s\n", candidates[index].position);
                                    printf("Email     : %s\n", candidates[index].email);
                                    printf("Experience: %d years\n", candidates[index].experience);
                                    printf("Salary    : %.2f\n", candidates[index].salary);
                                    printf("Education : %s\n", candidates[index].education);
                                    printf("Phone     : %s\n", candidates[index].phone);
                                } else {
                                    printf("Candidate with ID %d not found.\n", id);
                                }
                                break;
                            }
                            case 4:
                                updateRecord(candidates, count);
                                break;
                            case 5:
                                deleteRecord(candidates, &count);
                                break;
                            case 6:
                                saveRecords(candidates, count, filename);
                                break;
                            case 7:
                                loadRecords(candidates, &count, filename);
                                break;
                            case 8:
                                printf("Logging out...\n");
                                loggedIn = 0;
                                goto main_menu;
                            default:
                                printf("Invalid choice. Please try again.\n");
                        }
                    }
                }
                break;
            case 2:
                updateCredentials(&creds);
                break;
            case 3:
                saveRecords(candidates, count, filename);
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

main_menu:
    return 0;
}
