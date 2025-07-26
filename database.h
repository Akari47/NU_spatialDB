#ifndef DATABASE_H
#define DATABASE_H
#include "item.h"
#define MAX_ITEM_SIZE 100 
#define MAX_FILE_PATH_LENGTH 30
void insert_item();
void print_all_items();
void load_items();
void save_items();
void find_items_by_name();
void find_items_by_category();
void find_items_by_range();
void find_nearest_neighbor();
void find_items_by_name_partial();
void find_by_category_nearest();
#endif