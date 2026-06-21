#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "file_handler.h"

#define DATA_FILE "data/processes.txt"

// SAVE TO FILE
void saveProcessesToFile() {
    FILE *file = fopen(DATA_FILE, "w");

    if (file == NULL) {
        printf("%s[ERROR] Cannot open file for writing!%s\n", RED, RESET);
        return;
    }

    fprintf(file, "%d\n", processCount);

    for (int i = 0; i < processCount; i++) {

        char tempName[MAX_NAME_LEN];
        strcpy(tempName, processList[i].name);

        // Replace spaces with underscores
        for (int j = 0; tempName[j] != '\0'; j++) {
            if (tempName[j] == ' ') {
                tempName[j] = '_';
            }
        }

        fprintf(file, "%d %s %d %d %d\n",
                processList[i].pid,
                tempName,
                processList[i].arrivalTime,
                processList[i].burstTime,
                processList[i].priority);
    }

    fclose(file);

    printf("%s[SUCCESS] Processes saved successfully!%s\n", GREEN, RESET);
}

// LOAD FROM FILE
void loadProcessesFromFile() {
    FILE *file = fopen(DATA_FILE, "r");

    if (file == NULL) {
        printf("%s[INFO] No saved file found.%s\n", YELLOW, RESET);
        return;
    }

    if (fscanf(file, "%d", &processCount) != 1) {
        processCount = 0;
        fclose(file);
        return;
    }

    for (int i = 0; i < processCount; i++) {

        char tempName[MAX_NAME_LEN];

        if (fscanf(file, "%d %s %d %d %d",
                   &processList[i].pid,
                   tempName,
                   &processList[i].arrivalTime,
                   &processList[i].burstTime,
                   &processList[i].priority) == 5) {

            // Replace underscores back to spaces
            for (int j = 0; tempName[j] != '\0'; j++) {
                if (tempName[j] == '_') {
                    tempName[j] = ' ';
                }
            }

            strcpy(processList[i].name, tempName);

            processList[i].remainingTime = processList[i].burstTime;
            processList[i].state = READY;
        }
    }

    fclose(file);

    printf("%s[SUCCESS] Processes loaded successfully! (Count: %d)%s\n",
           GREEN, processCount, RESET);
}