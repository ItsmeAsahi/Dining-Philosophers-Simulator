# Dining Philosophers Simulator

This project is an Operating Systems laboratory course end project that simulates the classic "Dining Philosophers" synchronization problem using C, POSIX threads (`pthreads`), and mutexes. 

## Project Overview

The Dining Philosophers problem illustrates the challenges of allocating limited resources among competing processes without causing deadlock or starvation. In this simulation, five philosophers sit at a round table, alternating between thinking and eating. To eat, a philosopher must pick up both the fork to their left and the fork to their right.

This implementation successfully demonstrates how to manage these resources while actively preventing common concurrency issues.

## Key Features

*   **Multithreading:** Uses `pthreads` to represent each philosopher as an independent concurrent thread.
*   **Resource Synchronization:** Utilizes `pthread_mutex_t` to represent the forks, ensuring mutually exclusive access (only one philosopher can hold a specific fork at a time).
*   **Deadlock Prevention:** Implements an asymmetric resource acquisition strategy to break the "circular wait" condition.
*   **Starvation Mitigation:** Uses randomized thinking and eating durations combined with deadlock prevention to ensure all threads get a chance to execute.

## How it Works (Algorithm)

A standard naive implementation where every philosopher picks up their left fork then their right fork can lead to a **deadlock** (if everyone picks up their left fork simultaneously, no right forks are available, and everyone waits forever).

To solve this, this simulator uses **Asymmetric Acquisition**:
*   **Even-numbered philosophers** (0, 2, 4) pick up their *right* fork first, then their *left* fork.
*   **Odd-numbered philosophers** (1, 3) pick up their *left* fork first, then their *right* fork.

By breaking the symmetry, we guarantee that at least one philosopher will always be able to acquire both forks, thereby preventing the system from freezing and mitigating starvation.

## Prerequisites

To compile and run this program, you will need:
*   A Unix-like operating system (Linux, macOS, or WSL on Windows)
*   GCC (GNU Compiler Collection) or Clang
*   POSIX threads library (usually included by default on Unix systems)

## Compilation and Execution

1.  Save the C code in a file named `dining_philosophers.c`.
2.  Open your terminal and navigate to the directory containing the file.
3.  Compile the program using the `-pthread` flag to link the threading library:

    ```bash
    gcc dining_philosophers.c -o dining_simulator -pthread
    ```

4.  Run the executable:

    ```bash
    ./dining_simulator
    ```

## Example Output

You will see output indicating the state transitions of each philosopher as the threads run concurrently:

```text
Starting Dining Philosophers Simulation...

Philosopher 0 is THINKING.
Philosopher 1 is THINKING.
Philosopher 2 is THINKING.
Philosopher 0 is EATING.
Philosopher 1 is EATING.
Philosopher 0 finished eating and put down forks.
Philosopher 3 is EATING.
...
Simulation complete. All philosophers ate successfully.
```