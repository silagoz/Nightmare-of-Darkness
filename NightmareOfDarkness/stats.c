#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Player* createPlayer(int health, int strength, int capacity) {
    Player* player = (Player*)malloc(sizeof(Player));
    if (!player) {
        printf("Memory allocation failed for player.\n");
        return NULL;
    }
    player->health = health;
    player->strength = strength;
    player->bagCapacity = capacity;
    player->bagSize = 0;
    player->bag = (char**)malloc(capacity * sizeof(char*));
    if (!player->bag) {
        printf("Memory allocation failed for bag.\n");
        free(player);
        return NULL;
    }
    return player;
}


void destroyPlayer(Player* player) {
    if (!player) return;
    for (int i = 0; i < player->bagSize; ++i) {
        free(player->bag[i]);
    }
    free(player->bag);
    free(player);
}

int getHealth(Player* player) {
    return player->health;
}

void setHealth(Player* player, int health) {
    player->health = health;
}


int getStrength(Player* player) {
    return player->strength;
}

void setStrength(Player* player, int strength) {
    player->strength = strength;
}


int getBagCapacity(Player* player) {
    return player->bagCapacity;
}

void setBagCapacity(Player* player, int capacity) {
    char** newBag = (char**)realloc(player->bag, capacity * sizeof(char*));
    if (!newBag) {
        printf("Memory reallocation failed for bag.\n");
        return;
    }
    player->bag = newBag;
    player->bagCapacity = capacity;
    if (player->bagSize > capacity) {
        player->bagSize = capacity;
    }
}


int addItem(Player* player, const char* item) {
    if (player->bagSize >= player->bagCapacity) {
        printf("Bag is full! Cannot add item: %s\n", item);
        return 0;
    }
    player->bag[player->bagSize] = (char*)malloc((strlen(item) + 1) * sizeof(char));
    if (!player->bag[player->bagSize]) {
        printf("Memory allocation failed for item: %s\n", item);
        return 0;
    }
    strcpy(player->bag[player->bagSize], item);
    player->bagSize++;
    return 1;
}


void removeItem(Player* player, const char* item) {
    int found = 0;
    for (int i = 0; i < player->bagSize; ++i) {
        if (strcmp(player->bag[i], item) == 0) {
            free(player->bag[i]);
            for (int j = i; j < player->bagSize - 1; ++j) {
                player->bag[j] = player->bag[j + 1];
            }
            player->bagSize--;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Item not found in the bag: %s\n", item);
    }
}


void displayStats(Player* player) {
    printf("Player Stats:\n");
    printf("Health: %d\n", player->health);
    printf("Strength: %d\n", player->strength);
    printf("Bag Capacity: %d\n", player->bagCapacity);
    printf("Bag Items: ");
    if (player->bagSize == 0) {
        printf("None\n");
    } else {
        for (int i = 0; i < player->bagSize; ++i) {
            printf("%s ", player->bag[i]);
        }
        printf("\n");
    }
}

