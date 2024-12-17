#include "stats.c"
#include "creatures.c"
#include "items.c"
#include "rooms.c"
#include "menucommands.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Sila Gözümoglu 22050161005

Item* dropItem() {
    Item* newItem = (Item*)malloc(sizeof(Item));
    int random = rand() % 5;

    if (random == 0) {
        *newItem = createPotion();
    } else if (random == 1) {
        *newItem = createBigPotion();
    } else if (random == 2) {
        *newItem = createBatpon();
    } else if (random == 3) {
        *newItem = createLifeSaver();
    } else {
        *newItem = createSoulScreamer();
    }

    return newItem;
}

Room* movePlayer(Room* currentRoom, const char* direction) {
    if (strcmp(direction, "up") == 0 && currentRoom->up) {
        printf("You move up to a new room.\n");
        return currentRoom->up;
    } else if (strcmp(direction, "down") == 0 && currentRoom->down) {
        printf("You move down to a new room.\n");
        return currentRoom->down;
    } else if (strcmp(direction, "left") == 0 && currentRoom->left) {
        printf("You move left to a new room.\n");
        return currentRoom->left;
    } else if (strcmp(direction, "right") == 0 && currentRoom->right) {
        printf("You move right to a new room.\n");
        return currentRoom->right;
    } else {
        printf("You can't move in that direction!\n");
        return currentRoom;
    }
}

void lookBag(Player* player) {
    printf("Your items in your bag:\n");
    if (player->bagSize == 0) {
        printf("  Your bag is empty.\n");
    } else {
        for (int i = 0; i < player->bagSize; ++i) {
            printf("  - %s\n", player->bag[i]);
        }
    }
}

int main() {
    srand(time(0));

    Player* player = createPlayer(100, 10, 5);

    Room* room1 = createRoom("You are in a dungeon room. You should move to other rooms.");
    Room* room2 = createRoom("This room is full of chests, there may be information inside the chests. Be careful, monsters may appear!");
    Room* room3 = createRoom("There is lava in this room, be careful when walking!");
    Room* room4 = createRoom("There are so many plants in this room. They're all about to die. Monsters are responsible for these.");

    connectRooms(room1, room2, "right");
    connectRooms(room2, room3, "up");
    connectRooms(room3, room4, "left");
    connectRooms(room3, room1, "down");

    Room* currentRoom = room1;

    printf("Welcome to the Nightmare of Darkness!\n");
    int isGameRunning = 1;
    char command[50];

    while (isGameRunning && getHealth(player) > 0) {
        printf("\nCurrent Room:\n");
        displayRoom(currentRoom);

        printf("\nEnter a command: ");
        printf("\n  -move <direction>");
        printf("\n  -look at the bag");
        printf("\n  -save <file>");
        printf("\n  -load <file>");
        printf("\n  -map");
        printf("\n  -exit\n");

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "move", 4) == 0) {
            char direction[10] = "";
            if (sscanf(command + 5, "%s", direction) == 1) {
                currentRoom = movePlayer(currentRoom, direction);


                if (rand() % 100 < 30) {
                    Creature randomCreature = generateRandomCreature();
                    printf("A wild %s appears!\n", randomCreature.name);

                    while (randomCreature.health > 0 && getHealth(player) > 0) {
                        printf("\nYour turn! You attack the %s.\n", randomCreature.name);
                        creatureTakeDamage(&randomCreature, getStrength(player));
                        printf("%s's health: %d\n", randomCreature.name, randomCreature.health);

                        if (randomCreature.health <= 0) {
                            printf("You defeated the %s!\n", randomCreature.name);

                            Item* droppedItem = dropItem();
                            printf("The %s dropped: %s\n", randomCreature.name, droppedItem->name);
                            if (addItem(player, droppedItem->name)) {
                                printf("You picked up the %s.\n", droppedItem->name);
                                droppedItem->useItem(player);
                            }
                            free(droppedItem);
                            break;
                        }

                        printf("The %s attacks you!\n", randomCreature.name);
                        int damage = creatureAttack(&randomCreature);
                        setHealth(player, getHealth(player) - damage);
                        printf("You take %d damage. Your health: %d\n", damage, getHealth(player));

                        if (getHealth(player) <= 0) {
                            printf("You have been defeated...\n");
                            break;
                        }
                    }
                }
            } else {
                printf("Invalid move command. Usage: move <direction>\n");
            }
        } else if (strcmp(command, "look at the bag") == 0) {
            lookBag(player);
        } else if (strncmp(command, "save", 4) == 0) {
            char filepath[50];
            if (sscanf(command + 5, "%s", filepath) == 1) {
                saveGame(filepath, player, currentRoom);
            } else {
                printf("Invalid save command. Usage: save <file>\n");
            }
        } else if (strncmp(command, "load", 4) == 0) {
            char filepath[50];
            if (sscanf(command + 5, "%s", filepath) == 1) {
                if (loadGame(filepath, player, &currentRoom)) {
                    printf("Game loaded successfully.\n");
                }
            } else {
                printf("Invalid load command. Usage: load <file>\n");
            }
        }else if(strcmp(command, "map") == 0){
            int size = 9;
            const char* row1[] = { "Lava Room", "Room of Plants" };
            const char* row2[] = { "Dungeon Room", "Room of Chests" };

            printf("\n");
            drawSquaresRow(0, 0, size, row1, 2);
            drawSquaresRow(0, 0, size, row2, 2);
        } else if (strcmp(command, "exit") == 0) {
            exitGame();
        } else {
            printf("Invalid command!\n");
        }
    }


    destroyPlayer(player);
    destroyRoom(room1);
    destroyRoom(room2);
    destroyRoom(room3);
    destroyRoom(room4);

    return 0;
}



