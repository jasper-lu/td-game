#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "astar.h"
#include "structs.h"
#include "keyboard.h"
#include "xterm_control.h" 
#include "game_init.h"

int main() {

  setbuf(stdout,NULL);

  Mob * MOBS;

  char **map;
  map = malloc(sizeof(char*) * ROWS); 

  int i,Score;
  for (i = 0;  i < COLS + 2; ++i)
    map[i] = malloc(sizeof(char) * (COLS + 2));

  MOBS = malloc(sizeof(Mob) * 100);
  MOBS[0] = init_mob(1,1);
  int mob_size = 1;

  xt_par0(XT_CLEAR_SCREEN);
  xt_par2(XT_SET_ROW_COL_POS,1,1);

  init_map(map, ROWS, COLS);
  Tower* arr;
  i = 0;
  arr = malloc(sizeof(Tower) * 100);

  int row = 1;
  int col = 1;
  xt_par2(XT_SET_ROW_COL_POS,row,col);

  char c;

  Point finish = init_Point(18,8);

  printf("Before game loop \n");

  int move_c = 0;
  while(1)
    {
      if ((c = getkey()) == KEY_NOTHING){

      }
      else if(c == KEY_F9) 
	{
	  xt_par0(XT_CLEAR_SCREEN);
	  xt_par2(XT_SET_ROW_COL_POS,row=1,col=1);
	  break;
	}
      else if (c == KEY_UP && row > 1)
	{ 
	  xt_par2(XT_SET_ROW_COL_POS,--row,col);
	}
      else if (c == KEY_DOWN && row < 24)
	{
	  xt_par2(XT_SET_ROW_COL_POS,++row,col);
	}
      else if (c == KEY_RIGHT && col < 80)
	{
	  xt_par2(XT_SET_ROW_COL_POS,row,++col);
	}
      else if (c == KEY_LEFT && col > 1)
	{
	  xt_par2(XT_SET_ROW_COL_POS,row,--col);
	}
      else if ((c == 'T' || c == 't') )
	{
	  putchar('T');
	  map[row - 1][col - 1] = 'T';
	  Tower A = init_Tower(col-1,row-1);
	  arr[i] = A;
	  i++;
	}else if (c == 'r')
	{
	    printf("hi");
	    if(move_c == 0)
		move_c = 1;
	    else
		move_c = 0;
	}

     if(i > 0)
	tower_logic(arr, MOBS, mob_size);
    
      if(move_c == 4)
      {
	  move_mob(&MOBS[0], mob_size, &finish, map);
	  move_c = 0;
      }else{
	  ++move_c;
      }

      xt_par0(XT_CLEAR_SCREEN);
      xt_par2(XT_SET_ROW_COL_POS,1,1);

      draw_map(map, ROWS, COLS, arr, i, MOBS, mob_size);

      xt_par2(XT_SET_ROW_COL_POS, MOBS[0].y + 1,MOBS[0].x + 1);


      xt_par2(XT_SET_ROW_COL_POS, row,col);
      
      xt_par2(XT_SET_ROW_COL_POS, 15, 0);
      printf("Score:%d\n location of mob: %d,%d\n",Score,MOBS->x,MOBS->y);      
      xt_par2(XT_SET_ROW_COL_POS, row,col);

      if(loser(MOBS, &finish))
      {
	  printf("YOU LOSE,\n LOSER\n TRY AGAIN NEXT TIME \n");
//	  usleep(3000000);
	  break;
      }

      usleep(1000000 / FPS);
//	usleep(1000000);
    }
  getkey_terminate();

  xt_par0(XT_CLEAR_SCREEN);
  xt_par2(XT_SET_ROW_COL_POS,1,1);
    

  free(MOBS);
  free(arr);
}
