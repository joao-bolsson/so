#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5

sem_t mutex; // avoid two thread accessing the room at the same time
sem_t empty; // number of empty positions in the room
sem_t full;  // number of occupied positions in the room

pthread_t studentsInRoom[N];

char* idStudents[N];

int notUsed = 1; // just for don't get a warn of endless loop in the 'while's

int nextPosition; // next empty position of studentsInRoom

void *student(void* thread) {
    char* st = (char*) thread;
    while (notUsed > 0) {
        // produz
        sem_wait(&empty);
        sem_wait(&mutex);

        int inRoom = 0;
        // checks if the student is already in the room
        for (int i = 0; i < N; i++) {
            if (idStudents[i] == st) {
                inRoom = 1; // true
                printf("estudante %s já está na sala\n", st);
                break;
            }
        }

        if (!inRoom) {
            // insert
            idStudents[nextPosition] = st;
            printf("estudante %s entrou na sala na posição %d\n", st, nextPosition);
            nextPosition = (nextPosition + 1) % N;
        }

        sem_post(&mutex);
        sem_post(&full);
    }
}

// fellowship
void *manager(void *thread) {
    while (notUsed > 0) {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("bolsista entrou na sala\n");
        printf("proxima posição: %d\n", nextPosition);

        // remove
//        printf("entrega carteirinha pra entudante\n");

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main(void) {
    nextPosition = 0;
    int n = 20;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    printf("Inicializando os estudantes, total: %d\n", n);

    pthread_t students[n];
    char ids[n];

    char id = 'a';
    // creating the students
    for (int i = 0; i < n; i++) {
        ids[i] = id++;
        pthread_create(&students[i], NULL, student, &ids[i]);
        pthread_join(students[i], 0);
    }

    // creating the manager
    pthread_t fellowship;
    pthread_create(&fellowship, 0, manager, &fellowship);
    pthread_join(fellowship, 0);

    return 0;
}