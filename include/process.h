#ifndef PROCESS_H
#define PROCESS_H

#include <time.h>

#define MAX_PROCESSES 100
#define MAX_NAME_LEN 50

// Process States
#define NEW 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define TERMINATED 4

// Color codes for terminal output
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BG_BLUE "\x1b[44m"
#define BG_BLACK "\x1b[40m"

typedef struct {
    int pid;
    char name[MAX_NAME_LEN];
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int state;
} Process;

// Global process list
extern Process processList[MAX_PROCESSES];
extern int processCount;

// Function declarations
void addProcess();
void displayProcesses();
void deleteProcess(int pid);
void editProcess(int pid);
void clearInputBuffer();
void displayProcessStats();
void saveProcessesToFile();

#endif