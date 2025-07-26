#include <stdio.h>
#include "item.h"
#include "database.h"
int main(void){
    char code;
    for(;;){
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n');
        switch(code){
            case 'i': insert_item();
                break;
            case 'p': print_all_items();
                break;
            case 'l': load_items();
                break;
            case 's': save_items();
                break;
            case 'f': find_items_by_name();
                break;
            case 'c': find_items_by_category();
                break;
            case 'r': find_items_by_range();
                break;
            case 'n': find_nearest_neighbor();
                break;
            case 'w': find_items_by_name_partial();
                break;
            case 'd': find_by_category_nearest();
                break;
            case 'q': return 0;
            default:  printf("Illegal code\n");
        }
        printf("\n");
    }
}