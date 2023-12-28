#include <stdio.h>
#include <stdlib.h>

#include "crawler.h"
#include "curl.h"
//#include "url.h"
//#include "pagedir.h"
#include <stdbool.h>
#include <string.h>
/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */

//Im I allocating twice?
//Im i passing right arg to download?
void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
	//fprintf(stderr, "Argv 0: %s\nArgv 1: %s\n Argv 2: %s\n Argv 3: %s \nMax depth: %ls\n", argv[0],argv[1],argv[2],argv[3],maxDepth); 

	if(argc < 4){//Invalid number of arguments
                fprintf(stderr,"Error: Not enought arguments");
		fprintf(stderr, "This is num args %d\n",argc);
                exit(0);
        }
	//fprintf(stderr, "Stop one\n");
        //bool result = pagedir_init(argv[2]);
        if(pagedir_init(argv[2]) == false){
                fprintf(stderr,"Error: Can not open Directory");
                exit(0);
        }
	//fprintf(stderr, "Stop two\n");
	*pageDirectory = malloc(strlen(argv[2]) + 1);
	//fprintf(stderr,"Stop 2.4\n");
	strcpy(*pageDirectory, argv[2]);
	(*pageDirectory)[strlen(argv[2])] = '\0';
	 //fprintf(stderr, "Stop two.5\n");
        //int maxDepth = argv[3];
        if(atoi(argv[3]) > 10 || atoi(argv[3]) < 0){
                fprintf(stderr,"Error: Invalid depth");
		fprintf(stderr, "This is depth: %d\n", atoi(argv[3]));
                exit(0);
        }
	//fprintf(stderr, "Stop three\n");
	*maxDepth = atoi(argv[3]);
	//fprintf(stderr, "Argv 0: %s\nArgv 1: %s\n Argv 2: %s\n Argv 3: %s \nMax depth: %ls\n", argv[0],argv[1],argv[2],argv[3],maxDepth);
        //char *seedURL = argv[1];
        if(argv[1] == NULL){
                fprintf(stderr,"Error: Invalid seedURL");
                exit(0);
        }
	//fprintf(stderr, "Stop 5\n");
	*seedURL = malloc(strlen(argv[1])+1);
	strcpy(*seedURL,argv[1]);
	(*seedURL)[strlen(argv[1])] = '\0';
	//fprintf(stderr, "Stop 6\n");
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
	size_t size_out;
	char *html = download(seedURL,&size_out);
	int current_depth = 0; //Starting depth
	int document_ID = 1;//In pagedir_save each webpage needs to have their own unique document id
	//fprintf(stderr," Stop 1\n");
	//fprintf(stderr,"This is html: %s",html);
	webpage_t *web = create_webpage();
	web->url = seedURL;
	web->html = html;
	web->length = size_out;
	web->depth = current_depth;
	//{seedURL, html, size_out, current_depth};
	bag_t *bag_visited = create_bag();//Visited websites
	bag_t *bag = create_bag();//Non visited websites
	//fprintf(stderr," Stop 2\n");
	enqueue(bag,web); // Add seedURL to bag
	//fprintf(stderr," Stop 3\n");
	hashtable_t *hashtable = hashtable_new(10000000);
	bool result = hashtable_insert(hashtable, seedURL, seedURL);//Add seedURL to hashtable
	if(result == false){
		exit(0);
	}
	//fprintf(stderr," Stop 4\n");
	int counter = 0;
	while(bag->head != NULL){
		//fprintf(stderr,"Before dequeu\n");
		//webpage_t *webpage = dequeue(bag);
		//while (bag->head != NULL) {
    		//fprintf(stderr, "Before dequeue\n");
   		webpage_t *webpage = dequeue(bag);
		//printf("%d %s\n",webpage->depth, webpage->url);
		printf("%d Fetched: %s\n",webpage->depth, webpage->url);
    		if (webpage == NULL) {
        		fprintf(stderr, "Webpage is NULL after dequeue\n");
        		break; // Break the loop to avoid further issues
    		}
    		//fprintf(stderr, "After dequeue\n");
		if(counter == 1){
		//fprintf(stderr,"This is html: %s\n", webpage->html);
		}
		///fprintf(stderr,"This is counter: %d\n",counter);
		//counter += 1;
    // Rest of your code...


		//fprintf(stderr,"After dequeue\n");
		//webpage = dequeue(bag); // Attributs URL,html,length, depth
		//fprintf(stderr," Stop 4.3\n");
		//if(webpage->url == NULL){ break;}


		char *url = webpage->url;
		//fprintf(stderr," Stop 4.4\n");
		size_out = 0;//Reset sizeout
		//fprintf(stderr," Stop 4.5\n");
		//if(counter == 1){
		//	fprintf(stderr,"This is weburl: %s", url);
		//}
		char *html = download(url,&size_out);
		//fprintf(stderr," Stop 5\n");
		//counter += 1;
		if(html != NULL){
			//char doc_id_str[100];
			//sprintf(doc_id_str, "%d",document_ID);//Convert doc id into string
			//fprintf(stderr," Stop 6, Max depth: %d current depth: %d\n",maxDepth,current_depth);
			//fprintf(stderr,"Stop 5.5, before pagedir_save\n");
			pagedir_save(webpage, pageDirectory,document_ID);
			//fprintf(stderr,"Stop after pagedir\n");
			document_ID += 1;
			//fprintf(stderr,"Stop 6.5\n");
			if(webpage->depth < maxDepth){
				//printf("%d Scanning: %s\n", webpage->depth, webpage->url);
				//fprintf(stderr," Stop 7.777\n");
				pageScan(webpage,bag,hashtable);
				//current_depth += 1;	 // Passing webpage, bag and hashtable
			}
		}

//I need to perform bfs because i am incrementing the depth before it needs to be incremented. The children all need to go not just one before ++



		//free(webpage);
	}
	//free(hashtable);
	//free(bag);
	//free(size_out);

}

/**
 * Scans a webpage for URLs.
Your pagescanner should extract URLs from links in the webpages' HTML
 */

void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
	char *html = page->html;
	char *current_word = page->html;//Pointer to first word in html
	char *start_str = "<a href=\"";
	char *end_str = "\"";

	char *start_str_single = "<a href=\'";//printf("%s:       %d %s\n",page->url,page->depth+1,norm_url);
	char *end_str_single = "\'";

	int count = 5;
	int curr_count =0;
	//fprintf(stderr,"In pageScan\n");
	//char *url = strcat("<a href=\"", page->url);
	//char *complete = strcat(url,"\">");
	while(*current_word != '\0'){
		if(strncmp(current_word, start_str, strlen(start_str)) == 0 || strncmp(current_word, start_str_single,strlen(start_str_single)) == 0){
			//fprintf(stderr,"Found match %s\n",current_word);
			char *start_url = "Dud";//current_word + strlen(start_str);
                        char *end_url = "dud";//strstr(start_url, end_str);
			if(strncmp(current_word, start_str, strlen(start_str)) == 0){
				start_url = current_word + strlen(start_str);
				end_url = strstr(start_url,end_str);
			}else{
				start_url = current_word + strlen(start_str_single);
				end_url = strstr(start_url,end_str_single);
			}
			//printf("%s:       %d %s",page->url,
			//char *start_url = current_word + strlen(start_str);
			//char *end_url = strstr(start_url, end_str);//Find first occurence of string two in string one
			if(end_url != NULL || end_str_single != NULL){
				//fprintf(stderr,"In end URL if\n");
				size_t len = end_url - start_url;
				char *url = malloc(len + 1);
				strncpy(url,start_url,len);
				url[len] = '\0';//Add null character to end of url
				char *norm_url = normalizeURL(page->url, url);
				//if(strcmp(u
					//printf("Found %s\n",norm_url);
				//if(strchr(norm_url,'#') == NULL){

				int length_norm_url = strlen(norm_url);
				 //printf("%s:       %d %s\n",page->url,page->depth+1,norm_url);
				printf("%d Found: %s\n",page->depth+1,norm_url);
				if(norm_url[length_norm_url - 1] != '#'){
					bool result = isInternalURL(page->url,norm_url);
				//fprintf(stderr,"This is url in end URL %s\n",norm_url);
					if(result == true){
						// printf("%s:       %d %s\n",page->url,page->depth+1,norm_url);
					//fprintf(stderr,"Is internal if\n");
						bool insert_result = hashtable_insert(pagesSeen, norm_url,norm_url);//CHecking if url in hashtable
						if(insert_result == true){
						//fprintf(stderr,"Stop 0\n");
							size_t size_out;
							char *html = download(norm_url,&size_out);
						//if(curr_count == 0){
							//fprintf(stderr,"This is hmlt:%s",html);
						//}
						//curr_count +=1;
						//fprintf(stderr, "Stop .5\n");
							webpage_t *new_webpage = create_webpage();
						//fprintf(stderr,"Stop 1\n");
							new_webpage->url = norm_url;
						//fprintf(stderr, "This is url in pageScan: %s\n\n", new_webpage->url);
							new_webpage->html = html;
							new_webpage->length = size_out;
							new_webpage->depth = page->depth + 1;
							printf("%d Added: %s\n", page->depth+1, norm_url);
							enqueue(pagesToCrawl,new_webpage);
						//fprintf(stderr,"After enquiing\n");
						}else{
							printf("%d IgnDupl: %s\n", page->depth+1, norm_url);
						}
//fprintf(stderr,"Within while loop -4\n");
					}else{
						printf("%d IgnExtrn: %s\n",page->depth+1,norm_url);
					}
				}else{
					printf("%d IgnExtrn: %s\n",page->depth+1,norm_url);
				}
				//free(url);
				//free(norm_url);

//fprintf(stderr,"Within while loop -3\n");
			}
//fprintf(stderr,"Within while loop -2\n");
		}
		current_word += 1;
// fprintf(stderr,"Within while loop -1\n");
	}
	//fprintf(stderr,"After while loop\n");
	//free(html);

}

int main(const int argc, char *argv[]) {
	char *seedURL = NULL;
	char *pageDirectory = NULL;
	int maxDepth = 0;
	//fprintf(stderr,"Before seg?");
	parseArgs(argc, argv,&seedURL,&pageDirectory,&maxDepth);
	//fprintf(stderr,"Before after?\n");
	//fprintf(stderr,"This is seedURL: %s\n This is pageDirectory: %s\n This is maxDepth: %d", seedURL, pageDirectory, maxDepth);
	crawl(seedURL, pageDirectory,maxDepth);
	// Fill in with your implementation
}
