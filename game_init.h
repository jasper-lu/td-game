#include <stdio.h>
#define FPS 10
#define ROWS 10
#define COLS 20

void draw_towers(Tower *arr, int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
	    xt_par2(XT_SET_ROW_COL_POS,arr[i].y,arr[i].x);
	    printf("T");
	}
}

void draw_mobs(Mob *mobs, int n)
{
    int i;
    for(i = 0; i < n; ++i)
    {
	if(mobs->health > 0)
	{
	    xt_par2(XT_SET_ROW_COL_POS,mobs[i].y+1,mobs[i].x+1);
	    printf("M");
	}
	++mobs;
    }
}

void draw_map(char **map, const unsigned int row_size, const unsigned int col_size, Tower* arr, int arr_size, Mob* mobs, int mob_size)
{
    int r, c;
    printf(XT_CH_GREEN);
    for(r = 0; r < row_size; ++r)
    {
	for(c = 0; c < col_size + 2; ++c)
	{
	    char blah = map[r][c];
	    if(blah == 'X')
	    {
		xt_par2(XT_BG_BLUE,r,c);
	    }else if(blah == ' '){
		xt_par2(XT_BG_DEFAULT,r,c);
	    }else{
		xt_par2(XT_BG_DEFAULT,r,c);
	    }
	    printf("%c", map[r][c]);
	    xt_par2(XT_BG_DEFAULT,r,c);

	    //    printf("O");
	}
    }
    draw_towers(arr,arr_size); 
    draw_mobs(mobs,mob_size);
}

void init_map(char** map, const unsigned int row_size, const unsigned int col_size)
{
    FILE *fp;
    fp = fopen("map.txt", "r");
    char ch;

    int i,j;

    for(i = 0; i < ROWS; i++)
    {
	for(j = 0; j < COLS + 2; j++)
	{
	    ch = fgetc(fp);
	    map[i][j] = ch;
	}
    }
    fclose(fp);
}
