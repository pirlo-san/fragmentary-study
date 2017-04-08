#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct
{
    int              no;
    char             name[20];
    struct list_head list_node;
}player_t;

player_t *alloc_player(int no, const char *name)
{
    player_t *player = (player_t *)calloc(1, sizeof(player_t));

    player->no = no;
    strcpy(player->name, name);
    return player;
}

void dump_palyers(const struct list_head *players)
{
    if (list_empty(players))
        fprintf(stderr, "no players\n\n");

    player_t *player;
    list_for_each_entry(player, players, list_node)
    {
        fprintf(stderr, "no: %02d, name: %10s\n", player->no, player->name);
    }
    fprintf(stderr, "\n");
}
    
int main(int argc, char *argv[])
{
    LIST_HEAD(players);
    dump_palyers(&players);

    player_t *player1 = alloc_player(3, "maldini");
    list_add(&player1->list_node, &players);
    dump_palyers(&players);

    player_t *player2 = alloc_player(10, "seedorf");
    list_add(&player2->list_node, &player1->list_node);
    dump_palyers(&players);

    player_t *player3 = alloc_player(13, "nesta");
    list_add(&player3->list_node, &player2->list_node);
    dump_palyers(&players);

    player_t *player4 = alloc_player(21, "pirlo");
    list_add(&player4->list_node, &player3->list_node);
    dump_palyers(&players);

    player_t *player5 = alloc_player(22, "kaka");
    list_add(&player5->list_node, &player4->list_node);
    dump_palyers(&players);

    list_del(&player1->list_node);
    dump_palyers(&players);
    free(player1);

    list_del(&player2->list_node);
    dump_palyers(&players);
    free(player2);

    list_del(&player3->list_node);
    dump_palyers(&players);
    free(player3);

    list_del(&player4->list_node);
    dump_palyers(&players);
    free(player4);

    list_del(&player5->list_node);
    dump_palyers(&players);
    free(player5);

    return 0;
}

