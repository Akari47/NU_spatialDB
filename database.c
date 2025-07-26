#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "readline.h"
#include "database.h"
#include "page.h"
static Item item_array[MAX_ITEM_SIZE];
static int item_count = 0;
void insert_item(){
    if(item_count == MAX_ITEM_SIZE){
        printf("Database is full; can't add more items.\n");
        return;
    }
    Item newitem;
    printf("Enter the name of item: ");
    read_line(newitem.name, MAX_NAME_LENGTH);
    printf("Enter the category of item: ");
    read_line(newitem.category, MAX_CATEGORY_LENGTH);
    printf("Enter the x-coordinate: ");
    scanf("%d", &newitem.x);
    if(newitem.x < 0 || newitem.x > MAX_X_COORDINATE){
        printf("Error: x coordinate out of bounds.\n");
        return;
    }    
    printf("Enter the y-coordinate: "); 
    scanf("%d", &newitem.y);
    if(newitem.y < 0 || newitem.y > MAX_Y_COORDINATE){
        printf("Error: y coordinate out of bounds.\n");
        return;
    }

    item_array[item_count] = newitem;
    item_count++;
}
void print_all_items(){
    int i;
    printf("+------------------------------+------------------------------+---------+\n");
    printf("| Item name                    | Category                     | Position|\n");
    printf("+------------------------------+------------------------------+---------+\n");
    for(i = 0; i < item_count; i++){
        printf("| %-28.28s | %-28.28s | (%2d, %2d)|\n",
               item_array[i].name,
               item_array[i].category,
               item_array[i].x,
               item_array[i].y);
    }
    printf("+------------------------------+------------------------------+---------+\n");
}
void load_items(){
    printf("Enter a file name for loading: ");
    char file_name[MAX_FILE_PATH_LENGTH+1];
    read_line(file_name, MAX_FILE_PATH_LENGTH);
    FILE *fp;
    fp = fopen(file_name, "r");
    if(fp == NULL){
        printf("Cannot open the file\n");
        return;
    }
    char line[MAX_NAME_LENGTH + MAX_CATEGORY_LENGTH + 10];
    while(fgets(line, sizeof(line), fp) != NULL){
        Item newitem;
        if(sscanf(line, "%[^,],%[^,],%d,%d", newitem.name, newitem.category, &newitem.x, &newitem.y) == 4){
                if(item_count < MAX_ITEM_SIZE){
                    item_array[item_count] = newitem;
                    item_count++;
                }
                else{
                    printf("Warning: Database is full.\n");
                    break;
                }
            }
        }
    fclose(fp);
    printf("Items loaded successfully from %s. Total items: %d\n", file_name, item_count);
}
void save_items() {
    printf("Enter a file name for saving: ");
    char file_name[MAX_FILE_PATH_LENGTH];
    read_line(file_name, MAX_FILE_PATH_LENGTH);
    FILE *fp;
    fp = fopen(file_name, "w"); 
    if(fp == NULL){
        printf("Cannot open the file for saving\n");
        return;
    }
    for(int i = 0; i < item_count; i++) {
        fprintf(fp, "%s,%s,%d,%d\n", item_array[i].name, item_array[i].category, item_array[i].x, item_array[i].y);
    }
    fclose(fp);
    printf("Items saved successfully to %s. Total items: %d\n", file_name, item_count);
}
void find_items_by_name(){
    printf("Enter an item name for searching: ");
    char search_name[MAX_NAME_LENGTH];
    read_line(search_name, MAX_NAME_LENGTH);
    Item *result[MAX_ITEM_SIZE]; 
    int num_result = 0;
    for(int i = 0; i < item_count; i++){
        if(strcmp(item_array[i].name, search_name) == 0){
                result[num_result] = &item_array[i]; 
                num_result++;
        }
    }
    print_page(result, num_result);
}
void find_items_by_category(){
    printf("Enter an item category for searching: ");
    char search_category[MAX_CATEGORY_LENGTH];
    read_line(search_category, MAX_CATEGORY_LENGTH);
    Item *result[MAX_ITEM_SIZE]; 
    int num_result = 0;
    for (int i = 0; i < item_count; i++) {
        if(strcmp(item_array[i].category, search_category) == 0){
                result[num_result] = &item_array[i]; 
                num_result++;
        }
    }
    print_page(result, num_result);
}
void find_items_by_range(){
    int user_x, user_y;
    double threshold;
    Item *result[MAX_ITEM_SIZE];
    int num_result = 0;
    printf("Enter your x-coordinate: ");
    scanf("%d", &user_x);
    if(user_x < 0 || user_x > MAX_X_COORDINATE){
        printf("Error: x coordinate out of bounds (0-%d).\n", MAX_X_COORDINATE);
        return;
    }
    printf("Enter your y-coordinate: ");
    scanf("%d", &user_y);
    if(user_y < 0 || user_y > MAX_Y_COORDINATE){
        printf("Error: y coordinate out of bounds (0-%d).\n", MAX_Y_COORDINATE);
        return;
    }
    printf("Your position is now (%d,%d)\n", user_x, user_y);
    printf("Enter distance threshold (m): ");
    scanf("%lf", &threshold);
    for(int i = 0; i < item_count; i++){
        double distance_cells = sqrt(pow(item_array[i].x - user_x, 2) + pow(item_array[i].y - user_y, 2));
        double distance_meters = distance_cells * 40.0;

        if(distance_meters <= threshold){
            if(num_result < MAX_ITEM_SIZE){
                result[num_result] = &item_array[i];
                num_result++;
            }
        }
    }
    print_page(result, num_result);
}
void find_nearest_neighbor(){
    int user_x, user_y;
    Item *nearest_item = NULL;
    double min_distance = -1.0;
    printf("Enter your x-coordinate: ");
    scanf("%d", &user_x);
    if(user_x < 0 || user_x > MAX_X_COORDINATE){
        printf("Error: x coordinate out of bounds (0-%d).\n", MAX_X_COORDINATE);
        return;
    }
    printf("Enter your y-coordinate: ");
    scanf("%d", &user_y);
    if(user_y < 0 || user_y > MAX_Y_COORDINATE){
        printf("Error: y coordinate out of bounds (0-%d).\n", MAX_Y_COORDINATE);
        return;
    }
    printf("Your position is now (%d,%d)\n", user_x, user_y);
    for(int i = 0; i < item_count; i++) {
        double distance_cells = sqrt(pow(item_array[i].x - user_x, 2) + pow(item_array[i].y - user_y, 2));
        double current_distance_meters = distance_cells * 40.0;
        if (nearest_item == NULL || current_distance_meters < min_distance) {
            min_distance = current_distance_meters;
            nearest_item = &item_array[i];
        }
    }
    Item *result[1];
    result[0] = nearest_item;
    print_page(result, 1);
    printf("Nearest item found: %s at (%d, %d) with distance %.2f meters.\n", 
               nearest_item->name, nearest_item->x, nearest_item->y, min_distance);
}
void find_items_by_name_partial(){
    printf("Enter partial of items name for searching: ");
    char search_name[MAX_NAME_LENGTH];
    read_line(search_name, MAX_NAME_LENGTH);
    Item *result[MAX_ITEM_SIZE]; 
    int num_result = 0;
    for (int i = 0; i < item_count; i++) {
        if(strstr(item_array[i].name, search_name) != NULL){
                result[num_result] = &item_array[i]; 
                num_result++;
        }
    }
    print_page(result, num_result);
}
void find_by_category_nearest() {
    printf("Enter an item category for searching: ");
    char search_category[MAX_CATEGORY_LENGTH];
    read_line(search_category, MAX_CATEGORY_LENGTH);
    int category_found_in_database = 0;
    for (int i = 0; i < item_count; i++) {
        if (strcmp(item_array[i].category, search_category) == 0) {
            category_found_in_database = 1;
            break;
        }
    }
    if (!category_found_in_database) { 
        printf("Error: Category '%s' does not exist in the database.\n", search_category);
        return; 
    }
    int user_x, user_y;
    printf("Enter your x-coordinate: ");
    scanf("%d", &user_x);
    if(user_x < 0 || user_x > MAX_X_COORDINATE){
        printf("Error: x coordinate out of bounds (0-%d).\n", MAX_X_COORDINATE);
        return;
    }
    printf("Enter your y-coordinate: ");
    scanf("%d", &user_y);
    if(user_y < 0 || user_y > MAX_Y_COORDINATE){
        printf("Error: y coordinate out of bounds (0-%d).\n", MAX_Y_COORDINATE);
        return;
    }
    printf("Your position is now (%d,%d)\n", user_x, user_y);
    Item *nearest_in_category = NULL;
    double min_distance_in_category = -1.0;
    for (int i = 0; i < item_count; i++) {
        if (strcmp(item_array[i].category, search_category) == 0) {
            double distance_cells = sqrt(pow(item_array[i].x - user_x, 2) + pow(item_array[i].y - user_y, 2));
            double current_distance_meters = distance_cells * 40.0;
            if (nearest_in_category == NULL || current_distance_meters < min_distance_in_category) {
                min_distance_in_category = current_distance_meters;
                nearest_in_category = &item_array[i];
            }
        }
    }
    Item *result[1];
    if (nearest_in_category != NULL) {
        result[0] = nearest_in_category;
        print_page(result, 1);
        printf("Nearest item in category '%s' found: %s at (%d, %d) with distance %.2f meters.\n", 
               search_category, nearest_in_category->name, nearest_in_category->x, nearest_in_category->y, min_distance_in_category);
    }
}