#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "page.h"
#define RESULT_PAGE "result.html"
void print_page(Item *result[], int size){
	FILE *f;
	int i,j,k;
	if((f = fopen(RESULT_PAGE, "w")) == NULL){
		printf("Cannot open file %s for writing.\n", RESULT_PAGE);
		return;
	}
	fprintf(f, "<html>\n");
	fprintf(f, "<head>\n");
	fprintf(f, "<title>result page</title>\n");
	fprintf(f, "<style type=\"text/css\">\n");
	fprintf(f, "table { background-image: url(\"nagoya.gif\"); }\n");
	fprintf(f, "td { padding: 0px; border: 1px; width: 16px; height: 14px; font-size: 10px; text-aligh: center; color: #ff00ff; } \n");
	fprintf(f, "</style>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");
	fprintf(f, "<table>\n");
	for(i = 0; i < MAX_Y_COORDINATE; i++){
		fprintf(f, "<tr>\n");
		for(j = 0; j < MAX_X_COORDINATE; j++){
			fprintf(f,"<td>");
            int found_item_label = 0;
            for (k = 0; k < size; k++) {
                if (result[k]->x == j && result[k]->y == i) {
                    fprintf(f, "%d", k + 1);
                    found_item_label = 1;
                    break;
                }
            }
			fprintf(f,"</td>\n");
		}
		fprintf(f, "</tr>\n");
	}
	fprintf(f, "</table>\n");
	if(size == 0){
	    fprintf(f, "<p>No items found to display in HTML report.</p>\n");
	} 
    else{
	    fprintf(f, "<ul>\n");
	    for(k = 0; k < size; k++) {
	        fprintf(f, "<li>%d : %s</li>\n", k, result[k]->name);
	    }
	    fprintf(f, "</ul>\n");
	}
	fprintf(f, "</body>\n");
	fprintf(f, "</html>\n");
	fclose(f);
	printf("Search result HTML report is written to the file %s.\n", RESULT_PAGE);
	return;
}