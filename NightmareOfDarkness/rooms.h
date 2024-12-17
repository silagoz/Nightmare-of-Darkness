#ifndef ROOMS_H
#define ROOMS_H

#define MAX_ROOM_DESC 256

typedef struct Room {
    char description[MAX_ROOM_DESC];
    struct Room* up;
    struct Room* down;
    struct Room* left;
    struct Room* right;
} Room;


Room* createRoom(const char* description);
void connectRooms(Room* from, Room* to, const char* direction);
void displayRoom(const Room* room);
void destroyRoom(Room* room);

#endif
