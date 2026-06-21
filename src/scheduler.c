#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "scheduler.h"
#include "display.h"

int ganttChart[MAX_PROCESSES * 10];
int ganttTime[MAX_PROCESSES * 10];
int ganttSize = 0;

void swapProcess(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void fcfs() {
    system("clear" " || " "cls");
    displayHeader("FIRST COME FIRST SERVED (FCFS) SCHEDULING");

    if (processCount == 0) {
        printf("%s[!] No processes to schedule!%s\n", YELLOW, RESET);
        return;
    }

    Process temp[MAX_PROCESSES];
    memcpy(temp, processList, sizeof(processList));

    // Sort by arrival time
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = i + 1; j < processCount; j++) {
            if (temp[i].arrivalTime > temp[j].arrivalTime)
                swapProcess(&temp[i], &temp[j]);
        }
    }

    int currentTime = 0;
    ganttSize = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("%s%-10s %-20s %-12s %-15s %-15s %-15s%s\n",
           BOLD, "PID", "NAME", "START", "END", "WAITING", "TURNAROUND", RESET);
    displaySeparator();

    for (int i = 0; i < processCount; i++) {
        if (currentTime < temp[i].arrivalTime)
            currentTime = temp[i].arrivalTime;

        int startTime = currentTime;
        int endTime = currentTime + temp[i].burstTime;
        int waitingTime = startTime - temp[i].arrivalTime;
        int turnaroundTime = endTime - temp[i].arrivalTime;

        temp[i].waitingTime = waitingTime;
        temp[i].turnaroundTime = turnaroundTime;
        temp[i].completionTime = endTime;

        printf("%-10d %-20s %-12d %-15d %-15d %-15d\n",
               temp[i].pid,
               temp[i].name,
               startTime,
               endTime,
               waitingTime,
               turnaroundTime);

        ganttChart[ganttSize] = temp[i].pid;
        ganttTime[ganttSize] = endTime;
        ganttSize++;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        currentTime = endTime;
    }

    displaySeparator();
    printf("%s\n[STATISTICS]%s\n", CYAN, RESET);
    printf("%-50s: %.2f ms\n", "Average Waiting Time", totalWaitingTime / processCount);
    printf("%-50s: %.2f ms\n", "Average Turnaround Time", totalTurnaroundTime / processCount);

    memcpy(processList, temp, sizeof(processList));
    printf("\n%s[SUCCESS] FCFS scheduling completed!%s\n", GREEN, RESET);
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void sjf() {
    system("clear" " || " "cls");
    displayHeader("SHORTEST JOB FIRST (SJF) SCHEDULING");

    if (processCount == 0) {
        printf("%s[!] No processes to schedule!%s\n", YELLOW, RESET);
        return;
    }

    Process temp[MAX_PROCESSES];
    memcpy(temp, processList, sizeof(processList));

    // Sort by burst time
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = i + 1; j < processCount; j++) {
            if (temp[i].burstTime > temp[j].burstTime)
                swapProcess(&temp[i], &temp[j]);
        }
    }

    int currentTime = 0;
    ganttSize = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("%s%-10s %-20s %-12s %-15s %-15s %-15s%s\n",
           BOLD, "PID", "NAME", "START", "END", "WAITING", "TURNAROUND", RESET);
    displaySeparator();

    for (int i = 0; i < processCount; i++) {
        if (currentTime < temp[i].arrivalTime)
            currentTime = temp[i].arrivalTime;

        int startTime = currentTime;
        int endTime = currentTime + temp[i].burstTime;
        int waitingTime = startTime - temp[i].arrivalTime;
        int turnaroundTime = endTime - temp[i].arrivalTime;

        temp[i].waitingTime = waitingTime;
        temp[i].turnaroundTime = turnaroundTime;
        temp[i].completionTime = endTime;

        printf("%-10d %-20s %-12d %-15d %-15d %-15d\n",
               temp[i].pid,
               temp[i].name,
               startTime,
               endTime,
               waitingTime,
               turnaroundTime);

        ganttChart[ganttSize] = temp[i].pid;
        ganttTime[ganttSize] = endTime;
        ganttSize++;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        currentTime = endTime;
    }

    displaySeparator();
    printf("%s\n[STATISTICS]%s\n", CYAN, RESET);
    printf("%-50s: %.2f ms\n", "Average Waiting Time", totalWaitingTime / processCount);
    printf("%-50s: %.2f ms\n", "Average Turnaround Time", totalTurnaroundTime / processCount);

    memcpy(processList, temp, sizeof(processList));
    printf("\n%s[SUCCESS] SJF scheduling completed!%s\n", GREEN, RESET);
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void priorityScheduling() {
    system("clear" " || " "cls");
    displayHeader("PRIORITY SCHEDULING");

    if (processCount == 0) {
        printf("%s[!] No processes to schedule!%s\n", YELLOW, RESET);
        return;
    }

    Process temp[MAX_PROCESSES];
    memcpy(temp, processList, sizeof(processList));

    // Sort by priority (lower value = higher priority)
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = i + 1; j < processCount; j++) {
            if (temp[i].priority > temp[j].priority)
                swapProcess(&temp[i], &temp[j]);
        }
    }

    int currentTime = 0;
    ganttSize = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("%s%-10s %-20s %-12s %-15s %-15s %-15s%s\n",
           BOLD, "PID", "NAME", "START", "END", "WAITING", "TURNAROUND", RESET);
    displaySeparator();

    for (int i = 0; i < processCount; i++) {
        if (currentTime < temp[i].arrivalTime)
            currentTime = temp[i].arrivalTime;

        int startTime = currentTime;
        int endTime = currentTime + temp[i].burstTime;
        int waitingTime = startTime - temp[i].arrivalTime;
        int turnaroundTime = endTime - temp[i].arrivalTime;

        temp[i].waitingTime = waitingTime;
        temp[i].turnaroundTime = turnaroundTime;
        temp[i].completionTime = endTime;

        printf("%-10d %-20s %-12d %-15d %-15d %-15d\n",
               temp[i].pid,
               temp[i].name,
               startTime,
               endTime,
               waitingTime,
               turnaroundTime);

        ganttChart[ganttSize] = temp[i].pid;
        ganttTime[ganttSize] = endTime;
        ganttSize++;

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        currentTime = endTime;
    }

    displaySeparator();
    printf("%s\n[STATISTICS]%s\n", CYAN, RESET);
    printf("%-50s: %.2f ms\n", "Average Waiting Time", totalWaitingTime / processCount);
    printf("%-50s: %.2f ms\n", "Average Turnaround Time", totalTurnaroundTime / processCount);

    memcpy(processList, temp, sizeof(processList));
    printf("\n%s[SUCCESS] Priority scheduling completed!%s\n", GREEN, RESET);
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void roundRobin(int quantum) {
    system("clear" " || " "cls");
    displayHeader("ROUND ROBIN SCHEDULING");

    if (processCount == 0) {
        printf("%s[!] No processes to schedule!%s\n", YELLOW, RESET);
        return;
    }

    if (quantum <= 0) {
        printf("%s[ERROR] Invalid quantum value!%s\n", RED, RESET);
        return;
    }

    Process temp[MAX_PROCESSES];
    memcpy(temp, processList, sizeof(processList));

    int queue[MAX_PROCESSES];
    int queueSize = processCount;
    for (int i = 0; i < processCount; i++) {
        queue[i] = i;
    }

    int currentTime = 0;
    ganttSize = 0;
    int completed = 0;

    printf("%s%-10s %-20s %-12s %-15s %-15s %-15s%s\n",
           BOLD, "PID", "NAME", "START", "END", "WAITING", "TURNAROUND", RESET);
    displaySeparator();

    while (completed < processCount) {
        for (int i = 0; i < queueSize; i++) {
            int idx = queue[i];
            if (temp[idx].remainingTime > 0) {
                int startTime = currentTime;

                if (temp[idx].remainingTime <= quantum) {
                    currentTime += temp[idx].remainingTime;
                    temp[idx].remainingTime = 0;
                    temp[idx].completionTime = currentTime;
                    temp[idx].turnaroundTime = temp[idx].completionTime - temp[idx].arrivalTime;
                    temp[idx].waitingTime = temp[idx].turnaroundTime - temp[idx].burstTime;

                    printf("%-10d %-20s %-12d %-15d %-15d %-15d\n",
                           temp[idx].pid,
                           temp[idx].name,
                           startTime,
                           currentTime,
                           temp[idx].waitingTime,
                           temp[idx].turnaroundTime);

                    completed++;
                } else {
                    currentTime += quantum;
                    temp[idx].remainingTime -= quantum;

                    printf("%-10d %-20s %-12d %-15d %s(PREEMPTED)%s %-15s\n",
                           temp[idx].pid,
                           temp[idx].name,
                           startTime,
                           currentTime,
                           YELLOW, RESET,
                           "---");
                }

                ganttChart[ganttSize] = temp[idx].pid;
                ganttTime[ganttSize] = currentTime;
                ganttSize++;
            }
        }
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < processCount; i++) {
        totalWaitingTime += temp[i].waitingTime;
        totalTurnaroundTime += temp[i].turnaroundTime;
    }

    displaySeparator();
    printf("%s\n[STATISTICS]%s\n", CYAN, RESET);
    printf("%-50s: %.2f ms\n", "Average Waiting Time", totalWaitingTime / processCount);
    printf("%-50s: %.2f ms\n", "Average Turnaround Time", totalTurnaroundTime / processCount);

    memcpy(processList, temp, sizeof(processList));
    printf("\n%s[SUCCESS] Round Robin scheduling completed!%s\n", GREEN, RESET);
    printf("%sPress Enter to continue...%s", YELLOW, RESET);
    getchar();
}

void displaySchedulingResults() {
    if (ganttSize == 0) {
        printf("%s[!] No scheduling results to display!%s\n", YELLOW, RESET);
        return;
    }

    printf("\n%s[GANTT CHART]%s\n", CYAN, RESET);
    displaySeparator();

    printf("Time: 0");
    for (int i = 0; i < ganttSize; i++) {
        printf(" -> %d", ganttTime[i]);
    }
    printf("\nPID:  ");

    for (int i = 0; i < ganttSize; i++) {
        printf("[%d] ", ganttChart[i]);
    }
    printf("\n");
}