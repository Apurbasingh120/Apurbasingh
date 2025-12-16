#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Hospital {
    int slotNo;
    char name[50];
    int age;
    char department[100];
    char date_of_appointment[11];
} patient;

patient arr[20];
int patientCount = 0;
int nextSlotNo = 1;

void displayMenu();
void bookAppointment();
void viewAllAppointments();
void searchPatient();
void deleteAppointment();
void editAppointment();
void printReceipt(int index);
void saveReceiptToFile(int index);
void clearScreen();

int main() {
    int choice;
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║        WELCOME TO CITY HOSPITAL                          ║\n");
    printf("║        Appointment Management System                     ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    while (1) {
        displayMenu();
        printf("👉 Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                bookAppointment();
                break;
            case 2:
                viewAllAppointments();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                deleteAppointment();
                break;
            case 5:
                editAppointment();
                break;
            case 6:
                if (patientCount == 0) {
                    printf("\n⚠️  No appointments to download receipt!\n");
                } else {
                    int id;
                    viewAllAppointments();
                    printf("\nEnter Appointment ID to download receipt: ");
                    scanf("%d", &id);
                    if (id >= 1 && id <= patientCount) {
                        saveReceiptToFile(id - 1);
                    } else {
                        printf("\n❌ Invalid Appointment ID!\n");
                    }
                }
                break;
            case 7:
                printf("\n╔══════════════════════════════════════════════════════════╗\n");
                printf("║                                                          ║\n");
                printf("║    Thank you for using City Hospital System!             ║\n");
                printf("║    We wish you good health! 🏥                            ║\n");
                printf("║                                                          ║\n");
                printf("╚══════════════════════════════════════════════════════════╝\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│   HOSPITAL APPOINTMENT BOOKING SYSTEM│\n");
    printf("├──────────────────────────────────────┤\n");
    printf("│  1. 📅 Book New Appointment          │\n");
    printf("│  2. 📋 View All Appointments         │\n");
    printf("│  3. 🔍 Search Patient                │\n");
    printf("│  4. ❌ Delete Appointment            │\n");
    printf("│  5. ✏️  Edit Appointment              │\n");
    printf("│  6. � Download Receipt              │\n");
    printf("│  7. �🚪 Exit                          │\n");
    printf("└──────────────────────────────────────┘\n");
}

void bookAppointment() {
    if (patientCount >= 20) {
        printf("\n⚠️  Sorry! Maximum appointment limit reached.\n");
        return;
    }
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       📅 BOOK NEW APPOINTMENT        │\n");
    printf("└──────────────────────────────────────┘\n\n");
    
    printf("Enter Patient Name: ");
    scanf(" %[^\n]s", arr[patientCount].name);
    
    printf("Enter Age: ");
    scanf("%d", &arr[patientCount].age);
    
    printf("\nAvailable Departments:\n");
    printf("  • Cardiology\n");
    printf("  • Neurology\n");
    printf("  • Orthopedics\n");
    printf("  • General Medicine\n");
    printf("  • Pediatrics\n");
    printf("  • Dermatology\n");
    printf("\nEnter Department: ");
    scanf(" %[^\n]s", arr[patientCount].department);
    
    printf("Enter Date of Appointment (DD/MM/YYYY): ");
    scanf("%s", arr[patientCount].date_of_appointment);
    
    // Assign slot number
    arr[patientCount].slotNo = nextSlotNo++;
    
    patientCount++;
    printf("\n✅ Appointment booked successfully!\n");
    printf("🎫 Your Slot Number is: %d\n", arr[patientCount - 1].slotNo);
    
    // Print receipt
    printReceipt(patientCount - 1);
    
    // Ask if user wants to download receipt
    char downloadChoice;
    printf("\n💾 Do you want to download the receipt? (y/n): ");
    scanf(" %c", &downloadChoice);
    if (downloadChoice == 'y' || downloadChoice == 'Y') {
        saveReceiptToFile(patientCount - 1);
    }
}

void saveReceiptToFile(int index) {
    char filename[100];
    sprintf(filename, "receipt_slot_%d_%s.txt", arr[index].slotNo, arr[index].name);
    
    // Remove spaces from filename
    for (int i = 0; filename[i]; i++) {
        if (filename[i] == ' ') {
            filename[i] = '_';
        }
    }
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\n❌ Error: Could not create receipt file!\n");
        return;
    }
    
    fprintf(file, "============================================================\n");
    fprintf(file, "                    CITY HOSPITAL                           \n");
    fprintf(file, "               APPOINTMENT RECEIPT                          \n");
    fprintf(file, "============================================================\n");
    fprintf(file, "\n");
    fprintf(file, "  Receipt No : %d\n", index + 1);
    fprintf(file, "  Slot No    : %d\n", arr[index].slotNo);
    fprintf(file, "\n");
    fprintf(file, "============================================================\n");
    fprintf(file, "  PATIENT DETAILS                                           \n");
    fprintf(file, "============================================================\n");
    fprintf(file, "\n");
    fprintf(file, "  Name        : %s\n", arr[index].name);
    fprintf(file, "  Age         : %d\n", arr[index].age);
    fprintf(file, "  Department  : %s\n", arr[index].department);
    fprintf(file, "  Date        : %s\n", arr[index].date_of_appointment);
    fprintf(file, "\n");
    fprintf(file, "============================================================\n");
    fprintf(file, "\n");
    fprintf(file, "  Address : 123 Health Street, Medical City\n");
    fprintf(file, "  Contact : +91-1234567890\n");
    fprintf(file, "  Website : www.cityhospital.com\n");
    fprintf(file, "\n");
    fprintf(file, "============================================================\n");
    fprintf(file, "       Thank you for choosing City Hospital!                \n");
    fprintf(file, "       Please arrive 15 minutes before your                 \n");
    fprintf(file, "       scheduled appointment time.                          \n");
    fprintf(file, "============================================================\n");
    
    fclose(file);
    
    printf("\n✅ Receipt downloaded successfully!\n");
    printf("📁 File saved as: %s\n", filename);
}

void printReceipt(int index) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                    CITY HOSPITAL                         ║\n");
    printf("║               APPOINTMENT RECEIPT                        ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║                                                          ║\n");
    printf("║  Receipt No: %-10d                                  ║\n", index + 1);
    printf("║  Slot No   : %-10d                                  ║\n", arr[index].slotNo);
    printf("║                                                          ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║  PATIENT DETAILS                                         ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║                                                          ║\n");
    printf("║  Name        : %-40s ║\n", arr[index].name);
    printf("║  Age         : %-40d ║\n", arr[index].age);
    printf("║  Department  : %-40s ║\n", arr[index].department);
    printf("║  Date        : %-40s ║\n", arr[index].date_of_appointment);
    printf("║                                                          ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║                                                          ║\n");
    printf("║  📍 Address: 123 Health Street, Medical City             ║\n");
    printf("║  📞 Contact: +91-1234567890                              ║\n");
    printf("║  🌐 Website: www.cityhospital.com                        ║\n");
    printf("║                                                          ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║       Thank you for choosing City Hospital!              ║\n");
    printf("║       Please arrive 15 minutes before your               ║\n");
    printf("║       scheduled appointment time.                        ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
}

void viewAllAppointments() {
    if (patientCount == 0) {
        printf("\n⚠️  No appointments found!\n");
        return;
    }
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       📋 ALL APPOINTMENTS            │\n");
    printf("└──────────────────────────────────────┘\n\n");
    printf("┌──────┬────┬────────────────┬─────┬────────────────┬────────────┐\n");
    printf("│ Slot │ ID │      Name      │ Age │   Department   │    Date    │\n");
    printf("├──────┼────┼────────────────┼─────┼────────────────┼────────────┤\n");
    
    for (int i = 0; i < patientCount; i++) {
        printf("│ %4d │ %2d │ %-14s │ %3d │ %-14s │ %-10s │\n", 
               arr[i].slotNo, i + 1, arr[i].name, arr[i].age, 
               arr[i].department, arr[i].date_of_appointment);
    }
    printf("└──────┴────┴────────────────┴─────┴────────────────┴────────────┘\n");
    printf("📊 Total Appointments: %d\n", patientCount);
}

void searchPatient() {
    if (patientCount == 0) {
        printf("\n⚠️  No appointments to search!\n");
        return;
    }
    
    char searchName[50];
    int found = 0;
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       🔍 SEARCH PATIENT              │\n");
    printf("└──────────────────────────────────────┘\n\n");
    printf("Enter patient name to search: ");
    scanf(" %[^\n]s", searchName);
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       📋 SEARCH RESULTS              │\n");
    printf("└──────────────────────────────────────┘\n");
    
    for (int i = 0; i < patientCount; i++) {
        if (strstr(arr[i].name, searchName) != NULL) {
            printf("\n╭────────────────────────────────╮\n");
            printf("│ Slot No      : %-14d  │\n", arr[i].slotNo);
            printf("│ Appointment ID : %-14d│\n", i + 1);
            printf("├────────────────────────────────┤\n");
            printf("│ Name       : %-17s│\n", arr[i].name);
            printf("│ Age        : %-17d│\n", arr[i].age);
            printf("│ Department : %-17s│\n", arr[i].department);
            printf("│ Date       : %-17s│\n", arr[i].date_of_appointment);
            printf("╰────────────────────────────────╯\n");
            found = 1;
        }
    }
    
    if (!found) {
        printf("\n❌ No patient found with name '%s'\n", searchName);
    }
}

void deleteAppointment() {
    if (patientCount == 0) {
        printf("\n⚠️  No appointments to delete!\n");
        return;
    }
    
    int id;
    char confirm;
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       ❌ DELETE APPOINTMENT          │\n");
    printf("└──────────────────────────────────────┘\n");
    
    viewAllAppointments();
    
    printf("\nEnter Appointment ID to delete: ");
    scanf("%d", &id);
    
    if (id < 1 || id > patientCount) {
        printf("\n❌ Invalid Appointment ID!\n");
        return;
    }
    
    printf("\n⚠️  Are you sure you want to delete appointment for '%s'? (y/n): ", arr[id-1].name);
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        // Shift all elements after the deleted one
        for (int i = id - 1; i < patientCount - 1; i++) {
            arr[i] = arr[i + 1];
        }
        
        patientCount--;
        printf("\n✅ Appointment deleted successfully!\n");
    } else {
        printf("\n❎ Deletion cancelled.\n");
    }
}

void editAppointment() {
    if (patientCount == 0) {
        printf("\n⚠️  No appointments to edit!\n");
        return;
    }
    
    int id, choice;
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       ✏️  EDIT APPOINTMENT            │\n");
    printf("└──────────────────────────────────────┘\n");
    
    viewAllAppointments();
    
    printf("\nEnter Appointment ID to edit: ");
    scanf("%d", &id);
    
    if (id < 1 || id > patientCount) {
        printf("\n❌ Invalid Appointment ID!\n");
        return;
    }
    
    int index = id - 1;
    
    printf("\n┌──────────────────────────────────────┐\n");
    printf("│       What would you like to edit?   │\n");
    printf("├──────────────────────────────────────┤\n");
    printf("│  1. Name                             │\n");
    printf("│  2. Age                              │\n");
    printf("│  3. Department                       │\n");
    printf("│  4. Date of Appointment              │\n");
    printf("│  5. Edit All Details                 │\n");
    printf("│  6. Cancel                           │\n");
    printf("└──────────────────────────────────────┘\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("Enter New Name: ");
            scanf(" %[^\n]s", arr[index].name);
            printf("\n✅ Name updated successfully!\n");
            break;
        case 2:
            printf("Enter New Age: ");
            scanf("%d", &arr[index].age);
            printf("\n✅ Age updated successfully!\n");
            break;
        case 3:
            printf("\nAvailable Departments:\n");
            printf("  • Cardiology\n");
            printf("  • Neurology\n");
            printf("  • Orthopedics\n");
            printf("  • General Medicine\n");
            printf("  • Pediatrics\n");
            printf("  • Dermatology\n");
            printf("\nEnter New Department: ");
            scanf(" %[^\n]s", arr[index].department);
            printf("\n✅ Department updated successfully!\n");
            break;
        case 4:
            printf("Enter New Date (DD/MM/YYYY): ");
            scanf("%s", arr[index].date_of_appointment);
            printf("\n✅ Date updated successfully!\n");
            break;
        case 5:
            printf("\nEnter New Name: ");
            scanf(" %[^\n]s", arr[index].name);
            printf("Enter New Age: ");
            scanf("%d", &arr[index].age);
            printf("\nAvailable Departments:\n");
            printf("  • Cardiology\n");
            printf("  • Neurology\n");
            printf("  • Orthopedics\n");
            printf("  • General Medicine\n");
            printf("  • Pediatrics\n");
            printf("  • Dermatology\n");
            printf("\nEnter New Department: ");
            scanf(" %[^\n]s", arr[index].department);
            printf("Enter New Date (DD/MM/YYYY): ");
            scanf("%s", arr[index].date_of_appointment);
            printf("\n✅ All details updated successfully!\n");
            break;
        case 6:
            printf("\n❎ Edit cancelled.\n");
            return;
        default:
            printf("\n❌ Invalid choice!\n");
            return;
    }
    
    // Print updated receipt
    printf("\n--- Updated Appointment Details ---\n");
    printReceipt(index);
}

