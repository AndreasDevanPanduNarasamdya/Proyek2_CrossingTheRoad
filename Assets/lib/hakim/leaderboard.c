// leaderboard.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leaderboard.h"

void initLeaderboard(Leaderboard* lb) {
    lb->head = NULL;
    lb->count = 0;
}

LeaderboardEntry* createEntry(const char* name, int score) {
    LeaderboardEntry* newEntry = (LeaderboardEntry*)malloc(sizeof(LeaderboardEntry));
    strncpy(newEntry->name, name, MAX_NAME_LENGTH - 1);
    newEntry->name[MAX_NAME_LENGTH - 1] = '\0';
    newEntry->score = score;
    newEntry->next = NULL;
    return newEntry;
}

void addScore(Leaderboard* lb, const char* name, int score) {
    LeaderboardEntry* newEntry = createEntry(name, score);

    if (!lb->head || score > lb->head->score) {
        newEntry->next = lb->head;
        lb->head = newEntry;
    } else {
        LeaderboardEntry* current = lb->head;
        while (current->next && current->next->score >= score) {
            current = current->next;
        }
        newEntry->next = current->next;
        current->next = newEntry;
    }

    lb->count++;

    if (lb->count > MAX_ENTRIES) {
        // Remove the last entry
        LeaderboardEntry* current = lb->head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        lb->count--;
    }
}

void displayLeaderboard(const Leaderboard* lb) {
    printf("=== LEADERBOARD ===\n");
    LeaderboardEntry* current = lb->head;
    int rank = 1;
    while (current) {
        printf("%d. %s - %d\n", rank++, current->name, current->score);
        current = current->next;
    }
}

void freeLeaderboard(Leaderboard* lb) {
    LeaderboardEntry* current = lb->head;
    while (current) {
        LeaderboardEntry* next = current->next;
        free(current);
        current = next;
    }
    lb->head = NULL;
    lb->count = 0;
}
