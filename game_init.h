#include <stdio.h>
#define FPS 10
#define ROWS 10
#define COLS 20

void draw_map(char **map, const unsigned int row_size, const unsigned int col_size)
{
    int r, c;
    for(r = 0; r < row_size; ++r)
    {
//	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",map[r][0],map[r][1],map[r][2],map[r][3],map[r][4],map[r][5],map[r][6],map[r][7],map[r][8],map[r][9],map[r][10],map[r][11],map[r][12],map[r][13],map[r][14],map[r][15],map[r][16],map[r][17],map[r][18],map[r][19]);
	for(c = 0; c < col_size + 2; ++c)
	{
	    xt_par0(XT_CH_RED);
	    printf("%c",map[r][c]); 
	//    printf("O");
	}
    }
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
}
