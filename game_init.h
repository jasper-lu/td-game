#include <stdio.h>
#define FPS 10
#define ROWS 10
#define COLS 20

void draw_map(char **map, const unsigned int row_size, const unsigned int col_size)
{
    int r, c;
    for(r = 0; r < row_size; ++r)
    {
	for(c = 0; c < col_size; ++c)
	    putchar(map[r][c]); 
    }
}

void init_map(char** map, const unsigned int row_size, const unsigned int col_size)
{
    FILE *fp;
    fp = fopen("map", "r");
    char ch;

    map = malloc(ROWS); 
    int i,j;

    for(i = 0; i < ROWS; i++)
    {
	map[i] = malloc(COLS);
	for(j = 0; j < COLS; j++)
	{
	    ch = fgetc(fp);
	    map[i][j] = ch;
	}
    }
    printf("%c", map[0][0]);

//    draw_map(map, row_size, col_size);
}


void redraw(char **map)
{}
