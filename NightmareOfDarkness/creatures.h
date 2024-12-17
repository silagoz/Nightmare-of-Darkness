#ifndef CREATURES_H
#define CREATURES_H

typedef struct {
    int health;
    int strength;
    char name[50];
} Creature;

// Fonksiyonlar
Creature createCreature(const char* name, int health, int strength);
void displayCreature(const Creature* creature);
int creatureAttack(const Creature* creature);
void creatureTakeDamage(Creature* creature, int damage);
Creature generateRandomCreature();

#endif
