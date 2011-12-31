#include <stdio.h>
#include <stdlib.h>


struct loc {
        int x;
        int y;
};

struct enemy {
        struct loc *loc;
        char player;
};

struct player {
        struct loc *loc;
        int id;
};

struct game_state {
        struct player *player_ants;
        struct player *player_hills;
        struct enemy *enemy_ants;
        struct enemy *enemy_hills;
        struct loc *food;
        struct loc *dead_ants;

        int count_player_ants;
        int count_player_hills;
        int count_enemy_ants;
        int count_enemy_hills;
        int count_food;
        int count_dead;

        int my_ant_index;
};

int main(void)
{
  int i, player_count = 10;
  struct player *bar;
  struct player *foo = calloc(player_count, sizeof(struct player));
  for (i = 0; i < player_count; i+=1)
  {
          bar = &foo[i];
          bar->id = (i+1);
          bar->loc = malloc(sizeof(struct loc));
          bar->loc->row = 893724;
          bar->loc->col = 55735;
          printf("ID: %d, ", bar->id);
          printf("X: %d, ", bar->loc->row);
          printf("Y: %d\n", bar->loc->col);
  }
  return 0;
}
