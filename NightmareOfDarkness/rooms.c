#include "rooms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Room* createRoom(const char* description) {
    Room* room = (Room*)malloc(sizeof(Room));
    if (!room) {
        printf("Memory allocation failed for room.\n");
        return NULL;
    }
    strncpy(room->description, description, MAX_ROOM_DESC - 1);
    room->description[MAX_ROOM_DESC - 1] = '\0';
    room->up = NULL;
    room->down = NULL;
    room->left = NULL;
    room->right = NULL;
    return room;
}

// Ýki odayý baðla
void connectRooms(Room* from, Room* to, const char* direction) {
    if (strcmp(direction, "up") == 0) {
        from->up = to;
        if (to) to->down = from;
    } else if (strcmp(direction, "down") == 0) {
        from->down = to;
        if (to) to->up = from;
    } else if (strcmp(direction, "left") == 0) {
        from->left = to;
        if (to) to->right = from;
    } else if (strcmp(direction, "right") == 0) {
        from->right = to;
        if (to) to->left = from;
    } else {
        printf("Invalid direction: %s\n", direction);
    }
}


void displayRoom(const Room* room) {
    if (!room) {
        printf("You are in a void. No room exists here.\n");
        return;
    }
    printf("Room Description: %s\n", room->description);
    printf("Connections:\n");
    if (room->up) printf("  Up: %s\n", room->up->description);
    if (room->down) printf("  Down: %s\n", room->down->description);
    if (room->left) printf("  Left: %s\n", room->left->description);
    if (room->right) printf("  Right: %s\n", room->right->description);
}


void destroyRoom(Room* room) {
    if (!room) return;
    free(room);
}
