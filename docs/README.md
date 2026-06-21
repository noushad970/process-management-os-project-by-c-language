# Process Management System (PMS) v2.0

A comprehensive **CPU Process Scheduling Simulator** written in C with a modern terminal UI, implementing multiple scheduling algorithms used in Operating Systems.

---

## 📋 Features

### Core Functionality
- ✅ **Add/Remove/Edit Processes** - Dynamic process management
- ✅ **FCFS Scheduling** - First Come First Served algorithm
- ✅ **SJF Scheduling** - Shortest Job First algorithm
- ✅ **Priority Scheduling** - Priority-based process execution
- ✅ **Round Robin Scheduling** - Time quantum-based scheduling
- ✅ **Process Statistics** - Real-time metrics and analysis
- ✅ **Gantt Chart Visualization** - Visual process timeline
- ✅ **Data Persistence** - Save/Load processes from files
- ✅ **Color-Coded Terminal UI** - Beautiful and intuitive interface

### Advanced Features
- Process state management (NEW, READY, RUNNING, WAITING, TERMINATED)
- Waiting time and turnaround time calculations
- Average metrics computation
- Queue-based process management
- Input validation and error handling

---

## 🏗️ Project Structure

```
ProcessManagement/
├── main.c                    # Main entry point with menu system
├── Makefile                  # Build configuration
├── bin/                      # Compiled executable
├── build/                    # Build artifacts
├── data/
│   └── processes.txt        # Persistent process data
├── docs/
│   └── README.md            # This file
├── include/                 # Header files
│   ├── process.h            # Process structure & functions
│   ├── scheduler.h          # Scheduling algorithms
│   ├── display.h            # UI display functions
│   ├── queue.h              # Queue data structure
│   └── file_handler.h       # File I/O operations
└── src/                     # Implementation files
    ├── process.c            # Process management logic
    ├── scheduler.c          # Scheduling algorithms
    ├── display.c            # Terminal UI rendering
    ├── queue.c              # Queue implementation
    └── file_handler.c       # File persistence
```

---

## 🚀 Getting Started

### Prerequisites
- GCC compiler (or any C compiler)
- Linux/Windows with bash/PowerShell
- Basic understanding of process scheduling concepts

### Build Instructions

#### On Linux/Mac:
```bash
cd ProcessManagement
make clean
make all
make run
```

#### On Windows (PowerShell):
```powershell
cd ProcessManagement
gcc -Wall -Wextra -std=c99 -Iinclude -o bin/process_manager.exe `
    main.c src/process.c src/scheduler.c src/display.c src/queue.c src/file_handler.c
./bin/process_manager.exe
```

#### Using Make on Windows:
```bash
make all
make run
```

---

## 📊 Usage Guide

### Main Menu Options

**1. Add New Process**
- Enter process name, arrival time, burst time, and priority
- Automatic PID assignment (starting from 1001)
- Processes are auto-saved to file

**2. Display All Processes**
- View all added processes in table format
- Shows: PID, Name, Arrival Time, Burst Time, Priority, State, Remaining Time

**3. FCFS Scheduling**
- Executes processes in order of arrival
- Displays scheduling table with waiting and turnaround times
- Calculates average metrics

**4. SJF Scheduling**
- Executes shortest jobs first
- Optimal for minimizing average waiting time
- Shows process execution order

**5. Priority Scheduling**
- Executes processes based on priority (1=Highest, 5=Lowest)
- Non-preemptive scheduling
- Displays priority-based execution order

**6. Round Robin Scheduling**
- Time-quantum based scheduling
- Each process gets equal CPU time slice
- Preemption handling with time quantum

**7. Delete Process**
- Remove a process by its PID
- Auto-saves changes

**8. Edit Process**
- Modify process parameters
- Updates arrival time, burst time, or priority

**0. Exit**
- Saves all processes and exits

---

## 📈 Scheduling Algorithms Explained

### FCFS (First Come First Served)
- Simplest scheduling algorithm
- Non-preemptive
- Processes execute in arrival order
- **Pros:** Simple, fair
- **Cons:** High average waiting time, convoy effect

### SJF (Shortest Job First)
- Prioritizes processes with smallest burst time
- Can be preemptive or non-preemptive
- **Pros:** Minimum average waiting time
- **Cons:** Starvation risk for long jobs

### Priority Scheduling
- Each process has a priority level
- Lower priority values = Higher priority
- **Pros:** Flexible, can prioritize important tasks
- **Cons:** Risk of starvation for low-priority processes

### Round Robin
- Time-sharing approach with fixed time quantum
- Each process gets equal CPU time slice
- **Pros:** Fair, prevents starvation
- **Cons:** Higher context switching overhead

---

## 🎨 UI Features

### Color Coding
- 🔵 **BLUE** - Headers and titles
- 🟢 **GREEN** - Success messages
- 🔴 **RED** - Errors
- 🟡 **YELLOW** - Warnings and prompts
- 🔵 **CYAN** - Information and statistics

### Visual Elements
- Bordered headers with Unicode characters
- Separators for better readability
- Status indicators ([SUCCESS], [ERROR], [!], [*])
- Formatted tables for process information
- Gantt chart visualization

---

## 💾 Data Persistence

Process data is automatically saved to `data/processes.txt` in the format:
```
<process_count>
<pid> <name> <arrival_time> <burst_time> <priority>
...
```

When the program starts, it automatically loads previously saved processes.

---

## 📊 Output Examples

### Process Table
```
PID        NAME                     ARRIVAL         BURST          PRIORITY   STATE        REMAINING
───────────────────────────────────────────────────────────────────────────────────────
1001       Chrome                   0               10             3          READY        10
1002       Firefox                  2               5              2          READY        5
1003       VSCode                   3               8              1          READY        8
```

### Scheduling Results
```
[STATISTICS]
Average Waiting Time: 5.33 ms
Average Turnaround Time: 16.33 ms
```

---

## 🔧 Technical Details

### Data Structures
- **Process**: Struct containing all process information
- **Queue**: FIFO queue for process scheduling
- **Arrays**: For maintaining process lists

### Key Functions
- `addProcess()` - Add new process to system
- `fcfs(), sjf(), priorityScheduling(), roundRobin()` - Scheduling algorithms
- `displayProcesses()` - Render process table
- `saveProcessesToFile()`, `loadProcessesFromFile()` - Persistence

### Constants
- `MAX_PROCESSES`: 100 (maximum concurrent processes)
- `MAX_NAME_LEN`: 50 (max process name length)
- Process States: NEW, READY, RUNNING, WAITING, TERMINATED

---

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| "Command not found: gcc" | Install GCC: `sudo apt install build-essential` |
| Compilation errors | Ensure all header files are in `include/` directory |
| File not found error | Create `data/` directory: `mkdir -p data/` |
| Colors not displaying | Use compatible terminal (most modern terminals support ANSI) |
| Data not loading | Check permissions on `data/processes.txt` |

---

## 🎓 Learning Outcomes

By studying and using this project, you'll understand:
- ✓ CPU scheduling algorithms
- ✓ Process states and transitions
- ✓ Waiting time and turnaround time calculations
- ✓ Process synchronization concepts
- ✓ Queue data structures
- ✓ File I/O in C
- ✓ Terminal UI programming
- ✓ Makefile usage

---

## 📝 Example Session

```
1. Add Process (Chrome, AT=0, BT=10, Priority=3)
2. Add Process (Firefox, AT=2, BT=5, Priority=2)
3. Add Process (VSCode, AT=3, BT=8, Priority=1)
4. Run FCFS Scheduling
5. Run SJF Scheduling
6. Run Priority Scheduling
7. Run Round Robin with Quantum=3
8. View Results and Statistics
9. Save and Exit
```

---

## 📚 References

- Operating System Concepts - Silberschatz, Galvin, Gagne
- CPU Scheduling Algorithms
- Process Management in Unix/Linux

---

## 👨‍💻 Author & Credits

**Process Management System v2.0**
- Professional OS Simulator
- Educational Purpose
- Open Source

---

## 📄 License

This project is provided as-is for educational purposes.

---

## 📞 Support

For issues or questions, ensure:
1. All source files are present
2. Compiler is properly installed
3. Directory structure is maintained
4. Run `make clean && make rebuild`

---

**Happy Learning! 🚀**
