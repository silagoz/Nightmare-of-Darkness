#include "creatures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Creature createCreature(const char* name, int health, int strength) {
    Creature creature;
    creature.health = health;
    creature.strength = strength;
    strncpy(creature.name, name, sizeof(creature.name) - 1);
    creature.name[sizeof(creature.name) - 1] = '\0';
    return creature;
}

void displayCreature(const Creature* creature) {
    printf("Creature: %s\n", creature->name);
    printf("Health: %d\n", creature->health);
    printf("Strength: %d\n", creature->strength);
}

int creatureAttack(const Creature* creature) {
    return creature->strength + (rand() % 5);
}

void creatureTakeDamage(Creature* creature, int damage) {
    creature->health -= damage;
    if (creature->health < 0) {
        creature->health = 0;
    }
}

Creature generateRandomCreature() {
    int random = rand() % 4;
    if (random == 0) {
        return createCreature("Kenzius", 60, 15);
    } else if (random == 1) {
        return createCreature("Valerie", 30, 5);
    } else if (random == 2) {
        return createCreature("Batty", 32, 11);
    }else {
        return createCreature("Shaxel", 45, 9);
    }
}

