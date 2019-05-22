/**
 * @author João Bolsson (jvmarques@inf.ufsm.br)
 * @version 2019, May 19.
 */
#include "curl_code.h"

#define LINKS 50
#define WORD "Sport Club Internacional"
#define CLICKS_COUNT 7

/**
 * Look for the word on the page content of the given list of links.
 *
 * @param links Links to search.
 * @param links_readed Number of readed links.
 * @param count Clicks count.
 */
char *findWord(char **links, int links_readed, int count) {
    if (count > CLICKS_COUNT) {
        return "Palavra não encontrada";
    }
    int random = rand() % links_readed;

    // sorted link
    char *sortedLink = links[random];

    CURL *curl_handle;

    char *pageContent = download_page(curl_handle, sortedLink);
    if (strstr(pageContent, WORD) != NULL) {
        return "Palavra encontrada";
    }

    // links_readed: variavel onde o numero de links lidos eh salvo.
    int numberLinks;
    // links inside the page. that will get 50 links
    char **otherLinks = find_links(curl_handle, pageContent, LINKS, &numberLinks);

    return findWord(otherLinks, numberLinks, ++count);
}

int main() {
    char *firstLink = "https://pt.wikipedia.org/wiki/Sistema_operativo";

    srand(time(NULL));
    CURL *curl_handle;

    char *pageContent = download_page(curl_handle, firstLink);

    if (strstr(pageContent, WORD) != NULL) {
        printf("Palavra encontrada\n");
        return 0;
    }

    int links_readed;
    // links inside the page. that will get 50 links
    char **links = find_links(curl_handle, pageContent, LINKS, &links_readed);

    char *response = findWord(links, links_readed, 1);

    printf("RESPOSTA: %s\n", response);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();
    return 0;
}

