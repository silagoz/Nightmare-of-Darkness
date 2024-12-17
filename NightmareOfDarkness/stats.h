#ifndef STATS_H
#define STATS_H

#define MAX_ITEM_NAME 50


typedef struct {
    int health;
    int strength;
    int bagCapacity;
    int bagSize;
    char** bag;
} Player;


Player* createPlayer(int health, int strength, int capacity);
void destroyPlayer(Player* player);

int getHealth(Player* player);
void setHealth(Player* player, int health);

int getStrength(Player* player);
void setStrength(Player* player, int strength);

int getBagCapacity(Player* player);
void setBagCapacity(Player* player, int capacity);

int addItem(Player* player, const char* item);
void removeItem(Player* player, const char* item);
void displayStats(Player* player);

void lookBag(Player* player);


#endif
