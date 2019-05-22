/**
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @version 2019, May 22.
 */
#include "curl_code.h"
#include <time.h>
#include <pthread.h>

#define LINKS 50
#define WORD "Sport Club Internacional"
#define CLICKS_COUNT 7
#define THREADS 2

int links_readed;
char **links;
int count = 1;

/**
 * Look for the word on the page content of the given list of links.
 *
 * @param links Links to search.
 * @param links_readed Number of readed links.
 * @param count Clicks count.
 */
void findWord(char **links, int links_readed, int count) {
    if (count > CLICKS_COUNT) {
        printf("Palavra não encontrada\n");
        return;
    }
    int random = rand() % links_readed;

    // sorted link
    char *sortedLink = links[random];

    CURL *curl_handle;

    char *pageContent = download_page(curl_handle, sortedLink);
    if (strstr(pageContent, WORD) != NULL) {
        printf("Palavra encontrada\n");
        return;
    }

    // links_readed: variavel onde o numero de links lidos eh salvo.
    int numberLinks;
    // links inside the page. that will get 50 links
    char **otherLinks = find_links(curl_handle, pageContent, LINKS, &numberLinks);

    findWord(otherLinks, numberLinks, ++count);
}

void *threadFind() {
    findWord(links, links_readed, count);
    return NULL;
}

int main() {
    clock_t Ticks[2];
    Ticks[0] = clock();

    char *firstLink = "https://pt.wikipedia.org/wiki/Sistema_operativo";

    srand(time(NULL));
    CURL *curl_handle;

    char *pageContent = download_page(curl_handle, firstLink);

    if (strstr(pageContent, WORD) != NULL) {
        printf("Palavra encontrada\n");
    } else {
        // links inside the page. that will get 50 links
        links = find_links(curl_handle, pageContent, LINKS, &links_readed);

        pthread_t threads[THREADS];

        for (int i = 0; i < THREADS; i++) {
            pthread_create(&threads[i], NULL, threadFind, NULL);
            pthread_join(threads[i], NULL);
        }
    }
    Ticks[1] = clock();
    double time = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    printf("Tempo gasto: %g ms.\n", time);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
    return 0;
}

