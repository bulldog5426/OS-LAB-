#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t chopsticks[N]; // Mutex locks for chopsticks

// Function to simulate philosopher's behavior
void *philosopher(void *arg) {
    int id = *((int *)arg);

    // Each philosopher picks up the chopsticks to their left and right
    pthread_mutex_lock(&chopsticks[id]);
    pthread_mutex_lock(&chopsticks[(id + 1) % N]);

    printf("Philosopher %d is eating.\n", id);
    sleep(2); // Eating time

    // Release the chopsticks
    pthread_mutex_unlock(&chopsticks[id]);
    pthread_mutex_unlock(&chopsticks[(id + 1) % N]);

    printf("Philosopher %d finished eating.\n", id);

    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize mutex locks for chopsticks
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Create threads for each philosopher
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
