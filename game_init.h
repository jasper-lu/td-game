#include <stdio.h>
#define FPS 10
#define ROWS 10
#define COLS 20

void draw_map(char **map, const unsigned int row_size, const unsigned int col_size)
{
    int r, c;
    for(r = 0; r < row_size; ++r)
    {
	for(c = 0; c < col_size + 2; ++c)
	{
	    char blah = map[r][c];
	    if(blah == 'X')
	    {
		xt_par2(XT_BG_GREEN,r,c);
	    }else if(blah == ' '){
		xt_par0(XT_BG_DEFAULT);
	    }else{
		xt_par0(XT_BG_DEFAULT);
	    }
	    printf("%c", map[r][c]);

	//    printf("O");
	}
    }
    printf(XT_CH_NORMAL);
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
