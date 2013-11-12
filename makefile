game:	game.o keyboard.o xterm_control.o structs.o astar.o
	gcc game.o keyboard.o xterm_control.o structs.o astar.o -o game

test: test.o keyboard.o xterm_control.o structs.o
	gcc test.o keyboard.o xterm_control.o structs.o -o test
	
test.o: test.c
	gcc -c test.c

astar.o: astar.c
	gcc -c astar.c

game.o:	game.c
	gcc -c game.c
	
keyboard.o: keyboard.c
	gcc -c keyboard.c

xterm_control.o: xterm_control.c
	gcc -c xterm_control.c

structs.o: structs.c
	gcc -c structs.c 
