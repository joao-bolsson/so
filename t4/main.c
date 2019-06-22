#include <stdio.h>
#include <semaphore.h>

#define N 5

sem_t mutex; // avoid two thread accessing the room at the same time
sem_t empty; // number of empty positions in the room
sem_t full;  // number of occupied positions in the room

int i = 1;

void student() {
    while(i > 0) {
        // produz
        sem_wait(&empty);
        sem_wait(&mutex);

        // insert

        printf("estudante entrou na fila\n");

        sem_post(&mutex);
        sem_post(&full);
    }
}

// fellowship
void manager() {
    while(i > 0) {
        sem_wait(&full);
        sem_wait(&mutex);

        // remove
        printf("entrega carteirinha pra entudante\n");

        sem_post(&mutex);
        sem_post(&empty);
        // consome
    }
}

int main() {
    printf("Hello, World!\n");

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);


    return 0;
}