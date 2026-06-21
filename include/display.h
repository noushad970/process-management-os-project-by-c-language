#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

void displayMenu();
void displayHeader(const char *title);
void displaySeparator();
void displayProcessTable();
void displayGanttChart(int *ganttOrder, int ganttSize, int *ganttTime, int timeSize);
void displayStatistics(float avgWaitingTime, float avgTurnaroundTime);
void clearScreen();

#endif
