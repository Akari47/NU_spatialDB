#ifndef ITEM_H
#define ITEM_H
#define MAX_NAME_LENGTH 30
#define MAX_CATEGORY_LENGTH 20
#define MAX_X_COORDINATE 32
#define MAX_Y_COORDINATE 32
typedef struct {
    char name[MAX_NAME_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    int x;
    int y;
} Item;
#endif