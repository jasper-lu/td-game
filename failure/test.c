#include <stdio.h>
#include "structs.h"
#include "keyboard.h"
#include "xterm_control.h"
#include "pathfinding.h"
#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

int main() {
  char c = ' ';
  char d = 'T';
  char map[10][10] = {
    {'X','X','X','X','X','X','X','X','X','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ',' ',' ',' ','X',' ',' ',' ','X'},
    {'X',' ','X','X','X',' ',' ',' ',' ','X'},
    {'X',' ',' ',' ',' ',' ','X',' ',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ',' ','X'},
    {'X',' ',' ',' ',' ',' ',' ',' ','O','X'},
    {'X','X','X','X','X','X','X','X','X','X'}
  };
  point b = init_point(2,2);
  while(map[b.y][b.x] != 'O' || (c = getkey()) = KEY_NOTHING)
    {
      int dir = depth_move(b,map);
      printf("%d , " , dir);
      if( dir == DOWN)
	b.y++;
      if( dir == UP)
	b.y--;
      if( dir == LEFT)
	b.x--;
      if( dir == RIGHT)
	b.x++;
      if( c == KEY_ENTER)
	putchar(d);
    }
}
