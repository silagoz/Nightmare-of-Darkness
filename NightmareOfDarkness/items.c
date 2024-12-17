#include "items.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void usePotion(Player* player) {
    player->health += 20;
    if (player->health > 100) {
        player->health = 100;
    }
    printf("Potion used! Player's health is now %d.\n", player->health);
}

void useBigPotion(Player* player) {
    player->health += 50;
    if (player->health > 100) {
        player->health = 100;
    }
    printf("Big Potion used! Player's health is now %d.\n", player->health);
}

void useLifeSaver(Player* player) {
    printf("Life Saver equipped! Life Saver is a shield. Player will take 5 less damage from attacks.\n");
}

void useBatpon(Player* player) {
    player->strength += 20;
    printf("Batpon equipped! Batpon is a gun. Player's strength increased to %d.\n", player->strength);
}


void useSoulScreamer(Player* player) {
    player->strength += 10;
    printf("Soul Screamer equipped! Soul Screamer is a knife. Player's strength increased to %d.\n", player->strength);
}


Item createPotion() {
    Item item;
    strncpy(item.name, "Potion", MAX_ITEM_NAME - 1);
    item.name[MAX_ITEM_NAME - 1] = '\0';
    item.value = 50;
    item.weight = 1;
    item.useItem = usePotion;
    return item;
}

Item createBigPotion() {
    Item item;
    strncpy(item.name, "Big Potion", MAX_ITEM_NAME - 1);
    item.name[MAX_ITEM_NAME - 1] = '\0';
    item.value = 70;
    item.weight = 2;
    item.useItem = useBigPotion;
    return item;
}

Item createLifeSaver() {
    Item item;
    strncpy(item.name, "Life Saver", MAX_ITEM_NAME - 1);
    item.name[MAX_ITEM_NAME - 1] = '\0';
    item.value = 80;
    item.weight = 4;
    item.useItem = useLifeSaver;
    return item;
}

Item createBatpon() {
    Item item;
    strncpy(item.name, "Batpon Weapon", MAX_ITEM_NAME - 1);
    item.name[MAX_ITEM_NAME - 1] = '\0';
    item.value = 100;
    item.weight = 5;
    item.useItem = useBatpon;
    return item;
}

Item createSoulScreamer() {
    Item item;
    strncpy(item.name, "Soul Screamer", MAX_ITEM_NAME - 1);
    item.name[MAX_ITEM_NAME - 1] = '\0';
    item.value = 100;
    item.weight = 3;
    item.useItem = useSoulScreamer;
    return item;
}


void displayItem(const Item* item) {
    printf("Item: %s\n", item->name);
    printf("Value: %d\n", item->value);
    printf("Weight: %d\n", item->weight);
}

