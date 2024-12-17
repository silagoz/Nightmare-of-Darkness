#include "menucommands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawSquaresRow(int x, int y, int size, const char* labels[], int numLabels) {
    int labelRow = size / 2;

    for (int i = 0; i < size; i++) {
        for (int k = 0; k < numLabels; k++) {
            const char* label = labels[k];
            int labelLen = strlen(label);

            for (int j = 0; j < size * 2 + 1; j++) {
                if (i == 0 || i == size - 1 || j == 0 || j == size * 2) {
                    printf("*");
                } else if (i == labelRow && j >= (size * 2 - labelLen) / 2 && j < (size * 2 - labelLen) / 2 + labelLen) {
                    printf("%c", label[j - (size * 2 - labelLen) / 2]);
                } else {
                    printf(" ");
                }
            }
            printf("  ");
        }
        printf("\n");
    }
}


void saveGame(const char* filepath, Player* player, Room* currentRoom) {
    FILE* file = fopen(filepath, "w");
    if (!file) {
        printf("Failed to open file for saving: %s\n", filepath);
        return;
    }

    fprintf(file, "%d %d %d\n", player->health, player->strength, player->bagSize);
    for (int i = 0; i < player->bagSize; i++) {
        fprintf(file, "%s\n", player->bag[i]);
    }

    fprintf(file, "%s\n", currentRoom->description);

    fclose(file);
    printf("Game saved to %s.\n", filepath);
}


int loadGame(const char* filepath, Player* player, Room** currentRoom) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Failed to open file for loading: %s\n", filepath);
        return 0;
    }

    fscanf(file, "%d %d %d", &player->health, &player->strength, &player->bagSize);
    for (int i = 0; i < player->bagSize; i++) {
        player->bag[i] = (char*)malloc(MAX_ITEM_NAME * sizeof(char));
        fscanf(file, "%s", player->bag[i]);
    }

    char roomDescription[MAX_ROOM_DESC];
    fgetc(file);
    fgets(roomDescription, MAX_ROOM_DESC, file);
    roomDescription[strcspn(roomDescription, "\n")] = '\0';
    *currentRoom = createRoom(roomDescription);

    fclose(file);
    printf("Game loaded from %s.\n", filepath);
    return 1;
}


void exitGame() {
    printf("We will meet again soon!\n");
    exit(0);
}
