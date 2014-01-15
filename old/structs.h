#define U 1
#define R 2
#define D 3
#define L 4

struct Point;

typedef struct
{
    int x,y, _n, health;
}Mob;

typedef struct
{
  int x, y, dmg;
}Tower;

Mob init_mob(int x, int y);
void move_mob(Mob *mob, int mob_size, struct Point* end, char **map);

Tower init_Tower(int x, int y);

int loser(Mob* mob, struct Point* end);

int spawn(Mob* mob, int *mob_size, struct Point spawn_point, int count);

int round_won(Mob* mob, int* mob_size);
