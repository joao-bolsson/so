#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

/**
 * Max number of students in the room.
 */
#define N 5

/**
 * Time in seconds that each student must sleep.
 */
#define SLEEP_STUDENT 2

/**
 * Time in seconds that the manager must sleep.
 */
#define SLEEP_MANAGER 10

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

            printf("estudante %d entra na sala na posicao %d\n", *st, nextPosition);

            studentsInRoom[nextPosition] = st;
            nextPosition = (nextPosition + 1) % N;

            sem_post(&mutex);
        }

        sleep(SLEEP_STUDENT);
    }
    return NULL;
}

// fellowship
void *manager() {
    while (notUsed > 0) {
        sleep(SLEEP_MANAGER);

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Parâmetros errados ./main <numberOfStudents>\n");
        return 0;
    }

    char *p;
    int n; // number of students
    long conv = strtol(argv[1], &p, 10);

    n = (int) conv;

    if (n < N) {
        printf("Deve haver um mínimo de 5 estudantes\n");
        return 0;
    }

    nextPosition = 0;

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