// leaderboard.h
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 10

typedef struct LeaderboardEntry {
    char name[MAX_NAME_LENGTH];
    int score;
    struct LeaderboardEntry* next;
} LeaderboardEntry;

typedef struct {
    LeaderboardEntry* head;
    int count;
} Leaderboard;

void initLeaderboard(Leaderboard* lb);
void addScore(Leaderboard* lb, const char* name, int score);
void displayLeaderboard(const Leaderboard* lb);
void freeLeaderboard(Leaderboard* lb);

#endif
