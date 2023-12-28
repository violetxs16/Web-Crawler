#ifndef CRAWLER_H
#define CRAWLER_H
#include "pagedir.h"
#include <stdlib.h>
#include <stddef.h>
#include "hashtable.h"
#include "url.h"
#include "curl.h"
#include "queue.h"

//typedef struct bag bag_t;
struct bag;
typedef struct webpage webpage_t;

struct webpage{
        char *url;
        char *html;
        size_t length;
        int depth;
};

void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

void crawl(char* seedURL, char* pageDirectory, const int maxDepth);

void pageScan(webpage_t* page, struct bag* pagesToCrawl, hashtable_t* pagesSeen);

#endif
