#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

/**
 * Avoid two thread accessing the room at the same time.
 */
sem_t mutex;

int *studentsInRoom[N];

sem_t positions[N];

int notUsed = 1; // just for don't get a warn of endless loop in the 'while's

int nextPosition; // next empty position of studentsInRoom

void *student(void *thread) {
    int *st = (int *) thread;
    while (notUsed > 0) {
        sem_wait(&mutex);

        int inRoom = 0;
        // checks if the student is already in the room
        for (int i = 0; i < N; i++) {
            if (studentsInRoom[i] == st) {
                inRoom = 1; // true
                break;
            }
        }

        sem_post(&mutex);

        if (!inRoom) {
            // wait for the position is empty
            sem_wait(&positions[nextPosition]);
            sem_wait(&mutex);

            printf("estudante %p entra na sala na posicao %d\n", st, nextPosition);

            studentsInRoom[nextPosition] = st;
            nextPosition = (nextPosition + 1) % N;

            sem_post(&mutex);
        }

        sleep(2);
    }
    return NULL;
}

// fellowship
void *manager() {
    while (notUsed > 0) {
        sleep(10);

        sem_wait(&mutex);
        printf("bolsista entrou na sala\n");

        for (int i = 0; i < N; i++) {
            printf("Entrega carteirinha %d\n", i);
            sem_post(&positions[i]);
        }

        printf("bolsista saiu da sala\n");
        sem_post(&mutex);
    }
    return NULL;
}

int main(void) {
    nextPosition = 0;
    int n = 20; // TODO: receber n por parametro

    if (n < N) {
        printf("Deve haver um mínimo de 5 estudantes\n");
    }

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++) {
        sem_init(&positions[i], 0, 1);
    }

    printf("Inicializando os estudantes, total: %d\n", n);

    pthread_t students[n];
    int id[n]; // student id

    // creating the students
    for (int i = 0; i < n; i++) {
        id[i] = i;
        pthread_create(&students[i], NULL, student, &id[i]);
    }

    // creating the manager
    pthread_t fellowship;
    pthread_create(&fellowship, 0, manager, NULL);

    for (int i = 0; i < n; i++) {
        pthread_join(students[i], 0);
    }
    pthread_join(fellowship, 0);

    return 0;
}