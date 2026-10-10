#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Mutexes represent the forks between philosophers
pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    // Simulation loop
    for (int i = 0; i < 3; i++) { // Limits iterations for demonstration purposes
        printf("Philosopher %d is THINKING.\n", id);
        sleep(rand() % 2 + 1); // Random thinking time

        // DEADLOCK PREVENTION: Asymmetric acquisition
        // Even philosophers pick right then left; Odd pick left then right.
        // This ensures at least one philosopher can always eat, preventing circular wait.
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[right_fork]);
            pthread_mutex_lock(&forks[left_fork]);
        } else {
            pthread_mutex_lock(&forks[left_fork]);
            pthread_mutex_lock(&forks[right_fork]);
        }

        printf("Philosopher %d is EATING.\n", id);
        sleep(rand() % 2 + 1); // Random eating time (prevents strict starvation patterns)

        // Put down forks
        pthread_mutex_unlock(&forks[left_fork]);
        pthread_mutex_unlock(&forks[right_fork]);
        
        printf("Philosopher %d finished eating and put down forks.\n", id);
    }
    
    printf("Philosopher %d has left the table.\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize the mutexes (forks)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }

    printf("Starting Dining Philosophers Simulation...\n\n");

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_create(&philosophers[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    printf("\nSimulation complete. All philosophers ate successfully.\n");
    return 0;
}