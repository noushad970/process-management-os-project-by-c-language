#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "scheduler.h"
#include "display.h"
#include "file_handler.h"

int main() {
    int choice, pid, quantum;
    
    // Load previously saved processes
    loadProcessesFromFile();

    while (1) {
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("%s[ERROR] Invalid input! Please enter a number.%s\n", RED, RESET);
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            addProcess();
            break;

        case 2:
            displayProcesses();
            break;

        case 3:
            fcfs();
            break;

        case 4:
            sjf();
            break;

        case 5:
            priorityScheduling();
            break;

        case 6: {
            system("clear" " || " "cls");
            displayHeader("ROUND ROBIN SCHEDULING");
            printf("%s[*] Enter Time Quantum (in ms): %s", CYAN, RESET);
            if (scanf("%d", &quantum) != 1) {
                clearInputBuffer();
                printf("%s[ERROR] Invalid quantum value!%s\n", RED, RESET);
                break;
            }
            clearInputBuffer();
            roundRobin(quantum);
            break;
        }

        case 7: {
            system("clear" " || " "cls");
            displayHeader("DELETE PROCESS");
            printf("%s[*] Enter Process PID to delete: %s", CYAN, RESET);
            scanf("%d", &pid);
            clearInputBuffer();
            deleteProcess(pid);
            printf("%sPress Enter to continue...%s", YELLOW, RESET);
            getchar();
            break;
        }

        case 8: {
            system("clear || cls");
            displayHeader("EDIT PROCESS");
            printf("%s[*] Enter Process PID to edit: %s", CYAN, RESET);
            scanf("%d", &pid);
            clearInputBuffer();
            editProcess(pid);
            printf("%sPress Enter to continue...%s", YELLOW, RESET);
            getchar();
            break;
        }

        case 0:
            system("clear || cls");
            printf("%s[*] Saving final process states...%s\n", CYAN, RESET);
            saveProcessesToFile();
printf("\n%s+--------------------------------------------------------------+%s\n", BG_BLUE, RESET);
printf("%s|                %sTHANK YOU FOR USING PMS%s                    |%s\n", BG_BLUE, BOLD, RESET, BG_BLUE);
printf("%s+--------------------------------------------------------------+%s\n\n", BG_BLUE, RESET);
            return 0;

        default:
            printf("%s[ERROR] Invalid choice! Please select a valid option.%s\n", RED, RESET);
            printf("%sPress Enter to continue...%s", YELLOW, RESET);
            getchar();
        }
    }

    return 0;
}