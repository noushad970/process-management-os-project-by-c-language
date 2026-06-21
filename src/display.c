#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"

// Cross-platform screen clear
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Header
void displayHeader(const char *title) {
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                    %-40s|\n", title);
    printf("+--------------------------------------------------------------+\n");
}

// Separator
void displaySeparator() {
    printf("---------------------------------------------------------------\n");
}

// Menu
void displayMenu() {
    clearScreen();

    printf("\n+==============================================================+\n");
    printf("|                PROCESS MANAGEMENT SYSTEM                     |\n");
    printf("+==============================================================+\n");

    printf("\n");

    printf("[1] Add New Process\n");
    printf("[2] Display All Processes\n");
    printf("[3] FCFS Scheduling\n");
    printf("[4] Shortest Job First (SJF)\n");
    printf("[5] Priority Scheduling\n");
    printf("[6] Round Robin Scheduling\n");
    printf("[7] Delete Process\n");
    printf("[8] Edit Process\n");
    printf("[0] Exit\n");

    printf("\nEnter your choice: ");
}

// Process Table
void displayProcessTable() {
    displayHeader("PROCESS TABLE");

    if (processCount == 0) {
        printf("No processes in the system!\n");
        return;
    }

    printf("%-10s %-20s %-10s %-10s %-10s %-10s\n",
           "PID", "NAME", "ARRIVAL", "BURST", "PRIORITY", "REMAINING");

    displaySeparator();

    for (int i = 0; i < processCount; i++) {
        printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",
               processList[i].pid,
               processList[i].name,
               processList[i].arrivalTime,
               processList[i].burstTime,
               processList[i].priority,
               processList[i].remainingTime);
    }

    displaySeparator();
}

// Gantt Chart
void displayGanttChart(int *ganttOrder, int ganttSize, int *ganttTime, int timeSize) {
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                        GANTT CHART                          |\n");
    printf("+--------------------------------------------------------------+\n");

    printf("\nTime: 0");

    for (int i = 0; i < timeSize; i++) {
        printf(" --> %d", ganttTime[i]);
    }

    printf("\nProcess: ");

    for (int i = 0; i < ganttSize; i++) {
        printf("[P%d] ", ganttOrder[i]);
    }

    printf("\n");
}

// Statistics
void displayStatistics(float avgWaitingTime, float avgTurnaroundTime) {
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                     SCHEDULING STATISTICS                   |\n");
    printf("+--------------------------------------------------------------+\n");

    printf("Average Waiting Time     : %.2f ms\n", avgWaitingTime);
    printf("Average Turnaround Time  : %.2f ms\n", avgTurnaroundTime);

    printf("+--------------------------------------------------------------+\n");
}