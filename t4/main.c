#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

sem_t mutex; // avoid two thread accessing the room at the same time
sem_t empty; // number of empty positions in the room
sem_t full;  // number of occupied positions in the room

int *studentsInRoom[N];

int notUsed = 1; // just for don't get a warn of endless loop in the 'while's

int nextPosition; // next empty position of studentsInRoom

void *student(void *thread) {
    int *st = (int *) thread;
    while (notUsed > 0) {
        // produz
        sem_wait(&empty);
        sem_wait(&mutex);

        int inRoom = 0;
        // checks if the student is already in the room
        for (int i = 0; i < N; i++) {
            if (studentsInRoom[i] == st) {
                inRoom = 1; // true
                printf("estudante %p já está na sala\n", st);
                break;
            }
        }

        if (!inRoom) {
            // insert
            studentsInRoom[nextPosition] = st;
            printf("estudante %p entrou na sala na posição %d\n", st, nextPosition);
            nextPosition = (nextPosition + 1) % N;
        }

        sem_post(&mutex);
        sem_post(&full);
        sleep(2);
    }
    return NULL;
}

// fellowship
void *manager() {
    while (notUsed > 0) {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("bolsista entrou na sala\n");
        printf("proxima posição: %d\n", nextPosition);

        // remove
//        printf("entrega carteirinha pra entudante\n");

        sem_post(&mutex);
        sem_post(&empty);
        sleep(5);
    }
    return NULL;
}

int main(void) {
    nextPosition = 0;
    int n = 20;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

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