#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "display.h"
#include "file_handler.h"

Process processList[MAX_PROCESSES];
int processCount = 0;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void addProcess() {
    if (processCount >= MAX_PROCESSES) {
        printf("%s[ERROR] Maximum process limit reached!%s\n", RED, RESET);
        return;
    }

    system("clear || cls");
    displayHeader("ADD NEW PROCESS");

    Process p;
    p.pid = (processCount > 0) ? processList[processCount - 1].pid + 1 : 1001;
    p.state = NEW;

    printf("%s[*]%s Enter Process Name: ", CYAN, RESET);
    // Use a loop to ensure name is not empty
    while (fgets(p.name, MAX_NAME_LEN, stdin) && (p.name[0] == '\n' || p.name[0] == '\0')) {
        printf("%s[!] Process name cannot be empty. Please try again: %s", YELLOW, RESET);
    }
    p.name[strcspn(p.name, "\n")] = '\0';


    printf("%s[*]%s Arrival Time (in ms): ", CYAN, RESET);
    while (scanf("%d", &p.arrivalTime) != 1) {
        printf("%s[!] Invalid input. Please enter a number: %s", YELLOW, RESET);
        clearInputBuffer();
    }


    printf("%s[*]%s Burst Time (in ms): ", CYAN, RESET);
    while (scanf("%d", &p.burstTime) != 1 || p.burstTime <= 0) {
        printf("%s[!] Invalid input. Burst time must be > 0: %s", YELLOW, RESET);
        clearInputBuffer();
    }

    printf("%s[*]%s Priority (1=High, 5=Low): ", CYAN, RESET);
    while (scanf("%d", &p.priority) != 1) {
        printf("%s[!] Invalid input. Please enter a number: %s", YELLOW, RESET);
        clearInputBuffer();
    }
    clearInputBuffer();

    p.remainingTime = p.burstTime;
    p.waitingTime = 0;
    p.turnaroundTime = 0;
    p.completionTime = 0;

    processList[processCount] = p;
    processCount++;

    printf("\n%s[SUCCESS]%s Process PID: %d added successfully!%s\n", GREEN, BOLD, p.pid, RESET);
    saveProcessesToFile(); // Auto-save after adding
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void displayProcesses() {
    system("clear || cls");
    displayHeader("PROCESS LIST");

    if (processCount == 0) {
        printf("%s[!] No processes added yet!%s\n", YELLOW, RESET);
        printf("%sPress Enter to continue...%s", YELLOW, RESET);
        getchar();
        return;
    }

    printf("%s%-10s %-20s %-15s %-15s %-12s %-12s %-15s%s\n",
           BOLD, "PID", "NAME", "ARRIVAL (ms)", "BURST (ms)", "PRIORITY", "STATE", "REMAINING (ms)", RESET);
    displaySeparator();

    const char *states[] = {"NEW", "READY", "RUNNING", "WAITING", "TERMINATED"};

    for (int i = 0; i < processCount; i++) {
        printf("%-10d %-20s %-15d %-15d %-12d %-12s %-15d\n",
               processList[i].pid,
               processList[i].name,
               processList[i].arrivalTime,
               processList[i].burstTime,
               processList[i].priority,
               states[processList[i].state],
               processList[i].remainingTime);
    }

    displaySeparator();
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void deleteProcess(int pid) {
    int found = -1;
    for (int i = 0; i < processCount; i++) {
        if (processList[i].pid == pid) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("%s[ERROR] Process with PID %d not found!%s\n", RED, pid, RESET);
        return;
    }

    for (int i = found; i < processCount - 1; i++) {
        processList[i] = processList[i + 1];
    }

    processCount--;
    printf("%s[SUCCESS] Process with PID %d deleted successfully!%s\n", GREEN, pid, RESET);
    saveProcessesToFile(); // Auto-save after deleting
}

void editProcess(int pid) {
    int found = -1;
    for (int i = 0; i < processCount; i++) {
        if (processList[i].pid == pid) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("%s[ERROR] Process with PID %d not found!%s\n", RED, pid, RESET);
        return;
    }

    system("clear || cls");
    displayHeader("EDIT PROCESS");

    Process *p = &processList[found];
    char buffer[MAX_NAME_LEN];
    int new_val;

    printf("Editing Process PID: %d (Name: %s)\n", p->pid, p->name);
    printf("Press Enter to keep the current value.\n\n");

    // Edit Name
    printf("%s[*]%s Current Name: %s. New Name: ", CYAN, RESET, p->name);
    fgets(buffer, MAX_NAME_LEN, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(p->name, buffer);
    }

    // Edit Arrival Time
    printf("%s[*]%s Current Arrival Time: %d. New Arrival Time: ", CYAN, RESET, p->arrivalTime);
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &new_val) == 1) {
        p->arrivalTime = new_val;
    }

    // Edit Burst Time
    printf("%s[*]%s Current Burst Time: %d. New Burst Time: ", CYAN, RESET, p->burstTime);
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &new_val) == 1 && new_val > 0) {
        p->burstTime = new_val;
        p->remainingTime = new_val; // Reset remaining time
    } else if (buffer[0] != '\n') {
        printf("%s[!] Invalid burst time. Must be > 0. Keeping old value.%s\n", YELLOW, RESET);
    }

    // Edit Priority
    printf("%s[*]%s Current Priority: %d. New Priority: ", CYAN, RESET, p->priority);
    fgets(buffer, sizeof(buffer), stdin);
    if (sscanf(buffer, "%d", &new_val) == 1) {
        p->priority = new_val;
    }

    printf("\n%s[SUCCESS]%s Process PID: %d updated successfully!%s\n", GREEN, BOLD, p->pid, RESET);
    saveProcessesToFile(); // Auto-save after editing
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void displayProcessStats() {
    if (processCount == 0) {
        printf("%s[!] No processes to display statistics!%s\n", YELLOW, RESET);
        return;
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (int i = 0; i < processCount; i++) {
        totalWaitingTime += processList[i].waitingTime;
        totalTurnaroundTime += processList[i].turnaroundTime;
    }

    float avgWaitingTime = totalWaitingTime / processCount;
    float avgTurnaroundTime = totalTurnaroundTime / processCount;

    printf("%s%-50s%s %.2f ms\n", BOLD, "Average Waiting Time:", RESET, avgWaitingTime);
    printf("%s%-50s%s %.2f ms\n", BOLD, "Average Turnaround Time:", RESET, avgTurnaroundTime);
}