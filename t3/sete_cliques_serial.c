/**
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @version 2019, May 19.
 */
#include "curl_code.h"

#define LINKS 50
#define CLICKS_COUNT 7

typedef struct {
    /**
     * Link name.
     */
    char *link;

    /**
     * Page content of the link.
     */
    char *pageContent;
} LINK;

typedef struct {
    /**
     * All the links in a page.
     */
    LINK links[LINKS];
} PAGE;

typedef struct {
    /**
     * Pages of the stack.
     */
    PAGE pages[CLICKS_COUNT];
} STACK;

int main() {
    char *word = "Sport Club Internacional";

    srand(time(NULL));
    CURL *curl_handle;

    LINK first= {.link = "https://pt.wikipedia.org/wiki/Sistema_operativo"};
    first.pageContent = download_page(curl_handle, first.link);

    PAGE firstPage = {};

    // links_readed: variavel onde o numero de links lidos eh salvo.
    int links_readed;
    // links inside the page. that will get 50 links
    char **links = find_links(curl_handle, first.pageContent, LINKS, &links_readed);

    if (links_readed == LINKS) {
        // show all links
        for (int i = 0; i < LINKS; i++) {
            LINK link = {.link = links[i]};
            firstPage.links[i] = link;

            printf("%d. %s\n", i, links[i]);
        }
    }

    STACK stack;
    stack.pages[0] = firstPage;


    // Sorteia um dos links para ser acessado.
    int random = rand() % links_readed;

    printf("\nLINK SORTEADO: %s\n", firstPage.links[random].link);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
    return 0;
}

