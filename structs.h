#define U 1
#define R 2
#define D 3
#define L 4

typedef struct
{
    int x, y, _n, health;
}Mob;

typedef struct
{
  int x, y;
}Tower;

Mob init_mob(int x, int y);
void move_mob(Mob *mob, int mob_size);
