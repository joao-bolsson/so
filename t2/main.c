#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <wait.h>
#include <time.h>

#define MAXCHAR 1000
#define TIPS_SIZE 23
#define PATH_TIPS "./banco_de_dicas.txt"

/**
 * Gets a tip from tips file.
 * @param str String to store the tip.
 * @return The string with a tip from tips file.
 */
const char *getTip(char *str) {
    FILE *fp;
    char *filename = PATH_TIPS;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return NULL;
    }

    int r = rand() % TIPS_SIZE;
    int i = 0;

    while (fgets(str, MAXCHAR, fp) != NULL) {
        if (i == r) {
            break;
        }
        i++;
    }
    fclose(fp);
    return str;
}

/**
 * Creates a tip file inside of given directory.
 * @param dir Given directory path.
 */
void createTipFile(const char *dir) {
    char path[1024];

    snprintf(path, sizeof (path), "%s/%s", dir, "dica_do_dia.txt");

    FILE *fPtr = fopen(path, "w");

    if (fPtr == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    char str[MAXCHAR];
    getTip(str);

    fputs(str, fPtr);
    fclose(fPtr);
}

/**
 * List all sub-directories from a given directory and creates a process with fork for each one of them.
 * @param name Given base directory.
 */
void listdir(const char *name) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(name);
    if (dir == NULL) return;

    pid_t idProcesso;
    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

            idProcesso = fork();
            wait(NULL); // each process must wait the children

            if (idProcesso < 0) {
                // failure case
                fprintf(stderr, "fork falhou\n");
                closedir(dir);
                exit(-1);
            }

            if (idProcesso == 0) { // child
                snprintf(path, sizeof (path), "%s/%s", name, entry->d_name);

                printf("%d [label=\"%s, %d\"];\n", getpid(), path, getpid());
                printf("%d -> %d;\n", getppid(), getpid());

                // call recursively the list of directories of the current path
                listdir(path);

                // creates the tip file
                createTipFile(path);
                exit(0); // after the creation of tip file the process exits
            }
        }
    }
    closedir(dir);
}

int main() {
    srand((unsigned int) time(NULL));

    printf("digraph G {\n");
    // creates a tip file in root path and starts the process to build forks from it
    const char *path = "./home";
    createTipFile(path);
    printf("%d [label=\"%s, %d\"];\n", getpid(), path, getpid());
    listdir(path);

    printf("}\n");
    return 0;
}
