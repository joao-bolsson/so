/**
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @version 2019, May 19.
 */
#include "curl_code.h"

#define LINKS 50
#define CLICKS_COUNT 7

int main() {
    char *word = "Sport Club Internacional";
    char *firstLink = "https://pt.wikipedia.org/wiki/Sistema_operativo";

    srand(time(NULL));
    CURL *curl_handle;

    char *pageContent = download_page(curl_handle, firstLink);

    // links_readed: variavel onde o numero de links lidos eh salvo.
    int links_readed;
    // links inside the page. that will get 50 links
    char **links = find_links(curl_handle, pageContent, LINKS, &links_readed);

    if (links_readed == LINKS) {
        // show all links
        for (int i = 0; i < LINKS; i++) {
            printf("%d. %s\n", i, links[i]);
        }
    }

    // Sorteia um dos links para ser acessado.
    int random = rand() % links_readed;

    printf("\nLINK SORTEADO: %s\n", links[random]);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
    return 0;
}

