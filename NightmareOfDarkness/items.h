#ifndef ITEMS_H
#define ITEMS_H

#include "stats.h"

#define MAX_ITEM_NAME 50

typedef struct {
    char name[MAX_ITEM_NAME];
    int value;
    int weight;
    void (*useItem)(Player* player);
} Item;


Item createPotion();
Item createBigPotion();
Item createBatpon();
Item createLifeSaver();
Item createSoulScreamer();
Item* dropItem();
void displayItem(const Item* item);

#endif
